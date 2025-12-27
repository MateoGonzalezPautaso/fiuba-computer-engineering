def parser(path_txt):
    '''
    Recibe la ruta a un archivo .txt de dataset de batallas.

    Parsea el archivo .txt con el formato de ejemplo:
    T_i,B_i
    545,545
    459,325
    781,354
    593,963
    
    Devuelve una lista de tuplas, donde sus valores son:
    [(t1, b1), (t2, b2), ..., (ti, bi)]
    '''
    batallas = []
    
    with open(path_txt, 'r') as archivo: 
        next(archivo) #saltear cabecera

        for linea in archivo:
            t_i, b_i = linea.split(",")

            tupla_t_b = (int(t_i), int(b_i)) # (t_i, b_i)
            batallas.append(tupla_t_b)
            
    return batallas
