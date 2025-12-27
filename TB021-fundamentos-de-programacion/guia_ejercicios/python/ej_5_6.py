def es_potencia_de_dos(n):
    # Devuelve True si el numero es una potencia de dos
    if n <= 0:
        return False
    
    while n > 1:
        if n % 2 != 0:
            return False
        n = n // 2
    
    return True

assert es_potencia_de_dos(1) == True
assert es_potencia_de_dos(2) == True
assert es_potencia_de_dos(4) == True
assert es_potencia_de_dos(8) == True
assert es_potencia_de_dos(15) == False
assert es_potencia_de_dos(50) == False
assert es_potencia_de_dos(64) == True

def sumar_potencias_de_dos(n1, n2):
    # Devuelve la suma de las potencias de dos entre los numeros
    suma = 0
    for i in range(n1, n2+1):
        if es_potencia_de_dos(i):
            suma += i

    return suma

assert sumar_potencias_de_dos(1, 10) == 15
assert sumar_potencias_de_dos(1, 20) == 31
assert sumar_potencias_de_dos(1, 30) == 31