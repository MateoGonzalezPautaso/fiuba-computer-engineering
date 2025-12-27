# Programa que pregunta un numero n al usuario e imprime los primeros n numeros triangulares, con su indice
def main():
    n = int(input("Ingrese un numero: "))
    n_triangular = 0
    for i in range(1, n+1):
        n_triangular += i
        print(f"{i} - {n_triangular}")

main()