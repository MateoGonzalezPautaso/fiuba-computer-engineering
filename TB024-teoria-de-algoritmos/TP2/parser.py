def parser(path_txt):
    '''
    Recibe la ruta a un archivo .txt de dataset de minutos, soldados en i y f(i).

    Parsea el archivo .txt con el formato de ejemplo:
    3
    271
    533
    916
    656
    664
    21

    La primera línea indica la cantidad de minutos a considerar (n). 
    Luego vienen n líneas que corresponden a los x_i, y luego los 
    n valores que corresponden a la función f(.):

    Devuelve dos listas de valores, una con los correspondientes a x_i
    y otra con los de f()
    [x1, x2, ..., xn]
    [f1, f2, ..., fn]
    '''

    with open(path_txt, 'r') as archivo: 
        next(archivo) #saltear cabecera
        lineas = archivo.readlines()
        
        n = int(lineas[0])
        
        x_str = lineas[1:n + 1]
        f_str = lineas[n + 1:]

        x_int = list(map(int, x_str))
        f_int = list(map(int, f_str))
        
    return x_int, f_int