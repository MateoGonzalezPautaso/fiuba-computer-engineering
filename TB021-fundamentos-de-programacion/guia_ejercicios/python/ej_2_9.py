# Programa que imprime todas las fichas de domino, una por linea y sin repetir
def main():
    a = 0
    b = 0
    
    while(a <=6):
        for i in range(b, 7):
            print(f"{a} | {i}")
        
        b += 1
        a += 1

main()