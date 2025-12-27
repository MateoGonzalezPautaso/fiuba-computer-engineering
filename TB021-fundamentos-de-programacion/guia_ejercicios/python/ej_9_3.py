def diccionario_agenda(agenda):
    '''
    Escribir un programa que vaya solicitando al usuario que ingrese nombres.
    a) Si el nombre se encuentra en la agenda (implementada con un diccionario), debe mostrar
    el teléfono y, opcionalmente, permitir modificarlo si no es correcto.
    b) Si el nombre no se encuentra, debe permitir ingresar el teléfono correspondiente.
    El usuario puede utilizar la cadena "*", para salir del programa.
    '''
    while True:
        nombre = input("Ingrese un nombre: ")

        if nombre == "*":
            return agenda

        if nombre in agenda:
            print(f"Telefono: {agenda[nombre]}")

            while True:
                ingreso = input("Desea modificarlo: 'si' o 'no': ")
                if ingreso == "no":
                    break
                telefono = input("Ingrese el nuevo numero: ")
                if telefono.isdigit():
                    agenda[nombre] = int(telefono)
                    break
                else:
                    print("Ingreso incorrecto")

        else:
            while True:
                telefono = input("Ingrese el nuevo numero: ")
                if telefono.isdigit():
                    agenda[nombre] = int(telefono)
                    break
                else:
                    print("Ingreso incorrecto")


agenda = {
    "Mateo": 1122,
    "Juan": 3344,
    "Pedro": 5566
}

diccionario = diccionario_agenda(agenda)