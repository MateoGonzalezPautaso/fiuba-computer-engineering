def sumar_divisores(n):
    # Devuelve la suma de los divisores de un numero
    suma = 0
    for i in range(1, n):
        if n % i == 0:
            suma += i
        
    return suma

assert sumar_divisores(10) == 8
assert sumar_divisores(20) == 22
assert sumar_divisores(30) == 42

def numeros_perfectos(m):
    # Imprime los numeros tales que la suma de sus divisores es el numero en si
    parejas = 0
    n1 = 2
    while (parejas < m):
        n2 = sumar_divisores(n1)
        if (n1 == n2):
            print(n1, n2)
            parejas += 1
        n1 +=1

#numeros_perfectos(4)

def numeros_amigos(m):
    # La suma de divisores de n1 es igual a n2 y viceversa
    lista = []
    parejas = 0
    n1 = 2
    while (parejas < m):
        n2 = sumar_divisores(n1)
        if (n1 == sumar_divisores(n2)) and (n1 != n2) and (n1 not in lista):
            print(n1, n2)
            lista.append(n1)
            lista.append(n2)
            parejas += 1
        n1 +=1
        
#numeros_amigos(5)


