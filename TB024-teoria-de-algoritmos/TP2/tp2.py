import sys
from parser import parser

def reconstruir_solucion(x, f, KILLS):
    n = len(KILLS)
    if n == 0: return []
    
    decisiones = []     

    i = n - 1
    anterior = i    # En la iteración "anterior" siempre se ataca
    
    while i > 0:

        if anterior == i:
            
            for t in range(i - 1, -1, -1):
                if KILLS[i] == KILLS[t] + min(x[i - 1], f[(i - t) - 1]):
                    decisiones.append("Atacar")
                    anterior = t
                    break
        
        else:
            decisiones.append("Cargar")
        
        i -= 1

    decisiones.reverse()
    return decisiones

def maximizar_kills(x, f):
    n = len(x)
    if n == 0: return 0

    KILLS = [0] * (n + 1)

    for i in range(1, n + 1):
        max_kills = -1
        
        for t in range(0, i):
            ataque = KILLS[t] + min(x[i - 1], f[(i - t) - 1])

            if ataque > max_kills:
                max_kills = ataque

        KILLS[i] = max_kills

    decisiones = reconstruir_solucion(x, f, KILLS)
    return KILLS[n], decisiones

def main():
    parametros = sys.argv

    if (len(parametros) == 2):
        path_set = parametros[1]

        archivo = path_set.split("/")
        
        x, f = parser(path_set)
        resultado, decisiones = maximizar_kills(x, f)

        print(f"{archivo[-1]}")
        print(f"Estrategia: {decisiones}")
        print(f"Cantidad de tropas eliminadas: {resultado}")
        
    else:
        print("Número de parámetros incorrecto")

if __name__ == "__main__":
    main()