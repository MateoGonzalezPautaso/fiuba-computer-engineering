# TA047 - Ciencia de Datos — TP2

**Materia:** TA047 - Ciencia de Datos
**Docente:** Dr. Ing. Rodríguez
**Cuatrimestre:** 1°C 2026
**Grupo:** 02
**Facultad:** Facultad de Ingeniería — Universidad de Buenos Aires (FIUBA)

---

## Integrantes

| Nombre | Padrón | Email |
|---|---|---|
| Bermudez, Agustin | 111863 | abermudez@fi.uba.ar |
| Calderón, Tiago | 111894 | tcalderon@fi.uba.ar |
| Gonzalez Pautaso, Mateo | 111699 | magonzalezp@fi.uba.ar |
| Moreyra, Santiago | 110531 | smoreyra@fi.uba.ar |
| Nieves, Maylen | 111271 | mnieves@fi.uba.ar |

---

## Descripción

Trabajo Práctico 2 de la materia Ciencia de Datos (TA047): una **competencia de
Kaggle** de clasificación de texto. Se entrena y compara un conjunto de modelos
(Bayes Naive, Random Forest, XGBoost, Red Neuronal y un Ensamble), con
data augmentation y embeddings de por medio.

## Estructura

```
TP2/                                            # Competencia Kaggle - Clasificación de texto
├── Consigna/                                   # Enunciado e informe final
├── Template Notebooks/                         # Plantillas base para cada modelo
├── common/                                     # Utilidades compartidas entre notebooks
│   ├── data_utils.py
│   ├── embeddings.py
│   ├── evaluation.py
│   ├── io_utils.py
│   └── preprocessing.py
├── data/                                       # Datasets y scripts de augmentation
│   ├── train.csv
│   ├── test.csv
│   ├── sample_submission.csv
│   ├── train_augmented_eda_balanced.csv
│   ├── train_augmented_llm_balanced.csv
│   ├── augment_data.py
│   └── augment_data_llm.py
├── Entregas/
│   ├── Bayes Naive/
│   ├── Random Forest/
│   ├── XGBoost/
│   ├── Red Neuronal/
│   └── Ensamble/
├── TA047R_TP2_GRUPO02_EDA.ipynb
└── TA047R_TP2_GRUPO02_REPORTE.pdf
```
