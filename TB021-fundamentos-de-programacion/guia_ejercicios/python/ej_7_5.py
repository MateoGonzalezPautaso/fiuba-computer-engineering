def es_primo(n):
    # Dado un numero entero n, indica si es primo o no
    if n == 0 or n == 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

def son_primos(lista):
    # Devuelve una lista con todos los numeros primos en esta
    lista_primos = []
    for n in lista:
        if es_primo(n):
            lista_primos.append(n)
        
    return lista_primos

#lista_primos = son_primos([1, 2, 3, 5, 7, 9, 12, 14, 18, 37])
#print(lista_primos)

def suma_promedio(lista):
    # Devuelve la suma y el promedio de los valores de la lista
    return sum(lista), sum(lista)/len(lista)

#suma, promedio = suma_promedio([8, 8, 9, 9, 10, 6])
#print(suma, promedio)

def n_factorial(n):
    # Funcion que dado un numero n, nos permite calcular n!
    for i in range(1, n): # sino (n-1, 1, -1)
        n *= i
    return n

def son_factoriales(lista):
    lista_factoriales = []
    for n in lista:
        lista_factoriales.append(n_factorial(n))
    
    return lista_factoriales

#lista_factoriales = son_factoriales([1, 2, 3, 4, 5, 6])
#print(lista_factoriales)