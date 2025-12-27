def sumar_matrices(m1, m2):
    # Recibe dos matrices y devuelve la suma
    filas = len(m1)
    columnas = len(m1[0])
    matriz = []

    for fila in range(filas):
        fila_matriz = []
        
        for columna in range(columnas):
            fila_matriz.append(m1[fila][columna] + m2[fila][columna])
        
        matriz.append(fila_matriz)

    return matriz

m1 = [
    [1, 2, 5],
    [3, 7, 2]
]

m2 = [
    [3, 5, 8],
    [6, 1, 1]
]

#matriz = sumar_matrices(m1, m2)
#print(matriz)

def multiplicar_matrices(m1, m2):
    # Recibe dos matrices y devuelve su multiplicacion
    #columnas_m1 == filas_m2
    filas_m1 = len(m1)
    columnas_m1 = len(m1[0])
    columnas_m2 = len(m2[0])
    matriz = []

    for fila_m1 in range(filas_m1):
        fila_matriz = []
        
        for columna_m2 in range(columnas_m2):
            producto = 0

            for columna_m1 in range(columnas_m1):
                print(f"{m1[fila_m1][columna_m1]} * {m2[columna_m1][columna_m2]}")
                producto += m1[fila_m1][columna_m1] * m2[columna_m1][columna_m2]
            
            fila_matriz.append(producto)
            
        matriz.append(fila_matriz)
    
    return matriz
                                    
m1 = [
    [1, 2,],
    [3, 4]
]

m2 = [
    [1, 2,],
    [3, 4]
]

#matriz = multiplicar_matrices(m1, m2)
#print(matriz)