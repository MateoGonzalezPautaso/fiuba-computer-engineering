def tupla_ordenada(tupla):
    # Recibe una tupla e indica si esta ordenada de menor a mayor
    tupla_ordenada = tuple(sorted(tupla))
    return tupla == tupla_ordenada

resultado = tupla_ordenada((1, 5, 9, 3))
#print(resultado)