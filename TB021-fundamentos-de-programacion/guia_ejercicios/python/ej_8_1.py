def buscar_elemento(lista, elemento):
    '''
    Busca todos los elementos que coincidan con el pasado por 
    parametro, devuelve la cantidad de coincidencias encontradas,
    la posicion del primer elemento y una lista con las posiciones
    '''

    repeticiones = 0
    lista_posiciones = []
    for i in range(len(lista)):
        if lista[i] == elemento:
            repeticiones += 1
            posicion = lista.index(lista[i])
            lista_posiciones.append(i)

    return repeticiones, posicion, lista_posiciones

lista = [1, 3, 5, 7, 4, 3, 6, 9, 8, 0, 7, 4, 6, 3]
elemento = 7

repeticiones, posicion, lista_posiciones = buscar_elemento(lista, elemento)
#print(repeticiones, posicion, lista_posiciones)