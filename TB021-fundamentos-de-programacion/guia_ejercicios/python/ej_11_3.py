def wc(file):
    '''
    Escribir una función, llamada wc, que dado un archivo de texto, lo procese e imprima
    por pantalla cuántas líneas, cuantas palabras y cuántos caracteres contiene el archivo
    '''
    
    with open(file) as f:    

        n_lineas = 0
        n_palabras = 0
        n_caracteres = 0

        for linea in f:
            n_lineas += 1
            palabras = linea.split(" ")
            n_palabras += len(palabras)
            n_caracteres += len(linea)
        
        print(f"Cantidad de líneas: {n_lineas}")
        print(f"Cantidad de palabras: {n_palabras}")
        print(f"Cantidad de caracteres: {n_caracteres}")