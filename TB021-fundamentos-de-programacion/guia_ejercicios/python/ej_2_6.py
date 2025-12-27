# Programa que imprime todos los numeros pares entre dos numeros pedidos al usuario
def main():
    n1 = int(input("Ingrese el primer numero: "))
    n2 = int(input("Ingrese el segundo numero: "))
    for numero in range(n1, n2 + 1):
        if (numero % 2 == 0):
            print(numero)

main()