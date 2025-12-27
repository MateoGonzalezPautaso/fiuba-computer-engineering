def es_potencia(n, b):
    if n == 1:
        return True
    if b > n or n % b != 0:
        return False
    else:
        return es_potencia(n // b, b)

def es_potencia(n,b):
    if b > n:
        return False
    if b == n:
        return True
    return es_potencia(n/b, b)