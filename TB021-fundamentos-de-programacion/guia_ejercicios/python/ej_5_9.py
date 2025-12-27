def contar_multiplos(n1, n2):
    # Devuelve cuantos multiplos del primero hay menores al segundo
    i = 0
    for n in range(1, n2):
        if n1 % n == 0:
            print(n)
            i += 1
    print(f"Hay {i} multiplos de {n1}, menores a {n2}")

contar_multiplos(250, 100)