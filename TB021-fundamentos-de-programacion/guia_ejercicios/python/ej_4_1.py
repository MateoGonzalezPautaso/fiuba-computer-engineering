def es_par(n):
    # Dado un numero entero n, indica si es par o no
    return n % 2 == 0

def es_primo(n):
    # Dado un numero entero n, indica si es primo o no
    for i in range(2, n+1):
        if n != i and n % i == 0:
            return False
    return True

assert es_par(2) == True
assert es_par(10) == True
assert es_par(15) == False
assert es_primo(2) == True
assert es_primo(27) == False
assert es_primo(37) == True