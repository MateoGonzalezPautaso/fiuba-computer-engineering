def convertir_binarios(cadena):
    # Convierte una cadena binaria en un valor decimal
    decimal = 0
    i = 0
    for n in cadena[::-1]:
        if n == "1":
            decimal += 2 **(i)
        i += 1
    
    return decimal

decimal = convertir_binarios("100011")
#print(decimal)