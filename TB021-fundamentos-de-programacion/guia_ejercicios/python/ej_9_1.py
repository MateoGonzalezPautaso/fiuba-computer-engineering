def tuplas_a_diccionario(tuplas):
    '''
    Escribir una función que reciba una lista de tuplas, y que devuelva 
    un diccionario en donde las claves sean los primeros elementos de
    las tuplas, y los valores una lista con los segundos 
    '''
    diccionario = {}
    for key, value in tuplas:

        '''
        if key not in diccionario:
            diccionario[key] = []
        diccionario[key].append(value)  
        '''
        
        if key not in diccionario:
            diccionario[key] = [value]
        else:
            diccionario[key].append(value)        
    
    return diccionario

tuplas = [
    ("Hola", "don Pepito"),
    ("Hola", "don Jose"),
    ("Buenos", "dias")
    ]

diccionario = tuplas_a_diccionario(tuplas)