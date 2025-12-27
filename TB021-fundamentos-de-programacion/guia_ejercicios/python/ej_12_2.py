from math import gcd

def validar_numero_entero(ingreso):
    '''
    Asegura que los numeros ingresados solo sean enteros o flotantes
    '''
    if not isinstance(ingreso, int):
        raise TypeError(f"{ingreso} no es un numero entero o flotante")

    return ingreso

class Fraccion:
    '''
    Crear una clase Fraccion, que cuente con dos atributos: dividendo y
    divisor, que se asignan en el constructor, y se imprimen como X/Y en
    el método __str__.
    '''
    def __init__(self, numerador, denominador):
        self.numerador = validar_numero_entero(numerador)
        self.denominador = validar_numero_entero(denominador)
        self.simplificar()

    def __str__(self):
        return f"{self.numerador}/{self.denominador}"
    
    def __add__(self, otro):
        '''
        Implementar el método __add__ que recibe otra fracción y
        devuelve una nueva fracción con la suma de ambas.
        '''
        numerador = self.numerador * otro.denominador + self.denominador * otro.numerador
        denominador = self.denominador * otro.denominador
        return Fraccion(numerador, denominador)
    
    def __mul__(self, otro):
        '''
        Implementar el método __mul__ que recibe otra fracción y
        devuelve una nueva fracción con el producto de ambas.
        '''
        numerador = self.numerador * otro.numerador
        denominador = self.denominador * otro.denominador
        return Fraccion(numerador, denominador)
    
    def simplificar(self):
        '''
        Crear un método simplificar que modifica la fracción actual de
        forma que los valores del dividendo y divisor sean los menores posibles.
        '''
        mayor_comun_divisor = gcd(self.numerador, self.denominador)
        self.numerador = self.numerador // mayor_comun_divisor
        self.denominador = self.denominador // mayor_comun_divisor


def main():
    fraccion1 = Fraccion(1, 8)
    fraccion2 = Fraccion(3, 4)
    print(f"Fraccion 1: {fraccion1}, Fraccion 2: {fraccion2}")

    suma = fraccion1 + fraccion2
    print(suma)

    multiplicacion = fraccion1 * fraccion2
    print(multiplicacion)

main()