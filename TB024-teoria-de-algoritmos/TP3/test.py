import random
import time
import numpy as np
import scipy as sp
from matplotlib import pyplot as plt
from util import time_algorithm, RUNS_PER_SIZE
from parser import parser

# Algoritmo a medir
#from algoritmos.algortimo_pl import tribu_del_agua_pl
from algoritmos.algoritmo_bt import tribu_del_agua_bt
from algoritmos.aproximador_pakku import aproximador_pakku
from algoritmos.simulated_annealing import simulated_annealing

def generar_maestros_random(n, max_poder, k):
    '''
    Recibe la cantidad de maestros a generar y el rango máximo de poder

    Retorna una lista de tuplas que contienen los nombre de los maestros y los poderes
    '''
    maestros_agua = []

    for i in range(n):
        nombre = f"maestro_{i}"
        poder = random.randint(1, max_poder)

        maestro = (nombre, poder)
        maestros_agua.append(maestro)
    
    return maestros_agua, k

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

def ajuste_exp(x, tiempos):
    '''
    Ajusta los tiempos del algoritmo a una función con complejidad O(2^n)

    Recibe un array de int con los tamaños de entrada (x)
    Recibe un diccionario con los tiempos de ejecución de cada tamaño de entrada (tiempos)

    Devuelve la función 2^n ajustada con los parametros
    Devuelve los parametros c1 y c2 del ajuste de la función 2^n
    Devuelve la lista de errores del ajuste para cada tamaño de entrada
    '''
    f_exp = lambda x, c1, c2: c1 * (2 ** x)
    c_exp, _ = sp.optimize.curve_fit(f_exp, x, [tiempos[n] for n in x])
    errors_exp = [np.abs(f_exp(n, c_exp[0], c_exp[1]) - tiempos[n]) for n in x]
    return f_exp, c_exp, errors_exp

def graficar_tiempos(x, tiempos, f_nlogn, f_n2, f_exp, c_nlogn, c_n2, c_exp, errors_nlogn, errors_n2, errors_exp):
    '''
    Grafica los tiempos de ejecución medidos y su ajuste segun n log(n), n^2 y 2^n, ademas de los errores

    Recibe los mismos parametros que ajuste_n2 y ajuste_exp, además de los mismos retornados por dichas funciones

    El gráfico de la izquierda es la comparación entre los tiempos medidos, la funcion n log(n), la funcion n^2 y la funcion 2^n
    El gráfico de la derecha es el error del ajuste según el tamaño de entrada
    '''
    axs: tuple[plt.Axes, plt.Axes]

    # Gráfico de tiempos
    fig, axs = plt.subplots(1, 2, figsize=(20, 20), sharey=True)
    axs[0].plot(x, [tiempos[n] for n in x], label="Medición")
    axs[0].plot(x, [f_nlogn(n, c_nlogn[0], c_nlogn[1]) for n in x], 'r--', label="Ajuste O(n log(n))")
    axs[0].plot(x, [f_n2(n, c_n2[0], c_n2[1]) for n in x], 'g--', label="Ajuste O(n^2)")
    #axs[0].plot(x, [f_exp(n, c_exp[0], c_exp[1]) for n in x], 'r--', label="Ajuste O(2^n)")
    axs[0].set_title('Tiempo de ejecución')
    axs[0].set_xlabel('Tamaño del array')
    axs[0].set_ylabel('Tiempo de ejecución (s)')
    axs[0].legend()

    # Gráfico de errores
    axs[1].plot(x, errors_nlogn, label="Error O(n log(n))")
    axs[1].plot(x, errors_n2, label="Error O(n^2)")
    #axs[1].plot(x, errors_exp, label="Error O(2^n)")
    axs[1].set_title('Error de ajuste')
    axs[1].set_xlabel('Tamaño del array')
    axs[1].set_ylabel('Error absoluto (s)')
    axs[1].legend()

    plt.show()

def graficar_diagrama_barras(path_txt):
    '''
    Grafica los tiempos de ejecucion de cada algoritmo para cada dataset mediante un grafico de barras
    '''
    maestros, k = parser(path_txt)

    algoritmos = {
        "Backtracking": tribu_del_agua_bt,
        #"Simulated Annealing": simulated_annealing,
        "Aproximación Pakku": aproximador_pakku
        #"Programacion Lineal": tribu_del_agua_pl,
    }

    tiempos_promedio = []
    nombres_algoritmos = []

    for nombre_algo, funcion in algoritmos.items():
        suma_tiempos = 0
        
        for i in range(RUNS_PER_SIZE):
            copia_maestros = maestros[:] 
            
            start = time.time()
            funcion(copia_maestros, k)
            end = time.time()
            
            suma_tiempos += (end - start)
        
        promedio = suma_tiempos / RUNS_PER_SIZE
        nombres_algoritmos.append(nombre_algo)
        tiempos_promedio.append(promedio)

    plt.figure(figsize=(8, 6))
    barras = plt.bar(nombres_algoritmos, tiempos_promedio, color=['#1f77b4', '#2ca02c'])
    
    archivo = path_txt.split("/")[-1]

    plt.xlabel('Algoritmos')
    plt.ylabel(f'Tiempo Promedio (s) - {RUNS_PER_SIZE} runs')
    plt.title(f'Rendimiento en dataset: {archivo}')
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    for bar in barras:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2.0, height, f'{height:.5f}s', ha='center', va='bottom')

    plt.show()

def main():
    # Siempre seteamos la seed de aleatoridad para que los resultados sean reproducibles
    SEED = 22334455
    random.seed(SEED)

    # Tamaño mínimo=100, tamaño máximo=10k, cantidad de puntos=25
    x = np.linspace(100, 20_000, 15).astype(int)

    max_poder = 1000
    k = 30 # cantidad de subgrupos

    # La variable x van a ser los valores del eje x de los gráficos en todo el notebook
    tiempos = time_algorithm(aproximador_pakku, x, lambda s: generar_maestros_random(s, max_poder, k))

    # Calcular ajuste y mediciones
    f_nlogn, c_nlogn, errors_nlogn = ajuste_nlogn(x, tiempos)
    f_n2, c_n2, errors_n2 = ajuste_n2(x, tiempos)
    f_exp, c_exp, errors_exp =None, None, None # ajuste_exp(x, tiempos)

    # Graficar
    graficar_tiempos(x, tiempos, f_nlogn, f_n2, f_exp, c_nlogn, c_n2, c_exp, errors_nlogn, errors_n2, errors_exp)

    #path_dataset = "datasets/18_6.txt"
    #graficar_diagrama_barras(path_dataset)
    
if __name__ == "__main__":
    main()