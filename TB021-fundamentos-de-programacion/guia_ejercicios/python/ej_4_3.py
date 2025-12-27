def matriz_identidad(n):
    # Imprime la matriz identidad de la dimension n
    print(n)
    for fila in range(n):
        for columna in range(n):
            if fila == columna:
                print("1", end=" ")
            else:
                print("0", end=" ")
        print()

matriz_identidad(9)