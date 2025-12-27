# Programa que imprime todas las fichas de un juego de 0 a n, una por linea y sin repetir
def main():
    a = 0
    b = 0
    n = int(input("Ingrese hasta que numero de fichas desea tener: "))
    
    while(a <= n):
        for i in range(b, n+1):
            print(f"{a} | {i}")
        
        b += 1
        a += 1

main()