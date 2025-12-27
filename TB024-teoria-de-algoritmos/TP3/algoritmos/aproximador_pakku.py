def grupo_min(suma_grupos_greedy, k):
    minima_suma = suma_grupos_greedy[0]
    idx_min = 0

    for i in range(1, k):
        suma_act = suma_grupos_greedy[i]

        if suma_act < minima_suma:
            minima_suma = suma_act
            idx_min = i

    return idx_min

def aproximador_pakku(maestros_agua, k):
    if k < 0 or not maestros_agua:
        return None, 0
    
    grupos = [[] for i in range(k)]
    adic_pakku = 0
    suma_grupos_pakku = [0] * k

    maestros_agua = sorted(maestros_agua, key=lambda x:x[1], reverse=True)

    for maestro in maestros_agua:
        nombre, poder = maestro

        # Grupo con la menor suma actual
        idx_g_min = grupo_min(suma_grupos_pakku, k)

        suma_sin = suma_grupos_pakku[idx_g_min]
        suma_con = suma_sin + poder

        grupos[idx_g_min].append(maestro)
        suma_grupos_pakku[idx_g_min] = suma_con

        adic_pakku = adic_pakku - (suma_sin ** 2) + (suma_con ** 2)

    return grupos, adic_pakku




