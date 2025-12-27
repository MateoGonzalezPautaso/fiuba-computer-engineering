def posiciones_de(a, b):
    return _posiciones_de(a, b, 0, [])

def _posiciones_de(a, b, inicio, posiciones):
    if inicio > len(a) - len(b):
        return posiciones
    
    if a[inicio : inicio+len(b)] == b:
        posiciones.append(inicio)

    return _posiciones_de(a, b, inicio + 1, posiciones)

def posiciones_de(a,b, indice=0):
    if len(a) == 0:
        return []
    if a[:len(b)] == b:
        return [indice] + posiciones_de(a[1:],b,indice + 1)
    else:
        return posiciones_de(a[1:],b,indice + 1)