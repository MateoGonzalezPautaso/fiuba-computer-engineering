def main():
    ruta = input("Ingrese la ruta: ")
    try:
        actores = actores_por_anio(ruta)
        print(actores)
    except FileNotFoundError:
        print("Archivo no encontrado")

main()