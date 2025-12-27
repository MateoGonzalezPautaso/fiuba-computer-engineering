from parser import parser
from tp2 import maximizar_kills

def test_5():
    path_set = "./datasets/5.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 1413, "El resultado del dataset de n = 5 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 5.txt = {resultado}")

def test_10():
    path_set = "./datasets/10.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 2118, "El resultado del dataset de n = 10 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 10.txt = {resultado}")

def test_10bis():
    path_set = "./datasets/10_bis.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 1237, "El resultado del dataset de n = 10bis no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 10_bis.txt = {resultado}")

def test_20():
    path_set = "./datasets/20.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 11603, "El resultado del dataset de n = 20 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 20.txt = {resultado}")

def test_50():
    path_set = "./datasets/50.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 3994, "El resultado del dataset de n = 50 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 50.txt = {resultado}")

def test_100():
    path_set = "./datasets/100.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 7492, "El resultado del dataset de n = 100 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 100.txt = {resultado}")

def test_200():
    path_set = "./datasets/200.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 4230, "El resultado del dataset de n = 200 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 200.txt = {resultado}")

def test_500():
    path_set = "./datasets/500.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 15842, "El resultado del dataset de n = 500 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 500.txt = {resultado}")

def test_1000():
    path_set = "./datasets/1000.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 4508, "El resultado del dataset de n = 1000 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 1000.txt = {resultado}")

def test_5000():
    path_set = "./datasets/5000.txt"
    x, f = parser(path_set)
    resultado, _ = maximizar_kills(x, f)
    assert resultado == 504220, "El resultado del dataset de n = 5000 no coincide con la salida de catedra"
    print(f"Cantidad de tropas eliminadas 5000.txt = {resultado}")

if __name__ == "__main__":
    test_5()
    test_10()
    test_10bis()
    test_20()
    test_50()
    test_100()
    test_200()
    test_500()
    test_1000()
    test_5000()