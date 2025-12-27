def devolver_valores(lista_numeros):
    '''
    Recibe una lista de numeros no ordenada, devuelve su
    valor maximo y una tupla que incluya el valor maximo
    con su posicion
    '''
    maximo = max(lista_numeros)
    tupla = (maximo, lista_numeros.index(maximo))

    return maximo, tupla

lista = [1, 3, 5, 7, 4, 3, 6, 9, 8, 0, 7, 4, 6, 3]

maximo, tupla = devolver_valores(lista)
#print(maximo, tupla)