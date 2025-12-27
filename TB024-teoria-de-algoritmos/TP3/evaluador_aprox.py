import random
from matplotlib import pyplot as plt
import numpy as np
from parser import parser
from algoritmos.aproximador_pakku import aproximador_pakku
from algoritmos.algoritmo_bt import tribu_del_agua_bt
from algoritmos.simulated_annealing import simulated_annealing

def generar_dataset_perfecto(n_aprox, k, sum_por_grupo):
    """
    Genera un dataset de maestros y un óptimo conocido (real).
    
    Crea k grupos que suman *exactamente* la misma cantidad (sum_por_grupo)
    'n_aprox' y 'max_poder_hint' se usan solo como pistas para definir
    la "suma objetivo" de los grupos.
    """
    
    # Maestros promedio por grupo (aseguramos que sea al menos 1)
    maestros_por_grupo_aprox = max(1, n_aprox // k) 

    # Poder promedio de un maestro 
    poder_promedio_maestro = max(1, sum_por_grupo // maestros_por_grupo_aprox)
    
    maestros_global = []
    sumas_reales = []
    
    for i in range(k):
        suma_actual_grupo = 0
        
        # Generar maestros para este grupo hasta alcanzar EXACTAMENTE la suma
        while suma_actual_grupo < sum_por_grupo:
            
            poder_restante = sum_por_grupo - suma_actual_grupo
            
            # Decidir el poder del próximo maestro
            if poder_restante <= poder_promedio_maestro * 1.5:
                # Si estamos cerca del final, tomar exactamente lo que queda para garantizar que se sume justo
                poder = poder_restante
            else:
                # Si no esta cerca, toma un poder aleatorio entre el 50% y el 150% del poder promedio
                # ej: entre 50% y 150% del poder típico
                min_p = max(1, int(poder_promedio_maestro * 0.5))
                max_p = int(poder_promedio_maestro * 1.5)
                
                # No nos podemos pasar de lo que queda
                max_p = min(max_p, poder_restante - 1) 
                
                if min_p >= max_p:
                    poder = min_p
                else:
                    poder = random.randint(min_p, max_p)
            
            maestros_global.append(poder)
            suma_actual_grupo += poder
            
        sumas_reales.append(suma_actual_grupo)
        
    optimo_conocido = sum([s**2 for s in sumas_reales])
    
    random.shuffle(maestros_global)
    maestros_tuplas = [(f"maestro_{i}", p) for i, p in enumerate(maestros_global)]
    
    return maestros_tuplas, optimo_conocido


def evaluar_ratio_datasets_inmanejables():
    '''
    Grafica los ratios de aproximacion para cada dataset inmanejable por Backtracking 
    mediante un grafico de puntos
    '''
    k_i = [10, 20, 35, 50]
    n_i = [100, 122, 150, 250, 500]
    
    errores_pakku = []
    errores_sa = []

    etiquetas_pakku = []
    etiquetas_sa = []


    random.seed(12345)  # para que sea reproducible
    
    for k in k_i:
        for n in n_i:
            # Generamos un caso donde sabemos la respuesta
            maestros, optimo_teorico = generar_dataset_perfecto(n, k, random.randrange(k, 2435))
            
            _, score_pakku = aproximador_pakku(maestros[:], k)
            _, score_sa = simulated_annealing(maestros[:], k)
            
            ratio_pakku = score_pakku / optimo_teorico
            ratio_sa = score_sa / optimo_teorico
            etiqueta = f"n={len(maestros)}, k={k}"
            
            errores_pakku.append(ratio_pakku)
            errores_sa.append(ratio_sa)
            etiquetas_pakku.append(etiqueta)
            etiquetas_sa.append(etiqueta)

            print(f"{etiqueta}: Ratio={ratio_sa:.10f}")

    # Graficar
    plt.figure(figsize=(12, 6))
    plt.plot(etiquetas_pakku, errores_pakku, marker='o', linestyle='-', linewidth=0.75, markersize=3, color='purple')
    plt.plot(etiquetas_sa, errores_sa, marker='o', linestyle='-', linewidth=0.75, markersize=3, color='green')
    plt.axhline(y=1.0, color='r', linestyle='--', label='Óptimo Teórico')
    plt.xticks(rotation=45)
    plt.ylabel('Ratio de Aproximación A(I)/z(I)')
    plt.title('Calidad de la aproximación en datasets inmanejables')

    errores = errores_pakku + errores_sa
    min_ratio = min(errores)
    max_ratio = max(errores)
    plt.ylim(bottom=min_ratio * 0.999, top=max_ratio * 1.001)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.show()


def evaluar_ratio_datasets_catedra():
    '''
    Grafica los ratios de aproximacion para cada dataset mediante un grafico de barras
    '''
    archivos = [
        "datasets/5_2.txt",
        "datasets/6_3.txt",
        "datasets/6_4.txt", 
        "datasets/8_3.txt",
        "datasets/10_3.txt",
        "datasets/10_5.txt",
        "datasets/10_10.txt",
        "datasets/11_5.txt",
        "datasets/14_3.txt",
        "datasets/14_4.txt",
        "datasets/14_6.txt",
        "datasets/15_4.txt", 
        "datasets/15_6.txt",
        "datasets/17_5.txt",
        "datasets/17_7.txt",
        "datasets/17_10.txt", 
        "datasets/18_6.txt",
        "datasets/18_8.txt",
        "datasets/20_4.txt", 
        "datasets/20_5.txt", 
        "datasets/20_8.txt"
        ]
    ratios = []
    nombres = []

    for ruta in archivos:
        maestros, k = parser(ruta)
        nombre = ruta.split("/")[-1]
        
        _, score_optimo = tribu_del_agua_bt(maestros[:], k) 
        _, score_pakku = aproximador_pakku(maestros[:], k)
        
        ratio = score_pakku / score_optimo
        ratios.append(ratio)
        nombres.append(nombre)
        print(f"{nombre}: Opt={score_optimo}, Pakku={score_pakku}, Ratio={ratio:.10f}")

    # Graficar
    plt.figure(figsize=(8, 5))
    plt.bar(nombres, ratios, color='skyblue')
    plt.axhline(y=1.0, color='r', linestyle='--', label='Óptimo (1.0)')
    plt.ylabel('Ratio de Aproximación A(I)/z(I)')
    plt.title('Calidad de la aproximación en datasets de la cátedra')
    plt.ylim(bottom=0.99, top=max(ratios)*1.01)
    plt.legend()
    plt.show()


def main():
    # Siempre seteamos la seed de aleatoridad para que los resultados sean reproducibles
    SEED = 68523714
    random.seed(SEED)

    evaluar_ratio_datasets_catedra()
    #evaluar_ratio_datasets_inmanejables()


if __name__ == "__main__":
    main()