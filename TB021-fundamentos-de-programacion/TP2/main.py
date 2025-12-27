import logica
import presentacion


def main():
    while True:
        ruta_con_archivos = presentacion.pedir_ruta_directorio()

        if ruta_con_archivos == None:
            print("Saliendo del programa...")
            break

        ruta_directorio, archivos = ruta_con_archivos # Si la ruta no esta vacia, obtengo las dos devoluciones de pedir_ruta_directorio()

        archivos_txt = logica.obtener_archivos_con_rutas(ruta_directorio, archivos) # diccionario con nombre: ruta

        archivos_txt = logica.leer_lineas_archivo(archivos_txt) # diccionario con nombre: contenido

        n = presentacion.pedir_n_ngrama() # pido un n entero para poder armar los ngramas

        archivos_txt = logica.armar_ngrama(archivos_txt, n) # diccionario con nombre: ngrama

        documentos_plagiados = logica.obtener_documentos_plagiados(archivos_txt) # recorro los ngramas de los archivos y obtengo las similaridades

        if len(documentos_plagiados) > 0: # verifico que la lista no este vacia
            presentacion.imprimir_documentos_plagiados(documentos_plagiados) # imprimo los documentos con similaridad mayor al 15%
        else:
            print("No se encontraron resultados sospechosos")
            # podría cortar la ejecución aca para no escribir un reporte

        nombre_plagios = presentacion.pedir_nombre_reporte() # pido un nombre con extension csv para escribir el reporte

        logica.escribir_archivo_plagios(documentos_plagiados, nombre_plagios) # escribo el reporte

main()