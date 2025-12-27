def devolver_letra(cadena):
    # Devuelve la primera letra de cada palabra
    lista = cadena.split(" ")
    cadena_nueva = ""
    for i in range(0, len(lista)):
        cadena_nueva += lista[i][0]

    return cadena_nueva

cadena_nueva = devolver_letra("Mateo Gonzalez Pautaso")
#print(cadena_nueva)

def devolver_letra_mayuscula(cadena):
    # Devuelve la primera letra en mayuscula de cada palabra
    lista = cadena.split(" ")
    for i in range(0, len(lista)):
        reemplazo = ""
        reemplazo += lista[i][0].upper()
        reemplazo += lista[i][1:]
        lista[i] = reemplazo
    
    cadena_nueva = " ".join(lista)
    return cadena_nueva

cadena_nueva = devolver_letra_mayuscula("republica argentina")
#print(cadena_nueva)

def comenzar_a(cadena):
    # Borra las palabras que no empiecen con la letra A
    lista = cadena.split(" ")
    for i in lista[::-1]:
        if i[0] not in ["a", "A"]:
            lista.remove(i)

    cadena_nueva = " ".join(lista)
    return cadena_nueva

cadena_nueva = comenzar_a("Antes de ayer")
print(cadena_nueva)