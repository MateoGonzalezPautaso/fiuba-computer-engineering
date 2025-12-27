from pulp import *

def tribu_del_agua_pl(maestros_agua, k):
    maestros_agua = sorted(maestros_agua, key=lambda x: x[1], reverse=True)
    n = len(maestros_agua)

    nombres = {j: maestros_agua[j-1][0] for j in range(1, n+1)}
    fuerzas = {j: maestros_agua[j-1][1] for j in range(1, n+1)}

    prob = LpProblem("tribu_del_agua", LpMinimize)

    # lowBound = 0 porque las variables a las que se les pone esto son >= 0
    A = LpVariable.dicts("A",
                         (range(1, k+1), range(1, n+1)),
                         cat=LpBinary)

    Z = LpVariable("Z", lowBound=0)
    Y = LpVariable("Y", lowBound=0)

    prob += Z - Y

    # Cada maestro en un único grupo
    for j in range(1, n+1):
        prob += lpSum(A[i][j] for i in range(1, k+1)) == 1

    # Suma por grupo como expresión lineal
    S = {
        i: lpSum(A[i][j] * fuerzas[j] for j in range(1, n+1))
        for i in range(1, k+1)
    }

    # Forzar min/max
    for i in range(1, k+1):
        prob += Z >= S[i]
        prob += Y <= S[i]


    # ---- Fijación de los top-k maestros más fuertes ----
    # Así forzás que cada grupo reciba uno de los más grandes.
    top_k = min(k, n)
    for idx in range(1, top_k+1):
        prob += A[idx][idx] == 1

    # Resolver con CBC
    prob.solve(PULP_CBC_CMD(msg=0))

    return reconstruir(k, S, nombres, fuerzas, A)


def reconstruir(k, S, nombres, fuerzas, A):
    asign = [[] for _ in range(k)]
    suma_cuad = 0

    for i in range(1, k+1):
        si = value(S[i])
        suma_cuad += si * si
        for j in range(1, len(nombres)+1):
            if value(A[i][j]) > 0.5:
                asign[i-1].append((nombres[j], fuerzas[j]))

    return asign, int(suma_cuad)