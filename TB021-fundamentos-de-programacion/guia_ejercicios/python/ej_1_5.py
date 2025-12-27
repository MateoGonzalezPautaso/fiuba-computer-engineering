# Funcion que dado un numero n, nos permite calcular n!
def n_factorial(n):
    for i in range(1, n): # sino (n-1, 1, -1)
        n *= i
    return n

n = n_factorial(5)
#print(n)