# Funcion que dados cuatro numeros devuelve el mayor producto de dos de ellos
def maximo_producto(n1, n2, n3, n4):
    lista = [n1, n2, n3, n4]
    a = 0
    b = 0
    while (a<= 3):
        for i in range(b, 3):
            lista.append(lista[a] * lista[i+1])
        
        a += 1
        b += 1
    
    return max(lista)
    
print(maximo_producto(1, 5, -2, -4))