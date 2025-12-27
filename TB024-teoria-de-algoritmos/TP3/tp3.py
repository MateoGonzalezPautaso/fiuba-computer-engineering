import sys
from parser import parser
from algoritmos.algortimo_pl import tribu_del_agua_pl
from algoritmos.algoritmo_bt import tribu_del_agua_bt
from algoritmos.aproximador_pakku import aproximador_pakku
from algoritmos.simulated_annealing import simulated_annealing

def main():
    parametros = sys.argv

    if (len(parametros) == 2):
        path_set = parametros[1]

        archivo = path_set.split("/")
        
        maestros_agua, k = parser(path_set)
        asignaciones, adicion = tribu_del_agua_bt(maestros_agua, k)

        print(f"{archivo[-1]}")
        
        for i in range(k):
                nombres = ", ".join(nombre for nombre, _ in asignaciones[i])
                print(f"Grupo {i + 1}: {nombres}")

        print(f"Adición: {adicion}")
        
    else:
        print("Número de parámetros incorrecto")


def comparar_aproximadores():
    parametros = sys.argv

    if (len(parametros) == 2):
        path_set = parametros[1]

        archivo = path_set.split("/")
        
        maestros_agua, k = parser(path_set)
        _, optimo = tribu_del_agua_bt(maestros_agua, k)
        _, adicion_pakku = aproximador_pakku(maestros_agua, k)
        _, adicion_annealing = simulated_annealing(maestros_agua, k)
        _, adicion_pl = tribu_del_agua_pl(maestros_agua, k)

        print(f"{archivo[-1]}")
    
        print(f"Óptimo: {optimo}")
        print(f"Resultado Pakku: {adicion_pakku}")
        print(f"Resultado Annealing: {adicion_annealing}")
        print(f"Resultado pl: {adicion_pl}")
        
    else:
        print("Número de parámetros incorrecto")

if __name__ == "__main__":
    main()