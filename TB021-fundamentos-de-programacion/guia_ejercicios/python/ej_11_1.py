def head(file, n):
    '''
    Escribir una función, llamada head que reciba un archivo 
    y un número N e imprima las primeras N líneas del archivo
    '''

    with open(file) as lineas:

        for linea in lineas:
            print(linea.rstrip('\n'))
            n = n-1
            if n == 0:
                return

head("test.txt", 5)