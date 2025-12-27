from parser import parser
from tp1 import minimizar_sumatoria

def test_10():
    path_set = "./datasets/10.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 309600, "El resultado del dataset de 10 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 10.txt = {resultado}")

def test_50():
    path_set = "./datasets/50.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 5218700, "El resultado del dataset de 50 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 50.txt = {resultado}")

def test_100():
    path_set = "./datasets/100.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 780025365, "El resultado del dataset de 100 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 100.txt = {resultado}")

def test_1000():
    path_set = "./datasets/1000.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 74329021942, "El resultado del dataset de 1000 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 1000.txt = {resultado}")

def test_5000():
    path_set = "./datasets/5000.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 1830026958236, "El resultado del dataset de 5000 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 5000.txt = {resultado}")

def test_10000():
    path_set = "./datasets/10000.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 7245315862869, "El resultado del dataset 10000 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 10000.txt = {resultado}")

def test_100000():
    path_set = "./datasets/100000.txt"
    batallas = parser(path_set)
    resultado = minimizar_sumatoria(batallas)
    assert resultado == 728684685661017, "El resultado del dataset de 100000 batallas no coincide con la salida de catedra"
    print(f"Coeficiente de impacto 100000.txt = {resultado}")

if __name__ == "__main__":
    test_10()
    test_50()
    test_100()
    test_1000()
    test_5000()
    test_10000()
    test_100000()