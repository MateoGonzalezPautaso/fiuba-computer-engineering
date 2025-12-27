from parser import parser
from algoritmos.algortimo_pl import tribu_del_agua_pl

def test_5_2():
    archivo = '5_2.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 1894340
    print(f"Coeficiente de {archivo}: {resultado}")

def test_6_3():
    archivo = '6_3.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 1640690, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_6_4():
    archivo = '6_4.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 807418, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_8_3():
    archivo = '8_3.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 4298131, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_10_3():
    archivo = '10_3.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 385249, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_10_5():
    archivo = '10_5.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 355882, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_10_10():
    archivo = '10_10.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 172295, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_11_5():
    archivo = '11_5.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 2906564, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_14_3():
    archivo = '14_3.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 15659106, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_14_4():
    archivo = '14_4.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 15292055, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_14_6():
    archivo = '14_6.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 10694510, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_15_4():
    archivo = '15_4.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 4311889, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_15_6():
    archivo = '15_6.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 6377225, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_17_5():
    archivo = '17_5.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 15974095, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_17_7():
    archivo = '17_7.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 11513230, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_17_10():
    archivo = '17_10.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 5427764, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_18_6():
    archivo = '18_6.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 10322822, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_18_8():
    archivo = '18_8.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 11971097, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_20_4():
    archivo = '20_4.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 21081875, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_20_5():
    archivo = '20_5.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 16828799, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

def test_20_8():
    archivo = '20_8.txt'
    path_set = f"./datasets/{archivo}"
    x, f = parser(path_set)
    _, resultado = tribu_del_agua_pl(x, f)
    assert resultado == 11417428, f"El resultado del dataset {archivo} no coincide con la salida de catedra"
    print(f"Coeficiente de {archivo}: {resultado}")

if __name__ == "__main__":
    test_5_2()
    test_6_3()
    test_6_4()
    test_8_3()
    test_10_3()
    test_10_5()
    test_10_10()
    test_11_5()
    test_14_3()
    test_14_4()
    test_14_6()
    test_15_4()
    test_15_6()
    test_17_5()
    test_17_7()
    test_17_10()
    test_18_6()
    test_18_8()
    test_20_4()
    test_20_5()
    test_20_8()