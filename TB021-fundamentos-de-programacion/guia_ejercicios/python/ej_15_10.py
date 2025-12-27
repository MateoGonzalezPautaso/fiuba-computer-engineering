def tiene_mas_letra_a(cadena):
    cant_a = 0
    cant_b = 0
    return _tiene_mas_letra_a(cadena, cant_a, cant_b)

def _tiene_mas_letra_a(cadena, cant_a, cant_b):
    if len(cadena) == 0:
        return cant_a > cant_b
    elif cadena[0].lower() == "a":
        cant_a += 1
    elif cadena[0].lower() == "e":
        cant_b += 1
    
    return _tiene_mas_letra_a(cadena[1:], cant_a, cant_b)