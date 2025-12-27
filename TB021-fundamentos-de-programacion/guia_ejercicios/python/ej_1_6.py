# Funcion que dados dos numeros, devuelve la suma, resta, division y multiplicación
def calculos(n1, n2):
    suma = (n1 + n2)
    resta = (n1 - n2)
    division = (n1 / n2)
    multiplicación = (n1 * n2)
    print(f"Suma = {suma}, Resta = {resta}, Division = {division}, Multiplicacion = {multiplicación}")

# Funcion que dado un numero natural n, imprime su tabla de multiplicar
def tabla_multiplicar(n):
    for i in range(1, 11):
        print(f"{n} * {i} = {n * i}")

calculos(32, 8)
tabla_multiplicar(5)