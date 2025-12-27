import sys
from parser import parser

def imprimir_orden_batallas(batallas):
    '''
    Recibe una lista de tuplas con la información de batallas.
    
    Imprime por pantalla el indice y la batalla a pelear, mostrando el 
    orden de pelea de las mismas
    '''
    n = len(batallas)
    for i in range(n):
        print(f"{i + 1}. {batallas[i]}")

def minimizar_sumatoria(batallas):
    '''
    Recibe una lista de tuplas con la información de batallas.

    Las batallas son ordenadas segun el cociente t_i / b_i y en ese orden 
    se acumulan los tiempos. Además, calcula la sumatoria b_i * F_i

    Cada batalla esta representada como (T_i,B_i) donde:
        - T_i: tiempo de la batalla i
        - B_i: peso de la batalla i

    Devuelve el valor del coeficiente de impacto.
    '''
    batallas.sort(key = lambda x: x[0] / x[1])

    felicidad_actual = 0
    res = 0

    n = len(batallas)
    for i in range(n):
        batalla = batallas[i]
        t_i, b_i = batalla
        
        felicidad_actual += t_i
        res += (b_i * felicidad_actual)

    return res

def main():
    parametros = sys.argv

    if (len(parametros) == 2):
        path_set = parametros[1]
        
        archivo = path_set.split("/")

        batallas = parser(path_set)
        resultado = minimizar_sumatoria(batallas)

        print(f"Orden de las batallas (T_i, B_i) del dataset {archivo[-1]}")
        imprimir_orden_batallas(batallas)
        print(f"Coeficiente de impacto: {resultado}")
        
    else:
        print("Número de parámetros incorrecto")

if __name__ == "__main__":
    main()