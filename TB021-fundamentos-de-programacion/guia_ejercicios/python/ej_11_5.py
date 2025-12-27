def rot13(file1, file2):
    '''
    Escribir una función, llamada rot13, que reciba un archivo de texto de origen
    y uno de destino, de modo que para cada línea del archivo origen, se guarde una
    línea cifrada en el archivo destino. El algoritmo de cifrado a utilizar será
    muy sencillo: a cada caracter comprendido entre la a y la z, se le suma 13 y
    luego se aplica el módulo 26, para obtener un nuevo caracter.
    '''
    
    with open(file1) as f1:
        with open(file2, "w") as f2:

            for linea in f1:
                linea_encriptada = ""

                for caracter in linea:
                    if 'a' <= caracter <= 'z':
                        caracter_encriptado = chr(((ord(caracter) - ord("a") + 13) % 26) + ord("a"))
                    elif 'A' <= caracter <= 'Z':
                        caracter_encriptado = chr(((ord(caracter) - ord("A") + 13) % 26) + ord("A"))
                    else:
                        caracter_encriptado = caracter
                    
                    linea_encriptada += caracter_encriptado
                
                f2.write(linea_encriptada)

