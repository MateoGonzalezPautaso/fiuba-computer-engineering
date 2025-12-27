import os

EXTENSION_ARCHIVOS = ".txt"
CARACTERES_ESPECIALES = [",", "!", "¡", "#", "$", "%", "&", "?", "¿", "°", "+", "*", "~", ":", ".", "_", "@", ";", "^", "=", "[", "]", "{", "}", "<", ">"]


def obtener_archivos_con_rutas(ruta_directorio, archivos):
    '''
    La funcion recorre el directorio dado, arma una lista con los archivos y luego los de extension txt los guarda en un diccionario
    con el nombre del archivo y su clave, en caso de error devuelve un booleano indicando que fallo.
    PRECONDICIONES:
        - La ruta del directorio es una ruta valida ingresada por el usuario
    POSTCONDICIONES:
        - Devuelve un diccionario de archivos txt con clave nombre y valor el contenido
    '''
    archivos_txt = {} # armo un diccionario con "nombre_archivo": "ruta" para archivos txt

    for archivo in archivos: # recorro los nombres de la lista de nombres de archivos
        ruta_archivo = os.path.join(ruta_directorio, archivo) # obtengo la ruta del archivo

        if archivo.endswith(EXTENSION_ARCHIVOS): # si el archivo termina con la extension solicitada, lo asigna en el diccionario
            archivos_txt[archivo] = ruta_archivo # añado la clave, valor al diccionario

    return archivos_txt


def leer_lineas_archivo(diccionario_archivos_rutas):
    '''
    La funcion recorre cada ruta de los archivos del diccionario y lee el contenido de los mismos pasandolo por
    la funcion limpiar_texto, intercambiando la ruta por una lista de palabras limpias
    PRECONDICIONES:
        - diccionario_archivos_rutas es un diccionario con clave: nombre_archivo y valor: ruta_archivo
    POSTCONDICIONES:
        - diccionario_archivos_rutas es un diccionario con clave: nombre_archivo y valor: lista_lineas_limpias
    '''
    for nombre_archivo, ruta_archivo in diccionario_archivos_rutas.items(): # recorro las clave, valor de los archivos txt
        with open(ruta_archivo, "r") as archivo:
            lista_lineas_limpias = []

            for linea in archivo: # recorro las lineas del archivo
                linea.strip() # Para quitar \n de lineas vacias
                if not linea: # si la linea esta vacia, la saltea
                    continue

                linea = limpiar_texto(linea) # lista con la linea ya limpia
                lista_lineas_limpias += linea # sumo la linea a la lista de lineas

            diccionario_archivos_rutas[nombre_archivo] = lista_lineas_limpias # sustituyo la ruta por la lista de lineas limpias

    return diccionario_archivos_rutas


def limpiar_texto(texto):
    '''
    La funcion recibe una linea de un archivo de texto y remueve los espacios, convierte todo a minuscula e intercambia los
    caracteres especiales por caracteres vacios
    PRECONDICIONES:
        - texto es una linea valida de un archivo de texto
    POSTCONDICIONES:
        - texto es una lista de palabras limpias para poder ser procesada
    '''
    texto = texto.strip() # quito los saltos de linea del texto
    texto = texto.lower() # paso todo el texto a minuscula
    texto = texto.split(" ") # armo una lista de palabras

    for i in range(len(texto)):
        for caracter in CARACTERES_ESPECIALES:
            texto[i] = texto[i].replace(caracter, "") # reemplazo los caracteres especiales por caracteres vacios

    return texto


def armar_ngrama(diccionario_archivo_contenido, n):
    '''
    La funcion recibe un diccionario y un N entero para poder armar las tuplas de ngramas
    PRECONDICIONES:
        - diccionario_archivo_contenido es un diccionario valido con clave: nombre_archivo y valor: lista_lineas_limpias y
        n es un numero entero entre 2 y 9
    POSTCONDICIONES:
        - diccionario_archivo_contenido es un diccionario con clave: nombre_archivo y valor: {ngramas}
    '''
    for nombre_archivo, contenido in diccionario_archivo_contenido.items(): # recorro las clave, valor de los archivos txt
        ngrama = {} # armo un diccionario para guardar el ngrama

        while True:
            cantidad_palabras = len(contenido) # analizo el largo de la lista contenido

            if cantidad_palabras < n: # si la cantidad de elementos es menor a n, corto la ejecucion
                break

            clave_ngrama = contenido[:n] # asigno los n elementos que van a ser clave del diccionario
            tupla = tuple(clave_ngrama) # lo convierto a tupla para que pueda ser clave del diccionario

            if tupla not in ngrama: # si la clave no esta, la creo y asigno 1 como primera repeticion
                ngrama[tupla] = 1
            else: # si ya esta, le sumo 1
                ngrama[tupla] += 1

            contenido.pop(0) # saco el primer elemento de la lista

        diccionario_archivo_contenido[nombre_archivo] = ngrama # sustituyo la lista de lineas limpias por el ngrama

    return diccionario_archivo_contenido


def calcular_similaridad_jaccard(ngrama_A, ngrama_B):
    '''
    La funcion recibe dos ngramas y calcula las intersecciones entre los mismos junto a la cantidad de ngramas entre ambos, luego
    mediante el indice de Jaccard devuelve un valor entre 0 y 1, que multiplicado por 100 es un porcentaje
    PRECONDICIONES:
        - ngrama_A y ngrama_B son diccionarios validos con clave: tupla_n_elementos y valor: repeticiones
    POSTCONDICIONES:
        - similaridad es un porcentaje de numero flotante con 3 digitos de precision valido entre 0 y 100
    '''
    ngramas_compartidos = 0 # interseccion de ambos ngramas

    for ngrama, repeticiones_A in ngrama_A.items():
        if ngrama in ngrama_B: # si tienen la tupla en comun
            repeticiones_B = ngrama_B[ngrama]
            ngramas_compartidos += repeticiones_A + repeticiones_B # sumo los valores de la clave en comun de los diccionarios de ambos ngramas

    ngramas_totales = sum(ngrama_A.values()) + sum(ngrama_B.values()) # sumo los valores de las claves de los diccionarios de ambos ngramas

    similaridad = (ngramas_compartidos / ngramas_totales) * 100 # multiplico el indice (entre 0 y 1) por 100 para obtener porcentaje
    similaridad = round(similaridad, 3) # Uso el round para redondear el numero float a la precision elegida.

    return similaridad


def obtener_documentos_plagiados(diccionario_archivo_ngrama):
    '''
    La funcion recorre diccionario_archivo_ngrama y utilizando la funcion calcular_similaridad_jaccard verifica que
    archivos son plagios uno del otro, guardandolos en una lista
    PRECONDICIONES:
        - diccionario_archivo_ngrama es un diccionario valido con clave: nombre_archivo y valor: ngramas
    POSTCONDICIONES:
        - documentos_plagiados es una lista de nombres de archivos con similaridad mayores al 1%
    '''
    documentos_plagiados = []
    nombres_archivos = list(diccionario_archivo_ngrama.keys()) # lista con los nombres de los archivos

    for i in range(len(nombres_archivos)): # recorro todos los documentos 
        for j in range(i + 1, len(nombres_archivos)): # lo recorro junto al documento siguiente, considero el triangulo superior de la matriz
            
            documento_A = nombres_archivos[i] # obtengo el nombre del archivo
            ngrama_A = diccionario_archivo_ngrama[documento_A] # accedo al ngrama por la clave del diccionario

            documento_B = nombres_archivos[j]
            ngrama_B = diccionario_archivo_ngrama[documento_B]

            similaridad = calcular_similaridad_jaccard(ngrama_A, ngrama_B) # calculo el indice de jaccard

            if similaridad > 1:
                documentos_plagiados.append([documento_A, documento_B, similaridad]) # si el indice es mayor a 1, lo añado a la lista de plagios

    return documentos_plagiados


def escribir_archivo_plagios(documentos_plagiados, nombre_archivo):
    '''
    La funcion recibe una lista con documentos_plagiados y un nombre_archivo para escribir el reporte, abre
    el archivo en modo escritura y recorre las lineas de la lista
    PRECONDICIONES:
        - documentos_plagiados es una lista de listas con valores nombre1, nombre2 y el porcentaje de similaridad,
        nombre_archivo es un nombre valido para escribir un reporte en formato csv
    POSTCONDICIONES:
        - el reporte es escrito con la informacion de la lista y el encabezado nombre_archivo1,nombre_archivo2,similaridad
    '''
    try:
        with open(nombre_archivo, "w") as plagios: # abro el archivo en formato escritura
            plagios.write("nombre_archivo1,nombre_archivo2,similaridad\n") # escribo el encabezado

            for nombre1, nombre2, similaridad in documentos_plagiados:
                plagios.write(f"{nombre1},{nombre2},{similaridad}\n") # escribo las lineas con los documentos
    
    except PermissionError: # Windows, si el nombre le pertenece a un directorio o archivo, no es unico
        print("El nombre no es valido, un directorio ya tiene ese nombre")

    except IsADirectoryError: # igual que PermissionError pero para Linux
        print("El nombre no es valido, un directorio ya tiene ese nombre")

