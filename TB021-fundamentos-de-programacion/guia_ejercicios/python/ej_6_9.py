def confirmar_numero(mensaje, min, max):
    # Una vez que el usuario ingresa el valor entre min y max, lo devuelve

    while True:
        try:
            numero = int(input(f"{mensaje} [{min}..{max}]: "))
            if numero <= max and numero >= min:
                return numero
        except ValueError:
            numero = input(f"Por favor ingresa un numero entre [{min}..{max}]: ")

numero = confirmar_numero("¿Cuál es tu número favorito?", -50, 50)
print(numero)
