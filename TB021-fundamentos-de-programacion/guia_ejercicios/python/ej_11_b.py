def actores_por_anio(direccion):
    '''
    Implementar una función que dado el nombre de un archivo de la forma <película>;<año>;<actor1,actor2,...>
    devuelva un diccionario donde cada actor tenga asociado una lista con todos los años en los que actuó
    (puede haber años repetidos). Cualquier línea con datos inválidos (cualquier campo vacío, año no es un
    número) debe ser ignorada. Se puede suponer que todas las líneas contienen siempre tres elementos separados
    por ;.
    '''

    resultado = {}
    with open(direccion) as archivo:
        archivo.readline()
        for linea in archivo:
            linea = linea.rstrip()
            partes = linea.split(";")
            pelicula, anio, actores = partes

            if not anio.isdigit():
                continue

            actores = actores.split(",")
            for actor in actores:
                if actor not in resultado:
                    resultado[actor] = []
                resultado[actor].append(int(anio))

        return resultado
    
resultado = actores_por_anio("info_ej_11_x.csv")
print(resultado)