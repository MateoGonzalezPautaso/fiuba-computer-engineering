def combinaciones(caracteres, k, cadena_actual=''):
    if len(cadena_actual) == k:
        print(cadena_actual)
        return
    
    for char in caracteres:
        combinaciones(caracteres, k, cadena_actual + char)