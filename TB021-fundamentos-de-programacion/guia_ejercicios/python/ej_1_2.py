# from archivo import funcion
from ej_1_1 import producto_numeros
# import archivo
# import ej_1_1

def main():
    n1 = int(input("Ingrese el numero 1: "))
    n2 = int(input("Ingrese el numero 2: "))

    print(f"El resultado del producto de {n1} y {n2} es: {producto_numeros(n1, n2)}")
    #print(f"El resultado del producto de {n1} y {n2} es: {ej_1_1.producto_numeros(n1, n2)}")

main()