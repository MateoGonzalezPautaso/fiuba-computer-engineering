def cp(file1, file2):
    '''
    Escribir una función, llamada cp, que copie todo el contenido de un archivo
    (sea de texto o binario) a otro, de modo que quede exactamente igual
    '''
    
    with open(file1) as f1:
        contenido = f1.read()
        with open(file2, "w") as f2:
            f2.write(contenido)

cp("test.txt", "test_cp.txt")


def cp(ruta_origen, ruta_destino):
    with open(ruta_origen, "rb") as origen, open(ruta_destino, "wb") as destino:
        contenido = origen.read(1024) # cantidad de bytes a leer 1kB

        while len(contenido) > 0:
            destino.write(contenido)
            contenido = origen.read(1024)