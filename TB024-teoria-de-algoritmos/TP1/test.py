import random
import numpy as np
import scipy as sp
from matplotlib import pyplot as plt
from util import time_algorithm

# Algoritmo a medir
from tp1 import minimizar_sumatoria

def generar_batallas_bi_fijo(n, max_t, b_fijo):
    '''
    Recibe la cantidad de batallas que se deben luchar, el rango máximo de tiempos y el valor fijo de pesos

    Cada batalla es asignada un tiempo aleatorio y un peso fijo, para analizar el impacto de la variabilidad
    de los valores

    Retorna una lista de tuplas que contiene las batallas que se deben luchar de esta 
    forma (tiempo que dura la batalla, peso de la batalla)
    '''  
    result = []

    for i in range(n):
        t_i = random.randint(1, max_t)
        b_i = b_fijo
        result.append((t_i, b_i))
        
    return result

def generar_batallas_ti_fijo(n, t_fjo, max_b):
    '''
    Recibe la cantidad de batallas que se deben luchar, el valor fijo de tiempos y el rango máximo de pesos

    Cada batalla es asignada un tiempo fijo y un peso aleatorio, para analizar el impacto de la variabilidad
    de los valores

    Retorna una lista de tuplas que contiene las batallas que se deben luchar de esta 
    forma (tiempo que dura la batalla, peso de la batalla)
    '''  
    result = []

    for i in range(n):
        t_i = t_fjo
        b_i = random.randint(1, max_b)
        result.append((t_i, b_i))
        
    return result

def generar_batallas_ordenadas(n, max_t, max_b):
    '''
    Recibe la cantidad de batallas que se deben luchar, el rango máximo de tiempos y el rango máximo de pesos

    Cada batalla es asignada un tiempo y peso aleatorio

    Retorna una lista de tuplas que contiene las batallas que se deben luchar de esta 
    forma (tiempo que dura la batalla, peso de la batalla)
    '''  
    result = []

    for i in range(n):
        t_i = random.randint(1, max_t)
        b_i = random.randint(1, max_b)
        result.append((t_i, b_i))
        
    #result.sort(key = lambda x: x[0] / x[1]) # ordenado
    result.sort(key = lambda x: x[0] / x[1], reverse = True) # ordenado al reves

    return result

def generar_batallas_random(n, max_t, max_b):
    '''
    Recibe la cantidad de batallas que se deben luchar, el rango máximo de tiempos y el rango máximo de pesos

    Cada batalla es asignada un tiempo y peso aleatorio

    Retorna una lista de tuplas que contiene las batallas que se deben luchar de esta 
    forma (tiempo que dura la batalla, peso de la batalla)
    '''  
    result = []

    for i in range(n):
        t_i = random.randint(1, max_t)
        b_i = random.randint(1, max_b)
        result.append((t_i, b_i))
        
    return result

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

def graficar_tiempos(x, tiempos, f_n, f_nlogn, c_n, c_nlogn, errors_n, errors_nlogn):
    '''
    Grafica los tiempos de ejecución medidos y su ajuste segun n y n log(n), ademas de los errores

    Recibe los mismos parametros que ajuste_n y ajuste_nlogn, además de los mismos retornados por dichas funciones

    El gráfico de la izquierda es la comparación entre los tiempos medidos,la funcion n y la funcion n log(n)
    El gráfico de la derecha es el error del ajuste según el tamaño de entrada
    '''
    axs: tuple[plt.Axes, plt.Axes]

    # Gráfico de tiempos
    fig, axs = plt.subplots(1, 2, figsize=(20, 20), sharey=True)
    axs[0].plot(x, [tiempos[n] for n in x], label="Medición")
    axs[0].plot(x, [f_n(n, c_n[0], c_n[1]) for n in x], 'g--', label="Ajuste O(n)")
    axs[0].plot(x, [f_nlogn(n, c_nlogn[0], c_nlogn[1]) for n in x], 'r--', label="Ajuste O(n log(n))")
    axs[0].set_title('Tiempo de ejecución de minimizar_sumatoria')
    axs[0].set_xlabel('Tamaño del array')
    axs[0].set_ylabel('Tiempo de ejecución (s)')
    axs[0].legend()

    # Gráfico de errores
    axs[1].plot(x, errors_n, label="Error O(n)")
    axs[1].plot(x, errors_nlogn, label="Error O(n log(n))")
    axs[1].set_title('Error de ajuste')
    axs[1].set_xlabel('Tamaño del array')
    axs[1].set_ylabel('Error absoluto (s)')
    axs[1].legend()

    plt.show()

def main():
    # Siempre seteamos la seed de aleatoridad para que los resultados sean reproducibles
    SEED = 22334455
    random.seed(SEED)

    # Tamaño mínimo=100, tamaño máximo=100k, cantidad de puntos=50
    x = np.linspace(100, 100_000, 50).astype(int)
    max_t = 100000
    max_b = 100000

    # La variable x van a ser los valores del eje x de los gráficos en todo el notebook
    tiempos = time_algorithm(minimizar_sumatoria, x, lambda s: [generar_batallas_ordenadas(s, max_t, max_b)])

    # Calcular ajuste y mediciones
    f_n, c_n, errors_n = ajuste_n(x, tiempos)
    f_nlogn, c_nlogn, errors_nlogn = ajuste_nlogn(x, tiempos)

    # Graficar
    graficar_tiempos(x, tiempos, f_n, f_nlogn, c_n, c_nlogn, errors_n, errors_nlogn)

if __name__ == "__main__":
    main()
