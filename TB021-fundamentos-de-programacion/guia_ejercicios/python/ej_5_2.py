def es_primo(n):
    # Dado un numero entero n, indica si es primo o no
    for i in range(2, n+1):
        if n != i and n % i == 0:
            return False
    return True

def factores_primos(k):
    # Recibe un numero entero k e imprime su descomposicion en factores primos
    while (k != 1):
        for i in range(2, k+1):
            if es_primo(i) and k % i == 0:
                print(f"{k} / {i}: ", end="")
                k = k // i
                print(k)
                break
            
factores_primos(24)