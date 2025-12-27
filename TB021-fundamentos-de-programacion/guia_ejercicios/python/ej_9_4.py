def diccionario_caracter(texto):
    '''
    Escribir una función que reciba un texto y para cada caracter presente en 
    el texto devuelva la cadena más larga en la que se encuentra ese caracter
    '''
    diccionario = {}

    palabras = texto.lower().split(" ")

    for palabra in palabras:
        for caracter in palabra:

            if caracter not in diccionario:
                diccionario[caracter] = caracter

            if len(palabra) > len(diccionario[caracter]):
                diccionario[caracter] = palabra

    return diccionario

texto = "Que elefante"
diccionario = diccionario_caracter(texto)
print(diccionario)