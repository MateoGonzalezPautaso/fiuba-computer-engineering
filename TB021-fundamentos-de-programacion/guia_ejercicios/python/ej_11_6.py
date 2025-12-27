def guardar_numeros(lista, ruta):
    '''
    Escribir una función guardar_numeros que reciba la lista y una ruta, y guarde el
    contenido de la lista en el archivo, en modo texto, escribiendo un número por línea
    '''

    with open(ruta, "w") as file:
        for numero in lista:
            file.write(str(numero))

def cargar_numeros(ruta):
    '''
    Escribir una función cargar_numeros que reciba una ruta a un archivo con el
    formato anterior y devuelva la lista de números cargada
    '''

    with open(ruta) as file:
        lista = []
        for numero in file:
            lista.append(numero)

        return lista


import struct

def guardar_numeros(ruta_destino, numeros):

    with open(ruta_destino, "wb") as destino:

        for n in numeros:

            contenido = struct.pack(">i", 113) # 133 es el numero a empaquetar
            destino.write(contenido)

def cargar_numeros(ruta_destino):

    numeros = []

    with open(ruta_destino, "rb") as archivo:

        while True:
            contenido = archivo.read(4)

            if len(contenido) == 0:
                break
            
            n = struct.unpack(">i", contenido)

            numeros.append(n[0])

    return numeros