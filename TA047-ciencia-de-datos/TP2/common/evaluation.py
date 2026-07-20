"""
evaluate: imprime métricas en pantalla.
No persiste nada más, cada notebook es una entrega independiente.
"""

from typing import Any

import numpy as np
import pandas as pd
from sklearn.metrics import (
    classification_report,
    confusion_matrix,
    f1_score,
    precision_score,
    recall_score,
    accuracy_score
)

CLASS_NAMES = ["negativa", "neutra", "positiva"]

def evaluate(
    name: str,
    y_true: np.ndarray,
    y_pred: np.ndarray,
    hyperparams: dict[str, Any] | None = None
) -> None:
    """Imprime métricas completas del modelo en el set de validación.

    Parameters
    ----------
    name : str
        Nombre del experimento, e.g. ``"nb_tfidf_uniform"``.
    y_true, y_pred : array-like
        Labels reales y predichas en el set de validación.
    hyperparams : dict, optional
        Hiperparámetros del modelo. Se imprimen como referencia.
    """
    y_true = np.asarray(y_true)
    y_pred = np.asarray(y_pred)

    print(f"\n=== {name} ===")
    if hyperparams:
        print(f"Hiperparámetros: {hyperparams}\n")

    print(f"F1-macro:  {f1_score(y_true, y_pred, average='macro', zero_division=0):.4f}")
    print(f"Precision: {precision_score(y_true, y_pred, average='macro', zero_division=0):.4f}")
    print(f"Recall:    {recall_score(y_true, y_pred, average='macro', zero_division=0):.4f}")
    print(f"Accuracy:  {accuracy_score(y_true, y_pred):.4f}\n")

    print(classification_report(y_true, y_pred, target_names=CLASS_NAMES, digits=4, zero_division=0))

    cm_df = pd.DataFrame(confusion_matrix(y_true, y_pred), index=CLASS_NAMES, columns=CLASS_NAMES)
    print("Matriz de confusión (filas=real, cols=predicho):")
    print(cm_df.to_string())