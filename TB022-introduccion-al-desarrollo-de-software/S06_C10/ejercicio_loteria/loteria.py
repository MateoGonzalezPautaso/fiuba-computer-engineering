import random


class Loteria:
    def __init__(self, numeros, premio):
        self.numeros_ganadores = numeros
        self.numeros_sorteados = []
        self.premio = premio

    def sortear(self):
        numeros_sorteados = []
        for i in range(len(self.numeros_ganadores)):
            numero = random.randint(1, 45)
            while numero in self.numeros_sorteados:
                numero = random.randint(1, 45)
            numeros_sorteados.append(numero)
        self.numeros_sorteados = sorted(numeros_sorteados)

    def verificar_premio(self):
        aciertos = 0
        for numero in self.numeros_ganadores:
            if numero in self.numeros_sorteados:
                aciertos += 1

        if aciertos == 5:
            self.premio = self.premio * 0.4
        elif aciertos == 4:
            self.premio = self.premio * 0.1
        else:
            self.premio = 0

    def jugar(self):
        self.sortear()
        self.verificar_premio()
        return self.premio

def main():
    loteria = Loteria([1, 2, 3, 4, 5], 1_000_000)
    premio = loteria.jugar()
    print(f"Premio: {premio}")

main()