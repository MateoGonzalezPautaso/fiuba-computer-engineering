from algoritmos.aproximador_pakku import aproximador_pakku

def calcular_cota_minima(suma_grupos_actual, restante, k):
    """
    suma_grupos_actual: arreglo que guarda las sumas actuales de poder para los k grupos
    restante: el poder restante que me falta repartir entre los grupos

    Esta función para calcular la cota minima funciona repartiendo el poder restante entre los grupos de manera que queden lo más parecidos posibles.
    Asi tambien, termina minimizando la adicion de los cuadrados de los poderes de cada grupo.

    La cota minima es la menor adicion de cuadrados posible a la que puedo aspirar (irrealmente). Esta cota va a servir para verificar si incluso el caso mas optimista de la rama de ejecución actual
    ya es peor que la mejor solucion encontrada.
    """
    sumas_ordenadas = sorted(suma_grupos_actual)
    
    if restante == 0:
        return sum(s**2 for s in sumas_ordenadas)
    
    for i in range(k - 1):
        diferencia_poder = sumas_ordenadas[i + 1] - sumas_ordenadas[i]  # Es la diferencia entre el grupo mas debil y el siguiente
        poder_para_llenar = diferencia_poder * (i + 1)  # i + 1 es la cantidad de grupos que tengo que nivel hasta el poder del siguiente
        
        if restante >= poder_para_llenar:
            # Si me alcanza el poder, nivelo los grupos
            restante -= poder_para_llenar
            for j in range(i + 1):
                sumas_ordenadas[j] = sumas_ordenadas[i+1]
        else:
            # Si no me alcanza el poder, reparto equitativamente entre los que queria nivelar
            aumento_nivel = restante / (i + 1)
            for j in range(i + 1):
                sumas_ordenadas[j] += aumento_nivel
            return sum(s**2 for s in sumas_ordenadas)   # Devuelvo la cota porque ya no tengo mas poder restante

    # Los grupos estan nivelados y todavia queda poder restante, lo reparto equitativamente entre los grupos
    aumento_nivel_final = restante / k
    for j in range(k):
        sumas_ordenadas[j] += aumento_nivel_final
    
    return sum(s**2 for s in sumas_ordenadas)

def _tribu_del_agua_bt(maestros_agua, k, i, sol_actual, adic_actual, suma_grupos_actual, mejor_sol, adic_mejor, poder_restante):
    if i >= len(maestros_agua):
        if adic_actual < adic_mejor:
            copia = [list(g) for g in sol_actual]
            return copia, adic_actual 
        return mejor_sol, adic_mejor
    
    maestro = maestros_agua[i]
    nombre, poder = maestro
    restante = poder_restante[i + 1]
    
    for g in range(k):
        # Rama 1: Agrego al maestro en el subgrupo g
        suma_sin = suma_grupos_actual[g]
        suma_con = suma_sin + poder
        adic_con = adic_actual - (suma_sin ** 2) + (suma_con ** 2)

        # Agrego al maestro
        sol_actual[g].append(maestro)
        suma_grupos_actual[g] = suma_con

        cota_minima = calcular_cota_minima(suma_grupos_actual, restante, k)
        if cota_minima >= adic_mejor:
            # Incluso en el mejor de los casos, esta rama ya es peor que la mejor.
            sol_actual[g].pop()
            suma_grupos_actual[g] = suma_sin
            continue
        
        sol_res, adic_res = _tribu_del_agua_bt(maestros_agua, k, i + 1, sol_actual, adic_con, suma_grupos_actual, mejor_sol, adic_mejor, poder_restante)

        if adic_res < adic_mejor:
            mejor_sol, adic_mejor = sol_res, adic_res 

        # Rama 2: No agrego al maestro en el subgrupo g
        sol_actual[g].pop()
        suma_grupos_actual[g] = suma_sin

        # Si habia ubicado al maestro en un grupo vacio, no pruebo los demas porque van a ser permutaciones equivalentes
        if suma_sin == 0:
            break

    return mejor_sol, adic_mejor

def tribu_del_agua_bt(maestros_agua, k):
    '''
    maestros_agua = es una lista de tuplas de la forma [(nombre, poder), ...]
    k = la cantidad de subgrupos a armar
    '''
    sol_actual = [[] for i in range(k)]
    suma_grupos_actual = [0] * k

    # Inicializo la mejor solucion como una aproximación
    mejor_sol, adic_mejor = aproximador_pakku(maestros_agua, k)
    
    maestros_agua = sorted(maestros_agua, key=lambda x:x[1], reverse=True)

    # Guardando en un arreglo la sumatoria total de los poderes que me quedan por asignar
    n = len(maestros_agua)
    poder_restante = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        poder_restante[i] = poder_restante[i + 1] + maestros_agua[i][1]

    return _tribu_del_agua_bt(maestros_agua, k, 0, sol_actual, 0, suma_grupos_actual, mejor_sol, adic_mejor, poder_restante)