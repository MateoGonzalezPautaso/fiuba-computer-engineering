# Dado un numero entero devuelve 1 si es impar o 0 si es par
def par_o_impar(n):
    if (n % 2 == 0):
        return 0
    if (n % 2 != 0):
        return 1

#print(par_o_impar(11))

# Dado un numero entero devuelve el numero de digito de las unidades
def contar_digitos(n):
    n_digitos = len(str(n))
    return n_digitos

#print(contar_digitos(153))

# Dado un numero devuelve el primer numero multiplo de 10 inferior a el
def multiplo_inferior(n):
    multiplo = (n // 10) * 10
    return multiplo

#print(multiplo_inferior(153))