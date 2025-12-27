def producto_escalar(v1, v2):
    # Recibe dos vectores y devuelve su producto escalar
    producto_escalar = 0

    for i in range(0, len(v1)):
        producto_escalar += (v1[i] * v2[i])

    return producto_escalar 

#print(producto_escalar([1, 4], [3, 9]))
#print(producto_escalar([1, 4, 1], [3, 9, 1]))

def ser_ortogonales(v1, v2):
    # Recibe dos vectores y devuelve su producto escalar
    producto_escalar = 0
    for i in range(0, len(v1)):
        producto_escalar += (v1[i] * v2[i])
    
    return producto_escalar == 0

#print(ser_ortogonales([1, 0], [0, 9]))
#print(ser_ortogonales([1, 4, -1], [3, 9, 39]))
#print(ser_ortogonales([1, 0], [8, 9]))
#print(ser_ortogonales([1, 4, -1], [3, 9, 8]))

def ser_paralelos(v1, v2):
    # Recibe dos vectores y devuelve si son paralelos
    x = v1[0] / v2[0]
    for i in range(1, len(v1)):
        if x != v1[i] / v2[i]:
            return False
    
    return True

#print(ser_paralelos([1, 2], [2, 4]))
#print(ser_paralelos([1, 2, 8], [2, 4, 16]))
#print(ser_paralelos([1, 3], [2, 4]))
#print(ser_paralelos([1, 9, 8], [2, 4, 16]))

def devolver_norma(v1):
    # Recibe un vector y devuelve su norma
    norma = 0
    for i in range(0, len(v1)):
        norma += v1[i] **2
    
    return norma **(1/2)

#print(devolver_norma([1, 2]))
#print(devolver_norma([3, 2]))
#print(devolver_norma([1, 2, 9]))
#print(devolver_norma([1, 2, 4]))