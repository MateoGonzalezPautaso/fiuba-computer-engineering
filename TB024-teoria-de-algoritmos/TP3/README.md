# Trabajo Práctico 3: Problemas NP-Completos para la defensa de la Tribu del Agua

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
| `tp3.py`          | Implementación principal que contiene la función principal y un comparador de los aproximadores. |
| `parser.py`       | Función para leer los datasets y convertirlos a un formato válido. |
| `test_catedra.py` | Tests con los datasets de la cátedra. |
| `test.py`         | Generador de mediciones y gráficos. |
| `evaluador_aprox.py`         | Generador de mediciones y gráficos para la comparar aproximadores. |
| `util.py`         | Funciones auxiliares |
| `datasets/`       | Carpeta con los datasets de la cátedra. |
| `mediciones/`       | Carpeta con los gráficos de mediciones. |
| `latex/`            | Carpeta con la estructura del informe en Latex |
| `algoritmos/`      | Carpeta con los algoritmos principales del TP

## Como ejecutar el programa con un .txt como dataset
```bash
python3 tp3.py ruta/a/entrada.txt
```

## Como ejecutar los test de salida de cátedra
```bash
pytest test_catedra.py
```

## Requisitos necesarios para generar los gráficos de mediciones
```bash
pip install numpy scipy matplotlib
python3 test.py
```