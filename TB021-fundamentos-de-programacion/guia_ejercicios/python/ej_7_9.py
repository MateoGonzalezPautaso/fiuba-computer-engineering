def empaquetar_lista(lista):
    # Empaquetar significa indicar la repeticion de valores consecutivos mediante una tupla (valor, repeticiones)
    lista_empaquetada = []
    repeticiones = 1

    for i in range(0, len(lista)):
        tupla = (lista[i], repeticiones)

        if i == len(lista)-1:
            lista_empaquetada.append(tupla)

        elif lista[i] == lista[i+1]:
            repeticiones += 1
    
        else:
            lista_empaquetada.append(tupla)
            repeticiones = 1

    return lista_empaquetada

#lista_empaquetada = empaquetar_lista([1, 1, 1, 3, 5, 1, 1, 3, 3])
#print(lista_empaquetada)