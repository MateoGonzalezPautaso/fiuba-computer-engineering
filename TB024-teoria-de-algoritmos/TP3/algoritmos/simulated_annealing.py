'''
Algoritmo randomizado que va a partir desde la aproximacion que consigue el aproximador de Pakku. Va a ir probando cambios aleatorios 
para ver si puede mejorar la solucion, dandose dos casos:

1) Si el cambio aleatorio mejora la solución lo mantiene
2) Si el cambio aleatorio empeora la solución, lo mantiene con una probabilidad 'p' y sigue explorando esa rama para verificar si 
puede llegar a mejorar con mas cambios aleatorios
'''

from algoritmos.aproximador_pakku import aproximador_pakku
import random
import math

T_INICIAL = 1000000
T_FINAL = 0.1
TASA_ENFRIAMIENTO = 0.995

def calcular_suma_grupos(solucion, k):
    suma_grupos = [0] * k
    
    for i in range(k):
        grupo = solucion[i]
        for nombre, poder in grupo:
            suma_grupos[i] += poder

    return suma_grupos

def elegir_random_grupo_no_vacio(grupos):
        indices_grupos_no_vacios = []
        for i, grupo in enumerate(grupos):
            if len(grupo) > 0: 
                indices_grupos_no_vacios.append(i)

        return random.choice(indices_grupos_no_vacios)

def acepta_cambio(delta_adic, t_actual):
    if delta_adic < 0:
        return True   # El cambio mejoro la solucion
    else:
        # La probabilidad de aceptar depende de la temperatura y de que tan malo fue el cambio
        # Temperaturas altas permiten cambios no tan buenos
        # Las temperaturas bajas dismunuyen mucho la probabilidad para los cambios malos
        p = math.exp(-delta_adic / t_actual)
        if random.random() < p:
            return True
    return False

def simulated_annealing(maestros_agua, k):
    mejor_sol, adic_mejor = aproximador_pakku(maestros_agua, k)
    
    sol_actual = [list(g) for g in mejor_sol]
    adic_actual = adic_mejor
    suma_grupos_actual = calcular_suma_grupos(sol_actual, k)
    
    t_actual = T_INICIAL

    while t_actual >= T_FINAL:
        # Elige un grupo random que no este vacio
        g1 = elegir_random_grupo_no_vacio(sol_actual)
        
        # Elige un maestro random adentro de ese grupo
        idx = random.randrange(len(sol_actual[g1]))
        maestro = sol_actual[g1][idx]
        nombre, poder = maestro

        # Elige un grupo destino que no sea el mismo
        g2 = random.randrange(k)
        while g1 == g2:
            g2 = random.randrange(k)

        suma_g1_vieja = suma_grupos_actual[g1]
        suma_g2_vieja = suma_grupos_actual[g2]

        suma_g1_nueva = suma_g1_vieja - poder
        suma_g2_nueva = suma_g2_vieja + poder

        adic_nuevo = adic_actual - (suma_g1_vieja**2 + suma_g2_vieja**2) + (suma_g1_nueva**2 + suma_g2_nueva**2)
        delta_adic = adic_nuevo - adic_actual

        if acepta_cambio(delta_adic, t_actual):
            adic_actual = adic_nuevo
            suma_grupos_actual[g1] = suma_g1_nueva
            suma_grupos_actual[g2] = suma_g2_nueva

            sol_actual[g1].pop(idx)
            sol_actual[g2].append(maestro)

            if adic_actual < adic_mejor:
                adic_mejor = adic_actual
                mejor_sol = [list(g) for g in sol_actual]

        t_actual *= TASA_ENFRIAMIENTO

    return mejor_sol, adic_mejor