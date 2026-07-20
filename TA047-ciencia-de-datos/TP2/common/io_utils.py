"""
Generación de submissions para Kaggle y persistencia de modelos + vectorizadores.

El CSV de submission sigue el formato de Kaggle: columnas id
y label, una fila por reseña del test set.
"""

from pathlib import Path

import joblib
import pandas as pd
import numpy as np

MODELS_DIR      = Path("models")
SUBMISSIONS_DIR = Path("submissions")

def save_model(pipeline, name: str, models_dir: Path = MODELS_DIR) -> Path:
    """Persiste un modelo en disco."""
    models_dir.mkdir(parents=True, exist_ok=True)
    path = models_dir / f"{name}.joblib"
    joblib.dump(pipeline, path)
    print(f"Modelo guardado → {path}")
    return path

def load_model(name: str, models_dir: Path = MODELS_DIR):
    """Recupera un modelo guardado con save_model."""
    return joblib.load(Path(models_dir) / f"{name}.joblib")

def make_submission(
    pipeline,
    test_df: pd.DataFrame,
    filename: str,
    text_col: str = "text",
    id_col: str = "id",
    submissions_dir: Path = SUBMISSIONS_DIR,
    raw_texts=None,
) -> Path:
    """Genera el CSV de submission a partir de un modelo y el test set.

    El archivo generado sigue exactamente el formato del sample_submission
    de Kaggle: columnas id y label, sin índice.

    Parameters
    ----------
    pipeline : estimator
        Pipeline ya entrenado. Debe responder a ``.predict(textos)``.
    test_df : DataFrame
        Test set con columnas ``id`` y ``text``.
    filename : str
        Nombre del archivo de salida, e.g. ``"submission_v1.csv"``.
    raw_texts : array-like, optional
        Textos crudos para VectorizerPlusFeaturesPipeline, que necesita
        dos argumentos en predict (X_text, X_raw). Si es None, se usa
        el predict estándar de un solo argumento.
    """
    submissions_dir.mkdir(parents=True, exist_ok=True)

    if raw_texts is not None:
        preds = pipeline.predict(np.column_stack([test_df[text_col].values, raw_texts]))
    else:
        preds = pipeline.predict(test_df[text_col].values)

    sub = pd.DataFrame({id_col: test_df[id_col].values, "label": preds.astype(int)})

    path = submissions_dir / filename
    sub.to_csv(path, index=False)

    dist = sub["label"].value_counts(normalize=True).sort_index()
    print(f"Predicción guardada → {path}  ({len(sub)} predicciones)")
    print(f"Distribución: {', '.join(f'clase {k}: {v:.1%}' for k, v in dist.items())}")

    return path