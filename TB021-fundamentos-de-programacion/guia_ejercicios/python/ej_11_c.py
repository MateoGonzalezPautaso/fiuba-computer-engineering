def gym_mas_cercano(gimnasios, x, y):
    dist_min = None
    gym_min = None

    for gym in gimnasios:
        g_x, g_y = gimnasios[gym]
        dist = abs(x - g_x) + abs(y - g_y)

        if dist_min is None or dist < dist_min:
            dist_min = dist
            gym_min = gym

    return gym_min

def generar_gym_mas_cercanos(ruta_pokemon, gimnasios, ruta_destino):
    '''
    Escribir una función que reciba una ruta a un archivo de pokemones con el siguiente formato <pokemon>;<tipo>;<pos_x>,<pos_y>,
    y un diccionario de gimnasios (cada clave es el nombre de un gimnasio, y el valor asociado, su posicion, dada como una tupla
    (pos_x, pos_y)) y escriba en un archivo de salida el pokemon, su tipo y su gimnasio más cercano. El archivo de salida debe
    tener el siguiente formato: <pokemon;<tipo>;<gimnasio más cercano>. Para calcular la distancia entre pokemon y gimnasio se
    utiliza distancia manhattan:
    dist(p1, p2) = |p1_x - p2_x| + |p1_y - p2_y|
    '''

    with open(ruta_pokemon, "r") as archivo_origen, open(ruta_destino) as archivo_destino:
        for linea in archivo_origen:
            linea = linea.strip()
            pokemon, tipo, coordenadas = linea.split(";")
            x, y = coordenadas.split(",")
            x, y = int(x), int(y)
            gimnasio = gym_mas_cercano(gimnasios, x, y)

        archivo_destino.write(f"{pokemon};{tipo};{gimnasio}\n")

gimnasios = {
    "Brock": (1, 1),
    "Misty": (3,2)
}

generar_gym_mas_cercanos("info_ej_11_y.csv", gimnasios, "info_ej_11_y_cp.csv")