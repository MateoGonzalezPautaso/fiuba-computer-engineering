def validar_lista(coordenadas):
    if len(coordenadas) == 0:
        raise Exception(f"La lista esta vacia")
    
    for coordenada in coordenadas:
        if not isinstance(coordenada, (int, float)):
            raise ValueError(f"El numero no es un entero o flotante")
        
    return coordenadas

class Vector:
    '''
    Crear una clase Vector, que en su constructor reciba una lista de elementos
    que serán sus coordenadas. En el método __str__ se imprime su contenido con
    el formato [x,y,z]
    '''
    def __init__(self, coordenadas):
        self.coordenadas = validar_lista(coordenadas)

    def __str__(self):
        return f"{self.coordenadas}"
    
    def __add__(self, otro):
        '''
        Implementar el método __add__ que reciba otro vector, verifique si tienen la
        misma cantidad de elementos y devuelva un nuevo vector con la suma de ambos.
        Si no tienen la misma cantidad de elementos debe levantar una excepción.
        '''
        vector = []

        if len(self.coordenadas) != len(otro.coordenadas):
            raise Exception(f"Vectores no tienen la misma cantidad de elementos.")
        
        for i in range(len(self.coordenadas)):
            v = self.coordenadas[i] + otro.coordenadas[i]
            vector.append(v)
        
        return Vector(vector)
    
    def __mul__(self, numero):
        '''
        Implementar el método __mul__ que reciba un número y devuelva un nuevo vector,
        con los elementos multiplicados por ese número
        '''
        vector = []

        for i in range(len(self.coordenadas)):
            v = self.coordenadas[i] * numero
            vector.append(v)
        
        return Vector(vector)


def main():
    vector1 = Vector([1, 2, 3])
    vector2 = Vector([5, 7, 2])
    print(f"Vector 1: {vector1}, Vector 2: {vector2}")

    suma = vector1 + vector2
    print(suma)

    multiplicacion1 = vector1 * 2
    multiplicacion2 = vector2 * 3
    print(f"Multiplicacion 1: {multiplicacion1}, Multiplicacion 2: {multiplicacion2}")

main()