import os

RANGO_MAXIMO_N = 10
RANGO_MINIMO_N = 2
PORCENTAJE_SIMILARIDAD = 15
EXTENSION_REPORTE = ".csv"


def pedir_ruta_directorio():
    '''
    La funcion le pide un nombre de directorio al usuario y devuelve una lista con los nombres de los archivos en el mismo,
    si la ruta es invalida indica el error que sucede
    PRECONDICIONES:
        - Ninguna
    POSTCONDICIONES:
        - Si la ruta es valida devuelve una lista con los nombres de los archivos en el directorio
    '''
    while True:
        try:
            ruta_directorio = input("Ingrese el directorio a escanear (o deje vacío para salir): ")

            if not ruta_directorio: # si el ingreso esta vacio
                return None

            archivos = os.listdir(ruta_directorio) # obtengo una lista con los nombres de todos los archivos del directorio
            
            return ruta_directorio, archivos

        except FileNotFoundError: # si el nombre ingresado no es un directorio existente
            print("El directorio no existe")
        
        except NotADirectoryError: # si el nombre ingresado no es un directorio pero si, por ejemplo, un archivo
            print("La ruta ingresada no es un directorio")


def pedir_n_ngrama():
    '''
    La funcion valida el ingreso de n para armar los ngramas correspondientes
    PRECONDICIONES:
        - Ninguna
    POSTCONDICIONES:
        - En caso que n sea un entero entre los rangos establecidos, debe devolverlo y asi
        terminar la ejecucion del bucle
    '''
    while True:
        try:
            n = int(input("Ingrese el tamaño (2 a 9) para procesar los n-gramas: "))
            if RANGO_MINIMO_N <= n < RANGO_MAXIMO_N: # si n esta entre los rangos, lo devuelvo
                return n
            else:
                print("N no esta entre los rangos especificados")

        except ValueError: # si no se ingresa un numero entero, salta la excepcion
            print("El numero ingresado no es un entero")


def imprimir_documentos_plagiados(documentos_plagiados):
    '''
    La funcion recibe la lista de listas con los documentos plagiados y si estos tienen un porcentaje de
    similaridad mayores al 15% los imprime en pantalla para que sean revisados
    PRECONDICIONES:
        - documentos_plagiados es una lista de listas con valores nombre1, nombre2 y el porcentaje de similaridad
    POSTCONDICIONES:
        - Imprime linea por linea los archivos con porcentaje de similaridad mayores al 15%
    '''
    print("Resultados sospechosos:") # imprimo el encabezado
    
    for i, info in enumerate(documentos_plagiados, 1): # recorro los elementos de la lista de listas
        nombre1, nombre2, similaridad = info
        cadena = f"{i}. {nombre1} vs {nombre2} ({similaridad}%)" # armo la cadena a imprimir
        
        if similaridad >= PORCENTAJE_SIMILARIDAD: # si el indice es mayor a 15 como lo pide el enunciado, imprimo la linea
            print(cadena)


def pedir_nombre_reporte():
    '''
    La funcion valida el ingreso de un nombre junto a su extension para escribir el reporte
    PRECONDICIONES:
        - Ninguna
    POSTCONDICIONES:
        - En caso que el nombre tenga la extension solicitada, debe devolverlo y asi
        terminar la ejecucion del bucle
    '''
    while True:
        nombre_plagios = input("Ingrese el nombre del archivo para guardar el reporte: ")
                
        if nombre_plagios.endswith(EXTENSION_REPORTE): # si el nombre termina con la extension solicitada
            return nombre_plagios
        else:
            print("La extension del archivo no es correcta")