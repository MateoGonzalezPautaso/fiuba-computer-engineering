def grep(file, cadena):
    '''
    Escribir una función, llamada grep, que reciba una cadena y un archivo
    de texto, e imprima las líneas del archivo que contienen la cadena recibida
    '''
    
    with open(file) as f:

        for linea in f:
            if cadena in linea:
                print(linea.rstrip("\n"))