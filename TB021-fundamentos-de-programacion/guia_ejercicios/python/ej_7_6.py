def devolver_listas(lista, k):
    # Devuelve tres listas, una con menores, otra con mayores y otra con los iguales a k
    menores, mayores, iguales = [], [], []
    for n in lista:
        if n < k:
            menores.append(n)
        elif n > k:
            mayores.append(n)
        else:
            iguales.append(n)
    
    return menores, mayores, iguales

#menores, mayores, iguales = devolver_listas([1, 2, 3, 7, 9, 13, 15, 16, 17, 18, 21, 30, 45], 15)
#print(menores, mayores, iguales)

def devolver_multiplos(lista, k):
    # Devuelve una lista con los multiplos de k
    multiplos = []
    for n in lista:
        if n % k == 0:
            multiplos.append(n)
    
    return multiplos

#multiplos = devolver_multiplos([1, 2, 3, 7, 9, 13, 15, 16, 17, 18, 21, 30, 45], 15)
#print(multiplos)