def separar_miles(n):
    # Recibe una cadena y separa el numero en miles
    cadena_nueva = ""
    numero = int(n)
    while numero >= 1000:
        resto = numero % 1000
        cadena_nueva = "." + str(resto) + cadena_nueva
        numero = numero // 1000
    
    cadena_nueva = str(numero) + cadena_nueva
    return cadena_nueva

cadena_nueva = separar_miles("1234567890")
#print(cadena_nueva)