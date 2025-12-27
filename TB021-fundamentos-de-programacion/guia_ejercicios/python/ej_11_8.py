def leer_imagen_txt(matriz, file):
    '''
    Escribir una función que reciba una matriz y un archivo, y
    guarde el contenido de la matriz en el archivo, en modo texto
    '''

    with open(file, "w") as archivo:

        for fila in range(len(matriz)):
            for columna in range(len(matriz[0])):

                if matriz[fila][columna] == True:
                    archivo.write("B")
                else:
                    archivo.write("N")

            if fila < len(matriz) - 1:
                archivo.write("\n")


def escribir_imagen_txt(file):
    '''
    Escribir una función que reciba un archivo y
    devuelva la matriz cargada
    '''

    matriz = []

    with open(file) as archivo:

        for linea in archivo:
            fila = []
            for caracter in linea.strip():

                if caracter == "B":
                    fila.append(True)
                else:
                    fila.append(False)

            matriz.append(fila)
    
        return matriz


matriz = [
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True]
]

leer_imagen_txt(matriz, "imagen_NB.txt")

matriz = escribir_imagen_txt("imagen_NB.txt")
print(matriz)



def leer_imagen_bin(matriz, file):
    '''
    Escribir una función que reciba una matriz y un archivo, y
    guarde el contenido de la matriz en el archivo, en modo binario
    '''

    with open(file, "w") as archivo:

        for fila in range(len(matriz)):
            for columna in range(len(matriz[0])):

                if matriz[fila][columna] == True:
                    archivo.write("1")
                else:
                    archivo.write("0")

            if fila < len(matriz) - 1:
                archivo.write("\n")


def escribir_imagen_bin(file):
    '''
    Escribir una función que reciba un archivo binario
    y devuelva la matriz cargada
    '''

    matriz = []

    with open(file) as archivo:

        for linea in archivo:
            fila = []
            for caracter in linea.strip():

                if caracter == "1":
                    fila.append(True)
                else:
                    fila.append(False)

            matriz.append(fila)
    
        return matriz


matriz = [
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True],
    [True, False, True, False, True, False, True, False],
    [False, True, False, True, False, True, False, True]
]

leer_imagen_bin(matriz, "imagen_01.txt")

matriz = escribir_imagen_bin("imagen_01.txt")
print(matriz)