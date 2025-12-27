def es_primo(n):
    # Dado un numero entero n, indica si es primo o no
    for i in range(2, n+1):
        if n != i and n % i == 0:
            return False
    return True

def imprimir_primos(n):
    # Imprime todos los numeros primos hasta ese numero
    for i in range(2, n+1):
        if es_primo(i):
            print(i)
    
#imprimir_primos(50)