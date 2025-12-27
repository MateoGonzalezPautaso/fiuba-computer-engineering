def algoritmo_euclides(n, m):
    # Algoritmo de Euclides para calcular el maximo comun divisor de dos numeros
    if n > m:
        m, n = n, m

    r = m % n

    while r != 0:
        m, n = n, r
        r = m % n

    return n

def main():
    assert algoritmo_euclides(15,9) == 3
    assert algoritmo_euclides(9, 15) == 3
    assert algoritmo_euclides(10, 8) == 2
    assert algoritmo_euclides(12, 6) == 6

main()