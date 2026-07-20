"""
Preprocesamiento de texto para reseñas en español.

Dos funciones de limpieza con propósitos distintos:

- clean_minimal: NFKC + colapso de whitespace. Para BERT/BETO y
  embeddings contextuales, donde el tokenizer del modelo
  pre-entrenado espera texto natural.

- clean_classical: para BoW (Bag of Words) / TF-IDF (Term
  Frequency-Inverse Document Frequency) / embeddings estáticos.
  Lowercase + tokenización + remoción de stopwords.
  Conserva negaciones e intensificadores porque son
  centrales para análisis de sentimientos.

Si spaCy y el modelo es_core_news_sm están instalados, se usa
lematización completa. corriendo, corrió, corre -> correr
"""

import re
import unicodedata
import spacy

# ---------------------------------------------------------------------------
# Stopwords y palabras que SIEMPRE se conservan (negaciones, intensificadores,
# adversativas). Son críticas para el sentimiento: "no me gustó" vs "me gustó"
# colapsarían al mismo bag-of-words si removiéramos "no".
# ---------------------------------------------------------------------------

KEEP_WORDS: set[str] = {
    # negaciones
    "no", "ni", "nunca", "jamás", "jamas", "tampoco", "nada", "nadie",
    "ningún", "ninguna", "ningunos", "ningunas", "sin",
    # intensificadores / atenuadores
    "muy", "mucho", "mucha", "muchos", "muchas",
    "poco", "poca", "pocos", "pocas",
    "demasiado", "demasiada", "demasiados", "demasiadas",
    "bastante", "bastantes",
    # adversativas
    "pero", "sino", "aunque",
}

# Stopwords clásicas en español (basadas en la lista canónica de NLTK).
# Se quitan luego las de KEEP_WORDS.
_RAW_STOPWORDS: set[str] = set((
    "de la que el en y a los del se las por un para con una su al lo como "
    "más mas le ya o este sí si esta entre cuando sobre también tambien me "
    "hasta hay donde quien quién desde todo nos durante todos uno les contra "
    "otros ese eso ante ellos esto mí mi antes algunos qué que unos yo otro "
    "otras otra él el tanto esa estos quienes cual cuál ella estar estas "
    "algunas algo nosotros mis tú tu te ti tus ellas nosotras vosotros "
    "vosotras os mío mia mios mias tuyo tuya tuyos tuyas suyo suya suyos "
    "suyas nuestro nuestra nuestros nuestras vuestro vuestra vuestros "
    "vuestras esos esas estoy estás está estamos estáis están esté estés "
    "estemos estéis estén estaré estarás estará estaremos estaréis estarán "
    "estaría estarías estaríamos estaríais estarían estaba estabas estábamos "
    "estabais estaban estuve estuviste estuvo estuvimos estuvisteis "
    "estuvieron estuviera estuvieras estuviéramos estuvierais estuvieran "
    "estuviese estuvieses estuviésemos estuvieseis estuviesen estando estado "
    "estada estados estadas estad he has ha hemos habéis han haya hayas "
    "hayamos hayáis hayan habré habrás habrá habremos habréis habrán habría "
    "habrías habríamos habríais habrían había habías habíamos habíais habían "
    "hube hubiste hubo hubimos hubisteis hubieron hubiera hubieras "
    "hubiéramos hubierais hubieran hubiese hubieses hubiésemos hubieseis "
    "hubiesen habiendo habido habida habidos habidas soy eres es somos sois "
    "son sea seas seamos seáis sean seré serás será seremos seréis serán "
    "sería serías seríamos seríais serían era eras éramos erais eran fui "
    "fuiste fue fuimos fuisteis fueron fuera fueras fuéramos fuerais fueran "
    "fuese fueses fuésemos fueseis fuesen siendo sido tengo tienes tiene "
    "tenemos tenéis tienen tenga tengas tengamos tengáis tengan tendré "
    "tendrás tendrá tendremos tendréis tendrán tendría tendrías tendríamos "
    "tendríais tendrían tenía tenías teníamos teníais tenían tuve tuviste "
    "tuvo tuvimos tuvisteis tuvieron tuviera tuvieras tuviéramos tuvierais "
    "tuvieran tuviese tuvieses tuviésemos tuvieseis tuviesen teniendo tenido "
    "tenida tenidos tenidas tened"
).split())

STOPWORDS: set[str] = _RAW_STOPWORDS - KEEP_WORDS

# ---------------------------------------------------------------------------
# Carga del modelo de spaCy.
# ---------------------------------------------------------------------------

_nlp = None

def _load_spacy() -> spacy.language.Language:
    """Carga es_core_news_sm la primera vez que se llama, reutiliza luego."""
    global _nlp
    if _nlp is None:
        _nlp = spacy.load("es_core_news_sm", disable=["parser", "ner"])
        
    return _nlp

# ---------------------------------------------------------------------------
# Limpieza
# ---------------------------------------------------------------------------

_WS_RE = re.compile(r"\s+")

def clean_minimal(text: str) -> str:
    """Limpieza mínima: NFKC + colapso de whitespace.
    Normal Form Compatibility Composed es un método de normalización de 
    texto Unicode que estandariza caracteres visualmente similares

    Para BETO/BERT y embeddings contextuales. No baja a minúsculas (BETO
    es cased; "BUENO" y "bueno" llevan distinta señal).
    """
    text = unicodedata.normalize("NFKC", str(text))
    text = _WS_RE.sub(" ", text).strip()
    return text

def clean_classical(
    text: str,
    *,
    lemmatize: bool = True,
    remove_accents: bool = False,
    min_token_len: int = 2
) -> str:
    """Limpieza para BoW / TF-IDF / embeddings estáticos.

    Parameters
    ----------
    text : str
        Texto crudo.
    lemmatize : bool, default True
        Lematiza los tokens usando spaCy (corriendo -> correr).
    remove_accents : bool, default False
        Si True, normaliza quitando tildes. En español puede colapsar
        pares semánticamente distintos (sí/si, más/mas, té/te), por eso
        viene desactivado por defecto.
    min_token_len : int, default 2
        Descarta tokens de menos de N caracteres (filtra ruido tipo "a", "o").
    """
    text = clean_minimal(text).lower()
    if remove_accents:
        text = "".join(
            c for c in unicodedata.normalize("NFKD", text)
            if not unicodedata.combining(c)
        )

    nlp = _load_spacy()
    doc = nlp(text)
    tokens: list[str] = []
    for tok in doc:
        if tok.is_punct or tok.is_space or tok.like_num:
            continue
        lemma = tok.lemma_.lower().strip() if lemmatize else tok.text
        if not lemma or lemma in STOPWORDS:
            continue
        if len(lemma) < min_token_len:
            continue
        tokens.append(lemma)

    return " ".join(tokens)

def clean_batch(texts: list[str], **kwargs) -> list[str]:
    """Aplica clean_classical a una colección."""
    return [clean_classical(t, **kwargs) for t in texts]