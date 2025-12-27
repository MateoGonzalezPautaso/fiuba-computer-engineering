from time import sleep

def ingresar_contraseña(password):
    # No permite continuar hasta que el usuario ingrese la contraseña correcta en la cantidad de intentos
    ingreso = input("Tiene un maximo de 5 intentos para ingresar la contraseña: ")
    i = 1
    while (ingreso != password) and (i < 5):
        print("Contraseña incorrecta, espere 3 segundos")
        sleep(3)
        ingreso = input("Contraseña incorrecta, ingresela nuevamente: ")
        i += 1
    
    if (i == 5):
        print("Supero la cantidad de intentos")
        return False
    else:
        print("Contraseña correcta, prosiga")
        return True

def main():
    valor = ingresar_contraseña("mateo")
    print(valor)

main()