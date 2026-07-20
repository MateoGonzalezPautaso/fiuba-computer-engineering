"""
FastText vectorizer con interfaz sklearn-compatible.

Uso en notebook
---------------
    from embeddings import make_fasttext

    vec = make_fasttext()
    X_train = vec.fit_transform(X_train_text)   # (n, 300)
    X_val   = vec.transform(X_val_text)         # (n, 300)

El texto de entrada debe venir preprocesado con clean_classical()
(de preprocessing.py), igual que para BoW y TF-IDF.

Modelo preentrenado
-------------------
Se usa cc.es.300.bin de Meta: 300 dimensiones, ~7 GB.
"""

import numpy as np
import fasttext                      # pip install fasttext-wheel
import fasttext.util
from pathlib import Path
from sklearn.base import BaseEstimator, TransformerMixin

_DEFAULT_FILENAME: str = "cc.es.300.bin"
_DEFAULT_DIM: int = 300

# ---------------------------------------------------------------------------
# Helpers internos
# ---------------------------------------------------------------------------

def _load_model(model_path: Path) -> fasttext.FastText._FastText:
    """
    Carga el modelo desde disco. Si no existe, lo descarga.

    fasttext.util.download_model descarga cc.es.300.bin al directorio
    de trabajo actual.
    """
    if not model_path.exists():
        print(
            f"[FastText] Modelo no encontrado en '{model_path}'.\n"
            f"[FastText] Descargando cc.es.300.bin (Puede tardar un rato)..."
        )
        fasttext.util.download_model("es", if_exists="ignore")

        downloaded = Path(_DEFAULT_FILENAME)
        if model_path != downloaded:
            # Si se pidió una ruta distinta al default, mover el archivo
            downloaded.rename(model_path)

    print(f"[FastText] Cargando modelo desde '{model_path}'...")
    model = fasttext.load_model(str(model_path))
    print(f"[FastText] Modelo cargado. Dimensión: {model.get_dimension()}")
    return model


def _embed_text(text: str, model: fasttext.FastText._FastText) -> np.ndarray:
    """
    Convierte un texto en un vector (dim,) promediando los vectores
    de sus tokens.

    Texto vacío → vector de ceros (no rompe el pipeline).
    """
    tokens = text.split()
    if not tokens:
        return np.zeros(model.get_dimension(), dtype=np.float32)

    # get_word_vector ya maneja OOV internamente via subpalabras
    vectors = np.array(
        [model.get_word_vector(token) for token in tokens],
        dtype=np.float32
    )

    return vectors.mean(axis=0)


# ---------------------------------------------------------------------------
# FastTextVectorizer
# ---------------------------------------------------------------------------

class FastTextVectorizer(BaseEstimator, TransformerMixin):
    """
    Vectorizador de documentos basado en FastText preentrenado en español.

    Parameters
    ----------
    model_path : str | Path
        Ruta al archivo .bin del modelo FastText.
        Defecto: "cc.es.300.bin" en el directorio de trabajo.
    target_dim : int | None
        Si se indica, reduce el modelo a esa dimensión después de cargarlo
        usando fasttext.util.reduce_model
    """

    def __init__(
        self,
        model_path: str | Path = _DEFAULT_FILENAME,
        target_dim: int | None = None
    ):
        self.model_path = Path(model_path)
        self.target_dim = target_dim
        self._model = None

    # ------------------------------------------------------------------
    # Interfaz sklearn
    # ------------------------------------------------------------------

    def fit(self, X, y=None):
        """
        Carga el modelo FastText. No entrena nada: el modelo es preentrenado.
        y se ignora (existe solo para compatibilidad con Pipeline de sklearn).
        """
        self._model = _load_model(self.model_path)

        if self.target_dim is not None:
            current_dim = self._model.get_dimension()
            if self.target_dim < current_dim:
                print(
                    f"[FastText] Reduciendo dimensión: "
                    f"{current_dim} → {self.target_dim}"
                )
                fasttext.util.reduce_model(self._model, self.target_dim)

        return self

    def transform(self, X) -> np.ndarray:
        """
        Convierte una lista de textos ya preprocesados en una matriz
        de embeddings de forma (n_documentos, dim).

        Parameters
        ----------
        X : iterable de str
            Textos preprocesados con clean_classical().

        Returns
        -------
        np.ndarray de shape (n, dim), dtype float32
        """
        if self._model is None:
            raise RuntimeError(
                "El modelo no está cargado. Llamá a .fit() antes de .transform()."
            )

        return np.vstack(
            [_embed_text(text, self._model) for text in X]
        ).astype(np.float32)


# ---------------------------------------------------------------------------
# Factory function — análoga a make_bow() y make_tfidf() en data_utils.py
# ---------------------------------------------------------------------------

def make_fasttext(
    model_path: str | Path = _DEFAULT_FILENAME,
    target_dim: int | None = None
) -> FastTextVectorizer:
    """
    Crea un FastTextVectorizer listo para usar.
    """
    return FastTextVectorizer(model_path=model_path, target_dim=target_dim)