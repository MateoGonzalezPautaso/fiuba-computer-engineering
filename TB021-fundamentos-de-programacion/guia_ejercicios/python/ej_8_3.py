def agenda(cadena, lista_tuplas):
    '''
    Recibe una cadena a buscar en la lista de tuplas y
    devuelve una lista con todas las coincidencias
    '''
    lista_coincidencias = []

    for tupla in lista_tuplas:
        if cadena in tupla[0]:
            lista_coincidencias.append(tupla)

    return lista_coincidencias

cadena = "ate"
lista_tuplas = [
    ("Mate Gonzalez", 18394),
    ("Juan Mateo Perez", 34587),
    ("Bernardo Gutierrez", 456879),
    ("Juan Benavidez", 8765)
]

lista_coincidencias = agenda(cadena, lista_tuplas)
#print(lista_coincidencias)