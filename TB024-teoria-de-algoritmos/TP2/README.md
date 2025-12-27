# Trabajo Práctico 2: Programación Dinámica para el Reino de la Tierra

## Integrantes
+ **Agustín Bermudez**  
  - Padrón: 111863  
  - Mail: abermudez@fi.uba.ar  
+ **Tiago Calderón**  
  - Padrón: 111894  
  - Mail: tcalderon@fi.uba.ar  
+ **Mateo Gonzalez Pautaso**  
  - Padrón: 111699  
  - Mail: magonzalezp@fi.uba.ar  


## Estructura del repositorio

| Archivo / Carpeta | Descripción |
|-------------------|-------------|
| `tp2.py`          | Implementación principal que contiene la función `maximizar_kills`. |
| `analizador_optimalidad.py`          | Implementación por Backtracking de la función `maximizar_kills`. |
| `parser.py`       | Función para leer los datasets y convertirlos a ráfagas y fuerza acumulada. |
| `test_catedra.py` | Tests con los datasets de la cátedra. |
| `test.py`         | Generador de mediciones y gráficos. |
| `util.py`         | Funciones auxiliares |
| `datasets/`       | Carpeta con los datasets de la cátedra. |
| `mediciones/`       | Carpeta con los gráficos de mediciones. |
| `latex/`            | Carpeta con la estructura del informe en Latex |

## Como ejecutar el programa con un .txt como dataset
```bash
python3 tp2.py ruta/a/entrada.txt
```

## Como ejecutar el programa con funciones generadoras de datasets
```bash
python3 tp2.py
```

## Como ejecutar los test de salida de cátedra
```bash
python3 test_catedra.py
```

## Requisitos necesarios para generar los gráficos de mediciones
```bash
pip install numpy scipy matplotlib
python3 test.py
```
