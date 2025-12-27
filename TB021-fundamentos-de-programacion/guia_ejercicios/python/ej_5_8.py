def main():
    numero = int(input("Ingrese un numero o -1 para salir: "))
    i = 0
    suma = 0
    while numero != -1:
        suma += numero
        i += 1
        numero = int(input("Ingrese un numero o -1 para salir: "))
    
    print(f"Se ingresaron {i} numeros, la suma total de estos es {suma} y su promedio {suma/i}")

main()