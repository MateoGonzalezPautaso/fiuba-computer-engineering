import struct

FORMATO = ">i3sf" # Big Endian, signed 32-bit, len(string) = 3, floating point single precision

def guardar(estudiantes, ruta):

    with open(ruta, "wb") as archivo:

        for padron, iniciales, promedio in estudiantes:

            contenido = struct.pack(FORMATO, padron, iniciales.encode(), promedio) # paso el str a bytes
            archivo.write(contenido)


def cargar(ruta):

    estudiantes = []

    with open(ruta, "rb") as archivo:

        while True:

            cantidad = struct.calcsize(FORMATO)
            contenido = archivo.read(cantidad)

            if len(contenido) == 0:
                break

            padron, iniciales, promedios = struct.unpack(FORMATO, contenido)
            iniciales = iniciales.decode()
            estudiantes.append((padron, iniciales, promedios))

    return estudiantes

