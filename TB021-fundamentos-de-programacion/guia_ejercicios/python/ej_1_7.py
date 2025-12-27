# Funcion que pide una palabra al usuario y la imprime 1000 veces, en una unica linea con espacios
def imprimir_1000():
    palabra = input("Ingrese una palabra: ")
    for i in range(1, 1001):
        print(palabra, end=" ")

imprimir_1000()