# Trabajo Práctico 2
## Reseñas de Amazon en español

**TA047 Ciencia de Datos — Dr. Ing. Rodríguez — 1°C 2026**

---

## Introducción

En este trabajo práctico vamos a utilizar una colección de reseñas de productos de Amazon en idioma español y vamos a tratar de clasificar cada reseña según su sentimiento en tres categorías: negativa, neutra o positiva.

---

## Modalidad de entrega

### Repositorio

Deberán utilizar el mismo repositorio del TP1: `TA047R-1C2026-GRUPOXX`

En dicho repositorio deberá estar disponible todo el contenido obligatorio de la entrega (notebooks, modelos entrenados, *datasets*, reportes, presentación) y cualquier archivo que sea necesario para la correcta ejecución del trabajo.

### Notebook

El trabajo debe ser realizado en una notebook *Jupyter* de Python, se espera que la misma contenga **todos** los resultados de la ejecución los cuales siempre deben ser **reproducibles**. La notebook debe respetar la siguiente nomenclatura:

```
TA047R_TP2_GRUPOXX_CHPX_ENTREGA
```

En el caso que sea estrictamente necesario entregar más de una notebook, las mismas deben contar con una numeración correlativa manteniendo un orden lógico entre ellas:

```
TA047R_TP2_GRUPOXX_CHPX_ENTREGA_N1
TA047R_TP2_GRUPOXX_CHPX_ENTREGA_N2
...
```

Las secciones del trabajo deben estar claramente diferenciadas en la notebook utilizando celdas de *markdown*. Se debe incluir una sección principal con el título del trabajo, el número de grupo y el nombre de todos los integrantes.

Todo análisis realizado debe estar acompañado de su respectiva explicación y toda decisión tomada debe estar debidamente justificada. Cualquier hipótesis que sea considerada en el desarrollo del trabajo práctico debe ser detallada y debe estar informada en la entrega.

Cualquier criterio que se utilice basado en fuentes externas (papers, bibliografía, etc.) debe estar correctamente referenciado en el trabajo.

### Modelos

Todos los modelos entrenados deben ser guardados en un archivo (joblib / pickle) y deben estar disponibles en la entrega para ser utilizados por el equipo docente.

### Reportes

Se deberá confeccionar un reporte (en formato PDF) a modo de resumen de los puntos desarrollados en cada ejercicio. El documento deberá tener la siguiente nomenclatura:

```
TA047R_TP2_GRUPOXX_REPORTE
```

y deberá **seguir el template proporcionado por la cátedra**.

---

## Competencia Kaggle

El trabajo práctico estará enmarcado en una competencia de Kaggle, donde todos los alumnos deberán participar. Para unirse a la misma deben acceder con el enlace de invitación y conformar los grupos correspondientes. Pueden elegir cualquier nombre que represente al equipo.

El objetivo de la competencia es clasificar reseñas de productos de Amazon en español según su sentimiento: negativa (0), neutra (1) o positiva (2). Para saber qué tan bien se desempeña un modelo, cada grupo hará su predicción sobre el conjunto de test y la subirá (*submit*) a **Kaggle**.

**Kaggle** verificará las predicciones contra el archivo de soluciones utilizando la **métrica F1 macro** y mostrará la posición del equipo en la tabla de puntajes (leaderboard). Pero sólo usará para ello el 50% de sus respuestas. El 50% restante se usará también para calcular su puntaje pero en un tablero privado que sólo pueden ver los docentes y que se revelará al finalizar la competencia **(23/06/2026 23:55hs)**.

---

## Enunciado

Los conjuntos de datos a utilizar (`train` y `test`) se encuentran disponibles en la competencia de Kaggle, donde también encontrarán un archivo de ejemplo de cómo se deben subir las soluciones. El trabajo consiste en construir diferentes modelos de clasificación, capaces de analizar una porción de texto en lenguaje natural y detectar el sentimiento allí presente en tres categorías: negativa (0), neutra (1) y positiva (2).

Para ello habrá que realizar un preprocesamiento del texto para que este pueda ser analizado por los distintos modelos. Se deberá explorar **al menos dos representaciones del texto**: *bag of words* y al menos una alternativa (por ejemplo: TF-IDF, embeddings con Word2Vec o FastText), comparando su impacto en el desempeño de los modelos.

Los modelos que se deben construir son los siguientes:

- Bayes Naïve
- Random Forest
- XGBoost
- Un modelo de red neuronal aplicando Keras, TensorFlow y/o PyTorch. Se recomienda explorar arquitecturas basadas en transformers, como **BETO** (BERT en español).
- Un ensamble de al menos 3 modelos elegidos por el grupo.

Para cada uno de estos modelos se debe realizar una búsqueda de hiperparámetros que optimicen su desempeño en el conjunto de evaluación local (porción del archivo training). Una vez encontrados dichos hiperparámetros, se procederá a hacer un *submission* a **Kaggle**. Es decir que habrá **al menos 5 submits por integrante del grupo** (uno por cada modelo).

---

## Reporte

En el reporte se debe explicar de forma clara y sintética los hiperparámetros escogidos para cada modelo. En el caso de la red neuronal, se debe indicar la arquitectura y explicar por qué se la eligió. Se deben indicar además las métricas obtenidas en el conjunto de datos de prueba local (porción del archivo training) y el puntaje obtenido en el tablero público de Kaggle.

---

## Fechas de entrega

La fecha final de entrega del trabajo práctico es el día **23 de junio de 2026**.

---

## Condiciones de Aprobación

- **Todos los integrantes** de los grupos deben participar de la competencia.
- Se debe tener **al menos 1 subida** por modelo/ensamble pedido.
- Todas las semanas, **cada uno de los integrantes del grupo** debe participar en la competencia realizando al menos una subida a Kaggle.
- Deben cumplir con todos los puntos del enunciado.
- Deben presentar el informe en las fechas estipuladas.
