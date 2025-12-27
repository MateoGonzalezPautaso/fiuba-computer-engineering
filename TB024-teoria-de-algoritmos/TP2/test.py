import random
import numpy as np
import scipy as sp
from matplotlib import pyplot as plt
from util import time_algorithm

# Algoritmo a medir
from tp2 import maximizar_kills, reconstruir_solucion

def generar_estrategias_fi_fijo(n, max_x, f_fijo):
    x = random.sample(range(1, max_x + 1), n)

    f = [f_fijo] * n

    return x, f

def generar_estrategias_xi_fijo(n, x_fijo, max_f):
    x = [x_fijo] * n
    
    f = random.sample(range(1, max_f + 1), n)
    f.sort()
    
    return x, f

def generar_estrategias_ordenadas(n, max_x, max_f):
    x = random.sample(range(1, max_x + 1), n)
    
    f = random.sample(range(1, max_f + 1), n)
    f.sort()
        
    x.sort() # ordenado
    #x.sort(reverse = True) # ordenado al reves

    return x, f

def generar_estrategias_random(n, max_x, max_f):
    '''
    Recibe la cantidad de minutos donde llegarian soldados, el rango máximo de soldados y el rango máximo de fuerza

    Cada rafaga de soldados y fuerza acumulada es asignada un valor aleatorio

    Retorna dos listas que contienen las rafagas de soldados por minuto y la fuerza que se acumula en tales minutos
    '''
    x = random.sample(range(1, max_x + 1), n)

    f = random.sample(range(1, max_f + 1), n)
    f.sort()
    
    return x, f

def generar_datos_reconstruccion_random(n, max_x, max_f):
    x = random.sample(range(1, max_x + 1), n)

    f = random.sample(range(1, max_f + 1), n)
    f.sort()

    KILLS = maximizar_kills(x, f)
    
    return x, f, KILLS

def ajuste_n2(x, tiempos):
    '''
    Ajusta los tiempos del algoritmo a una función con complejidad O(n^2)

    Recibe un array de int con los tamaños de entrada (x)
    Recibe un diccionario con los tiempos de ejecución de cada tamaño de entrada (tiempos)

    Devuelve la función n^2 ajustada con los parametros
    Devuelve los parametros c1 y c2 del ajuste de la función n^2
    Devuelve la lista de errores del ajuste para cada tamaño de entrada
    '''
    f_n2 = lambda x, c1, c2: c1 * (x**2) + c2
    c_n2, _ = sp.optimize.curve_fit(f_n2, x, [tiempos[n] for n in x])
    errors_n2 = [np.abs(f_n2(n, c_n2[0], c_n2[1]) - tiempos[n]) for n in x]
    return f_n2, c_n2, errors_n2

def ajuste_n(x, tiempos):
    '''
    Ajusta los tiempos del algoritmo a una función con complejidad O(n)

    Recibe un array de int con los tamaños de entrada (x)
    Recibe un diccionario con los tiempos de ejecución de cada tamaño de entrada (tiempos)

    Devuelve la función n ajustada con los parametros
    Devuelve los parametros c1 y c2 del ajuste de la función n
    Devuelve la lista de errores del ajuste para cada tamaño de entrada
    '''
    f_n = lambda x, c1, c2: c1 * x + c2
    c_n, _ = sp.optimize.curve_fit(f_n, x, [tiempos[n] for n in x])
    errors_n = [np.abs(f_n(n, c_n[0], c_n[1]) - tiempos[n]) for n in x]
    return f_n, c_n, errors_n

def ajuste_nlogn(x, tiempos):
    '''
    Ajusta los tiempos del algoritmo a una función con complejidad O(n log(n))

    Recibe un array de int con los tamaños de entrada (x)
    Recibe un diccionario con los tiempos de ejecución de cada tamaño de entrada (tiempos)

    Devuelve la función n log(n) ajustada con los parametros
    Devuelve los parametros c1 y c2 del ajuste de la función n log(n)
    Devuelve la lista de errores del ajuste para cada tamaño de entrada
    '''
    f_nlogn = lambda x, c1, c2: c1 * x * np.log(x) + c2 
    c_nlogn, _ = sp.optimize.curve_fit(f_nlogn, x, [tiempos[n] for n in x])
    errors_nlogn = [np.abs(c_nlogn[0] * n * np.log(n) + c_nlogn[1] - tiempos[n]) for n in x]
    return f_nlogn, c_nlogn, errors_nlogn

def graficar_tiempos(x, tiempos, f_n2, f_nlogn, f_n, c_n2, c_nlogn, c_n, errors_n2, errors_nlogn, errors_n):
    '''
    Grafica los tiempos de ejecución medidos y su ajuste segun n^2 y n log(n), ademas de los errores

    Recibe los mismos parametros que ajuste_n2 y ajuste_nlogn, además de los mismos retornados por dichas funciones

    El gráfico de la izquierda es la comparación entre los tiempos medidos,la funcion n^2 y la funcion n log(n)
    El gráfico de la derecha es el error del ajuste según el tamaño de entrada
    '''
    axs: tuple[plt.Axes, plt.Axes]

    # Gráfico de tiempos
    fig, axs = plt.subplots(1, 2, figsize=(20, 20), sharey=True)
    axs[0].plot(x, [tiempos[n] for n in x], label="Medición")
    axs[0].plot(x, [f_n2(n, c_n2[0], c_n2[1]) for n in x], 'g--', label="Ajuste O(n^2)")
    axs[0].plot(x, [f_n(n, c_n[0], c_n[1]) for n in x], 'r--', label="Ajuste O(n)")
    #axs[0].plot(x, [f_nlogn(n, c_nlogn[0], c_nlogn[1]) for n in x], 'r--', label="Ajuste O(n log(n))")
    axs[0].set_title('Tiempo de ejecución de reconstruir_solucion')
    axs[0].set_xlabel('Tamaño del array')
    axs[0].set_ylabel('Tiempo de ejecución (s)')
    axs[0].legend()

    # Gráfico de errores
    axs[1].plot(x, errors_n2, label="Error O(n^2)")
    axs[1].plot(x, errors_n, label="Error O(n)")
    axs[1].set_title('Error de ajuste')
    axs[1].set_xlabel('Tamaño del array')
    axs[1].set_ylabel('Error absoluto (s)')
    axs[1].legend()

    plt.show()

def main():
    # Siempre seteamos la seed de aleatoridad para que los resultados sean reproducibles
    SEED = 22334455
    random.seed(SEED)

    # Tamaño mínimo=100, tamaño máximo=10k, cantidad de puntos=25
    x = np.linspace(100, 10_000, 25).astype(int)
    max_x = 100000
    max_f = 100000

    # La variable x van a ser los valores del eje x de los gráficos en todo el notebook
    tiempos = time_algorithm(reconstruir_solucion, x, lambda s: generar_datos_reconstruccion_random(s, max_x, max_f))

    # Calcular ajuste y mediciones
    f_n2, c_n2, errors_n2 = ajuste_n2(x, tiempos)
    #f_nlogn, c_nlogn, errors_nlogn = ajuste_nlogn(x, tiempos)
    f_n, c_n, errors_n = ajuste_n(x, tiempos)
    f_nlogn, c_nlogn, errors_nlogn = None, None, None
    # Graficar
    graficar_tiempos(x, tiempos, f_n2, f_nlogn, f_n, c_n2, c_nlogn, c_n, errors_n2, errors_nlogn, errors_n)

if __name__ == "__main__":
    main()
