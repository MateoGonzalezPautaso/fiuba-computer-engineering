def parser(path_txt):
    '''
    Recibe la ruta a un archivo .txt de dataset de maestros agua.

    Parsea el archivo .txt con el formato de ejemplo:
    #cabecera
    2
    Pakku, 101
    Yue, 134
    Yakone, 759
    Pakku I, 308
    Wei, 644
    
    Devuelve una lista de tuplas y la cantidad k de subgrupos
    '''
    maestros_agua = []

    with open(path_txt, 'r') as archivo: 
        next(archivo)   # saltear cabecera
        lineas = archivo.readlines()
        
        k = int(lineas[0])

        for linea in lineas[1:]:
            nombre_maestro, habilidad = linea.strip().split(",")
            
            maestro = (nombre_maestro, int(habilidad))
            maestros_agua.append(maestro)
    
    return maestros_agua, k