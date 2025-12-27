# Trabajo Práctico 1: Algoritmos Greedy en la Nación del Fuego

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
| `tp1.py`          | Implementación principal que contiene la función `minimizar_sumatoria`. |
| `parser.py`       | Función para leer los datasets y convertirlos a batallas. |
| `test_catedra.py` | Tests con los datasets de la cátedra. |
| `test.py`         | Generador de mediciones y gráficos. |
| `util.py`         | Funciones auxiliares |
| `datasets/`       | Carpeta con los datasets de la cátedra. |
| `mediciones/`       | Carpeta con los gráficos de mediciones. |
| `latex/`            | Carpeta con la estructura del informe en Latex |

## Como ejecutar el programa
```bash
python3 tp1.py ruta/a/entrada.txt
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