def imprimir_nombres(tupla):
    # Recibe una tupla con nombres e imprime el mensaje
    for nombre in tupla:
        print(f"Estimado {nombre}, vote por mi")

#imprimir_nombres(("Mateo", "Valentino", "Nazarena"))

def imprimir_nombres_posiciones(tupla, p, n):
    # Recibe una tupla con nombres e imprime n mensajes desde la posicion p
    for i in range(p, p + n):
        print(f"Estimado {tupla[i]}, vote por mi")

#imprimir_nombres_posiciones(("Mateo", "Valentino", "Nazarena", "Liliana", "Paulo", "Lupe"), 2, 3)

def imprimir_super_tupla(tupla, p, n):
   # Recibe una tupla con nombres e imprime n mensajes desde la posicion p segun genero
    for i in range(p, p + n):
        if tupla[i][1] == "Masculino":
            print(f"Estimado {tupla[i][0]}, vote por mi")
        else:
            print(f"Estimada {tupla[i][0]}, vote por mi")

'''
imprimir_super_tupla((("Mateo", "Masculino"),
                      ("Valentino", "Masculino"),
                      ("Nazarena", "Femenino"),
                      ("Liliana", "Femenino"),
                      ("Paulo", "Masculino"),
                      ("Lupe", "Femenino")), 2, 3)
'''