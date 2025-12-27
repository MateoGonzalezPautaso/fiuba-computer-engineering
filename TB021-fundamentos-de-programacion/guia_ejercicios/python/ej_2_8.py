from ej_1_5 import n_factorial

# Programa que toma una cantidad m de valores y le calcula el factorial
def main():
    ingreso = input("Ingrese un numero para calcularle el factorial: ")
    i = 0
    while (ingreso != "exit"):
        factorial = n_factorial(int(ingreso))
        print(f"{factorial} - {i}")
        i += 1
        ingreso = input("Escriba 'exit' para salir o ingrese otro numero: ")

main()