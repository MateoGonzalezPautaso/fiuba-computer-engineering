def guardar_diccionario(diccionario, ruta):
    '''
    Escribir una función guardar_diccionario que reciba un diccionario y una ruta, y
    guarde el contenido del diccionario en el archivo, en modo texto, escribiendo un
    par clave-valor por línea con el formato clave,valor.
    '''

    with open(ruta, "w") as file:
        for key, values in diccionario.items():
            for value in values:
                file.write(f"{key}, {value}\n")

def cargar_diccionario(ruta):
    '''
    Escribir una función cargar_diccionario que reciba una ruta a un archivo con el
    formato anterior y devuelva el diccionario cargado
    '''

    diccionario = {}
    with open(ruta) as file:
        for linea in file:
            linea = linea.strip()
            key, value = linea.split(",")
            if key not in diccionario:
                diccionario[key] = []
            diccionario[key].append(value)
        
        return diccionario
