def devolver_consonantes(cadena):
    # Devuelve solo las consonantes de palabras
    cadena_nueva = ""
    for i in range(0, len(cadena)):
        if cadena[i].upper() not in ["A", "E", "I", "O", "U"]:
            cadena_nueva += cadena[i]

    return cadena_nueva

cadena_nueva = devolver_consonantes("algoritmos")
#print(cadena_nueva)

def devolver_vocales(cadena):
    # Devuelve solo las vocales de palabras
    cadena_nueva = ""
    for i in range(0, len(cadena)):
        if cadena[i].upper() in ["A", "E", "I", "O", "U", " "]:
            cadena_nueva += cadena[i]

    return cadena_nueva

cadena_nueva = devolver_vocales("sin consonantes")
#print(cadena_nueva)

def cambiar_vocal(cadena):
    vocales = ["a", "e", "i", "o", "u", "a", "A", "E", "I", "O", "U", "A"]
    cadena_nueva  = ""
    
    for letra in cadena:
        
        if letra in vocales:
            posicion = vocales.index(letra)
            vocal_siguiente = vocales[-len(vocales) + 1 + posicion]
            cadena_nueva += vocal_siguiente
        else:
            cadena_nueva += letra

    return cadena_nueva

cadena_nueva = cambiar_vocal("vestuario")
#print(cadena_nueva)

def palindromo(cadena):
    # Indica si se trata de un palindromo
    cadena_nueva = cadena.replace(" ", "").lower()
    if cadena_nueva == cadena_nueva[::-1]:
        print(f"{cadena} | es un palindromo")
    else:
        print(f"{cadena} | no es un palindromo")

palindromo("anita lava la tina")