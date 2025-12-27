def main():
    decision = "si"
    i = 0
    suma = 0
    while (decision != "no"):
        nota = int(input("Ingrese una nota: "))
        i += 1
        suma += nota
        promedio = suma / i
        print(f"Se ingresaron {i} notas y el promedio es: {promedio}")
        decision = input("Desea seguir ingresando notas - 'si' o 'no': ")

main()