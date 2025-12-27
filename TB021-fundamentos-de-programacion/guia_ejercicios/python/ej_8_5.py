def busqueda_binaria(lista, elemento):
    '''
    Recibe una lista ordenada y un elemento. 
    Si el elemento se encuentra en la lista, 
    debe encontrar su posición mediante búsqueda 
    binaria y devolverlo. Si no se encuentra, 
    debe agregarlo a la lista en la posición correcta 
    y devolver esa nueva posición
    '''
    inicio = 0
    fin = len(lista) - 1

    while inicio <= fin:
        medio = (inicio + fin) // 2
        if lista[medio] == elemento:
            return medio
        
        elif lista[medio] > elemento:
            fin = medio - 1

        elif lista[medio] < elemento:
            inicio = medio + 1

    lista.insert(medio, elemento)
  
    return medio

lista = [
    '1234', 
    '123456789', 
    'adlfjkb', 
    'dflkhj', 
    'gato', 
    'hola', 
    'juan', 
    'kask', 
    'lol',
    'mateo', 
    'milanesa', 
    'perro', 
    'qwerty'
]

resultado = busqueda_binaria(lista, "lol")
print(resultado)

'''resultado = busqueda_binaria(lista, "python")
print(resultado)'''