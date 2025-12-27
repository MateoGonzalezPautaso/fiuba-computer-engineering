def letras_2(cadena):
    # Dada una cadena imprime los dos primeros caracteres
    print(cadena[:2])

letras_2("Hola que tal")

def ultimas_letras(cadena):
    # Dada una cadena imprime los tres ultimos caracteres
    print(cadena[-3:])

ultimas_letras("Hola que tal")

def saltear_caracteres(cadena):
    # Dada una cadena imprime cada dos caracteres
    print(cadena[::2])

saltear_caracteres("recta")

def sentido_inverso(cadena):
    # Dada una cadena imprime la cadena en sentido inverso
    print(cadena[::-1])

sentido_inverso("Hola mundo!")

def doble_sentido(cadena):
    # Dada una cadena imprime la cadena en sentido y en su inverso
    print(f"{cadena}{cadena[::-1]}")

doble_sentido("reflejo")