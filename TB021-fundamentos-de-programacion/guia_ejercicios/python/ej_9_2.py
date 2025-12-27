def diccionario_apariciones(cadena):
    '''
    Escribir una función que reciba una cadena y devuelva un diccionario con
    la cantidad de apariciones de cada palabra en la cadena
    '''
    diccionario = {}
    lista = cadena.lower().split(" ")

    for palabra in lista:

        #diccionario[palabra] = diccionario.get(palabra, 0) + 1

        if palabra not in diccionario:
            diccionario[palabra] = 1

        else:
            diccionario[palabra] += 1

    return diccionario

cadena = "Que lindo dia que hace hoy"
diccionario = diccionario_apariciones(cadena)


def diccionario_caracteres(cadena):
    '''
    Escribir una función que cuente la cantidad de apariciones de cada
    caracter en una cadena de texto, y los devuelva en un diccionario.
    '''
    diccionario = {}
    lista = list(cadena.lower().replace(" ", ""))
    
    for caracter in lista:

        if caracter not in diccionario:
            diccionario[caracter] = 1

        else:
            diccionario[caracter] += 1

    return diccionario

cadena = "Que lindo dia que hace hoy"
diccionario = diccionario_caracteres(cadena)


import random

def diccionario_dados(iteraciones):
    '''
    Escribir una función que reciba una cantidad de iteraciones de una
    tirada de 2 dados a realizar y devuelva la cantidad de veces que se
    observa cada valor de la suma de los dos dados.
    '''
    diccionario = {}

    for i in range(iteraciones):

        dado1 = random.randint(1, 6)
        dado2 = random.randint(1, 6)
        suma = dado1 + dado2

        if suma not in diccionario:
            diccionario[suma] = 1

        else:
            diccionario[suma] += 1

    return diccionario

iteraciones = random.randint(5, 10)
diccionario = diccionario_dados(iteraciones)