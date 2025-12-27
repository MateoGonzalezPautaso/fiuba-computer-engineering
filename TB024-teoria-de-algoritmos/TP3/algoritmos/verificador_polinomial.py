'''
Para demostrar que el problema planteado esta en NP, basta con armar un vertificador para el problema de decisión que funcione en tiempo polinomial
'''

def grupos_parejos(maestros_agua, k, B, subgrupos):
    '''
    maestros_agua = es una lista de tuplas pero la convertimos en un diccionario que usa como clave el nombre del maestro y almacena su poder,
    esto para mejorar la complejidad de ejecucion
    k = la cantidad de subgrupos a armar
    B = valor que debe ser mayor a la adición de los cuadrados de las sumas de las fuerzas de los grupos
    subgrupos = lista de listas donde cada sublista representa un grupo de maestros del estilo
    [
        ["Mateo", "Agustin"],
        ["Tiago"]
    ]
    
    Cada elemento xi debe estar asignado a un grupo y sólo un grupo.
    '''
    maestros_dict = {nombre: poder for nombre, poder in maestros_agua}
    maestros_agua = maestros_dict
    
    if len(subgrupos) != k:
        return False    # La cantidad de subgrupos no coincide con k
    
    asignados = set()
    B_conseguido = 0

    for subgrupo in subgrupos:
        poder_subgrupo = 0
        
        for nombre_maestro in subgrupo:

            if nombre_maestro in asignados or nombre_maestro not in maestros_agua:
                return False    # El maestro solo puede estar asignado a un subgrupo
            
            asignados.add(nombre_maestro)
            poder_subgrupo += maestros_agua[nombre_maestro]

        B_conseguido += poder_subgrupo ** 2

    if len(asignados) != len(maestros_agua):
        return False    # Cada maestro debe estar asignado a un grupo

    return B_conseguido <= B