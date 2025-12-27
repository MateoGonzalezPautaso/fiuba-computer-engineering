from random import randrange

def adivinar_numero(n_random):
    # Adivinar el numero aleatorio secreto
    numero = int(input("Ingrese un numero del 1 al 100: "))
    while numero != n_random:
        if n_random > numero:
            print("El numero aleatorio es mayor al ingresado")
        else:
            print("El numero aleatorio es menor al ingresado")
        numero = int(input("Ingrese un numero del 1 al 100: "))

    print(f"El numero secreto era {n_random}")

def main():
    n_random = randrange(1, 100)
    adivinar_numero(n_random)

main()