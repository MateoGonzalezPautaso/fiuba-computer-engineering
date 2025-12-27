def validar_caja(diccionario):
    for billete in diccionario:
        if billete not in [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000]:
            raise ValueError(f'Denominación {billete} no permitida')

def suma_total(diccionario):
    suma = 0
    for billete, cantidad in diccionario.items():
        suma += billete * cantidad

    return suma

def agregar_billetes(diccionario, agregado):
    for billete, cantidad in agregado.items():

        if billete not in diccionario:
            diccionario[billete] = cantidad
        else:
            diccionario[billete] += cantidad
    
    return diccionario

def quitar_billetes(diccionario, quitado):
    for billete, cantidad in quitado.items():

        if diccionario[billete] < cantidad:
            raise ValueError(f'No hay suficientes billetes de denominación {billete}')
    
    for billete, cantidad in quitado.items():

        if diccionario[billete] > cantidad:
            diccionario[billete] -= cantidad
        else:
            diccionario.pop(billete)
    return diccionario



class Caja:
    '''
    Escribir una clase Caja para representar cuánto dinero hay en una caja de un
    negocio, desglosado por tipo de billete (por ejemplo, en el quiosco de la
    esquina hay 6 billetes de 500 pesos, 7 de 100 pesos y 4 monedas de 2pesos).Las
    denominaciones permitidas son 1, 2, 5, 10, 20, 50, 100, 200, 500 y 1000 pesos.
    '''

    def __init__(self, diccionario):
        validar_caja(diccionario)
        self.diccionario = diccionario
        self.suma = suma_total(self.diccionario)

    def __str__(self):
        return f"Caja {self.diccionario} total: {self.suma}"

    def total(self):
        return self.suma

    def agregar(self, agregado):
        validar_caja(agregado)
        self.diccionario = agregar_billetes(self.diccionario, agregado)

    def quitar(self, quitado):
        validar_caja(quitado)
        self.diccionario = quitar_billetes(self.diccionario, quitado)
        self.quitado = suma_total(quitado)
        print(self.quitado)


def main():
    #c = Caja({500: 6, 300: 7, 2: 4})
    #print(c)
    c = Caja({500: 6, 100: 7, 2: 4})
    print(str(c))
    print(c.total())
    #c.agregar({250: 2})
    c.agregar({50: 2, 2: 1})
    print(str(c))
    #c.quitar({50: 3, 100: 1})
    c.quitar({50: 2, 100: 1})
    print(str(c))

main()