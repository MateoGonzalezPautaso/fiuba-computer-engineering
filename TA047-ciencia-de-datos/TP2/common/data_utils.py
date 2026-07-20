"""
Utilidades de datos: split de validación y vectorizadores.

Split
-----
Todos los experimentos del TP deben usar get_split. Si cada notebook
hace su propio train_test_split con random_state distinto, los
F1-macro entre modelos dejan de ser comparables.

Vectorizadores
--------------
- ngram_range=(1, 2): unigramas + bigramas. Los bigramas capturan
  "no funciona", "muy bueno"
- min_df=5: mínima cantidad de documentos en los que debe aparecer una 
  palabra para entrar al vocabulario. Con 5, una palabra que aparece en 
  solo 1, 2, 3 o 4 reseñas se descarta. Filtra typos ("exelentte"), 
  palabras muy raras, y nombres propios poco frecuentes que no generalizan.
- max_df=0.95: máxima proporción de documentos en los que puede aparecer 
  una palabra. Con 0.95, una palabra que aparece en más del 95% de las 
  reseñas se descarta. Son palabras tan comunes que no distinguen ninguna clase.
- sublinear_tf=True en TF-IDF: aplica 1 + log(tf), reduce el peso de tokens 
  repetidos muchas veces en una misma reseña.
- lowercase=False: el texto ya viene preprocesado por clean_classical,
  no se quiere doble lowercase ni re-tokenización.
- token_pattern: expresión regular que define qué cuenta 
  como token. El patrón por defecto de sklearn descarta palabras de un solo 
  carácter y no maneja guiones. Este patrón acepta palabras de dos o más 
  caracteres y permite guiones internos, para que "anti-rrobo" o "re-entrega" 
  no se partan en dos tokens.
"""

import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from sklearn.model_selection import train_test_split

import re
from nltk.corpus import sentiwordnet as swn

from scipy.sparse import hstack, csr_matrix
from sklearn.base import BaseEstimator, ClassifierMixin

from common.preprocessing import KEEP_WORDS

SEED: int = 42
VAL_SIZE: float = 0.2

def get_split(
    df: pd.DataFrame,
    text_col: str = "text",
    label_col: str = "label",
    val_size: float = VAL_SIZE,
    seed: int = SEED
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    """Devuelve (X_train, X_val, y_train, y_val) con split estratificado."""
    # Un split estratificado garantiza que la proporción de cada clase 
    # se mantenga igual en ambas partes.
    return train_test_split(
        df[text_col].to_numpy(),
        df[label_col].to_numpy(),
        test_size=val_size,
        random_state=seed,
        stratify=df[label_col].values
    )

def make_bow(
    ngram_range: tuple[int, int] = (1, 2),
    min_df: int = 5,
    max_df: float = 0.95,
    max_features: int | None = 50_000 # límite del tamaño del vocabulario.
) -> CountVectorizer:
    """Bag-of-Words con conteos enteros."""
    return CountVectorizer(
        ngram_range=ngram_range,
        min_df=min_df,
        max_df=max_df,
        max_features=max_features,
        lowercase=False,
        token_pattern=r"(?u)\b\w[\w-]+\b"
    )

def make_tfidf(
    ngram_range: tuple[int, int] = (1, 2),
    min_df: int = 5,
    max_df: float = 0.95,
    max_features: int | None = 100_000,
    sublinear_tf: bool = True
) -> TfidfVectorizer:
    """TF-IDF con sublinear TF."""
    return TfidfVectorizer(
        ngram_range=ngram_range,
        min_df=min_df,
        max_df=max_df,
        max_features=max_features,
        sublinear_tf=sublinear_tf,
        lowercase=False,
        token_pattern=r"(?u)\b\w[\w-]+\b"
    )

def extract_features(texts_raw: list[str]) -> np.ndarray:
    """Extrae features numéricas del texto crudo.

    Features de longitud, puntuación, negación y sentimiento (SentiWordNet).
    Devuelve matriz (n, n_features) lista para concatenar con TF-IDF/BoW
    usando scipy.sparse.hstack.

    Parametros
    ----------
    texts_raw : list[str]
        Textos sin preprocesar (el texto crudo original).
    """
    rows = []
    negaciones = KEEP_WORDS  # reutiliza las negaciones ya definidas

    for text in texts_raw:
        tokens = text.lower().split()
        n_tokens      = len(tokens)
        n_chars       = len(text)
        avg_word_len  = np.mean([len(t) for t in tokens]) if tokens else 0

        # Puntuación y mayúsculas
        n_excl        = text.count("!")
        n_inter       = text.count("?")
        ratio_mayusc  = sum(1 for c in text if c.isupper()) / max(len(text), 1)
        signos_rep    = int(bool(re.search(r"[!?]{2,}", text)))

        # Negaciones
        n_neg         = sum(1 for t in tokens if t in negaciones)

        # SentiWordNet - promedio de scores sobre los tokens
        pos_scores, neg_scores, obj_scores = [], [], []
        for token in tokens:
            synsets = list(swn.senti_synsets(token))
            if synsets:
                s = synsets[0]
                pos_scores.append(s.pos_score())
                neg_scores.append(s.neg_score())
                obj_scores.append(s.obj_score())

        avg_pos = np.mean(pos_scores) if pos_scores else 0.0
        avg_neg = np.mean(neg_scores) if neg_scores else 0.0
        avg_obj = np.mean(obj_scores) if obj_scores else 0.0
        sentiment_diff = avg_pos - avg_neg  # positivo -> reseña positiva

        rows.append([
            n_tokens, n_chars, avg_word_len,
            n_excl, n_inter, ratio_mayusc, signos_rep,
            n_neg,
            avg_pos, avg_neg, avg_obj, sentiment_diff,
        ])

    return np.array(rows, dtype=np.float32)


class VectorizerPlusFeaturesPipeline(BaseEstimator, ClassifierMixin):
    """
    Wrapper que combina un vectorizador (TF-IDF o BoW) + features numéricas
    + clasificador en un solo objeto con interfaz sklearn (fit/predict).

    Permite usar save_model / load_model igual que con Pipeline.

    Parameters
    ----------
    vectorizer : TfidfVectorizer | CountVectorizer
        Vectorizador de texto. Puede ser make_tfidf() o make_bow().
    classifier : estimator
        Clasificador sklearn-compatible. Debe responder a fit/predict.
    """

    def __init__(self, vectorizer, classifier):
        self.vectorizer = vectorizer
        self.classifier = classifier

    def _unpack(self, X):
        """Acepta array 2D (n, 2), lista de tuplas, o solo array de textos."""
        X = np.array(X, dtype=object)
        if X.ndim == 2:
            return X[:, 0], X[:, 1]
        if X.ndim == 1 and isinstance(X[0], (tuple, list, np.ndarray)):
            return np.array([x[0] for x in X]), np.array([x[1] for x in X])
        return X, X

    def _build_matrix(self, X_text, X_raw):
        tfidf_matrix = self.vectorizer.transform(X_text)
        num_features = csr_matrix(extract_features(X_raw))
        return hstack([tfidf_matrix, num_features])

    def fit(self, X, y, sample_weight=None):
        X_text, X_raw = self._unpack(X)
        tfidf_matrix = self.vectorizer.fit_transform(X_text)
        num_features = csr_matrix(extract_features(X_raw))
        X_combined = hstack([tfidf_matrix, num_features])
        self.classifier.fit(X_combined, y, sample_weight=sample_weight)
        return self

    def predict(self, X):
        X_text, X_raw = self._unpack(X)
        X = self._build_matrix(X_text, X_raw)
        return self.classifier.predict(X)