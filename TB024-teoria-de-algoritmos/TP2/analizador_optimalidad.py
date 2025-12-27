import sys
from tp2 import maximizar_kills     # Algoritmo a medir
from test import generar_estrategias_random, generar_estrategias_ordenadas, generar_estrategias_xi_fijo, generar_estrategias_fi_fijo
from parser import parser

def _maximizar_kills_bt(x, f, n, i, ult_atq, mejor_estado):
    if i > n: 
        return 0    # kills de aca en adelante

    key = (i, ult_atq)
    if key in mejor_estado:
        return mejor_estado[key]    # Ya esta calculado el maximo para este estado

    # Rama 1: no ataco y sigo cargando
    no_ataco_ahora = _maximizar_kills_bt(x, f, n, i + 1, ult_atq, mejor_estado)

    # Rama 2: ataco en este minuto
    j = i - ult_atq
    kills_i = min(x[i - 1], f[j - 1])
    ataco_ahora = kills_i + _maximizar_kills_bt(x, f, n, i + 1, i, mejor_estado)

    max_kills = max(no_ataco_ahora, ataco_ahora)
    mejor_estado[key] = max_kills
    return max_kills

def maximizar_kills_bt(x, f):
    n = len(x)
    mejor_estado = {}
    return _maximizar_kills_bt(x, f, n, 1, 0, mejor_estado)


def main():
    parametros = sys.argv
    cantidad_parametros = len(parametros)

    if (cantidad_parametros == 1):
        n = 250
        max_x = 100000
        max_f = 100000
        
        # datasets de test.py
        x, f = generar_estrategias_random(n, max_x, max_f)
        #x, f = generar_estrategias_ordenadas(n, max_x, max_f)
        #x, f = generar_estrategias_xi_fijo(n, 100, max_f)
        #x, f = generar_estrategias_fi_fijo(n, max_x, 100)

        resultado_pd, _ = maximizar_kills(x, f)
        resultado_bt = maximizar_kills_bt(x, f)

        print(f"Con Programación Dinámica: {resultado_pd}")
        print(f"Con Backtracking: {resultado_bt}")

    elif (cantidad_parametros == 2):
        path_set = parametros[1]

        # datasets catedra
        x, f = parser(path_set)

        resultado_pd, _ = maximizar_kills(x, f)
        resultado_bt = maximizar_kills_bt(x, f)

        print(f"Con Programación Dinámica: {resultado_pd}")
        print(f"Con Backtracking: {resultado_bt}")
        
    else:
        print("Número de parámetros incorrecto")

if __name__ == "__main__":
    main()