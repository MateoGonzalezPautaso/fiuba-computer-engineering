def validar_numero_entero(ingreso):
    '''
    Asegura que los numeros ingresados solo sean enteros
    '''
    if not isinstance(ingreso, int):
        raise TypeError(f"{ingreso} no es un numero entero")

    return ingreso

def validar_desde_hasta(desde, hasta):
    '''
    Valida que sea un intervalo de rangos validos
    '''
    desde = validar_numero_entero(desde)
    hasta = validar_numero_entero(hasta)
    assert desde < hasta, "El punto inicio desde debe ser menor al punto final hasta"
    return desde, hasta


class Intervalo():
    def __init__(self, desde, hasta):
        '''
        Implementar la clase Intervalo(desde, hasta) que representa un intervalo entre dos
        instantes de tiempo (números enteros expresados en segundos), con la condición desde < hasta.
        '''
        self.desde, self.hasta = validar_desde_hasta(desde, hasta)

    def __str__(self):
        '''
        Funcion para aplicar el metodo str o print
        '''
        return f"{self.desde}, {self.hasta}"

    def duracion(self):
        '''
        Implementar el método duracion que devuelve la duración en segundos del intervalo.
        '''
        return self.hasta - self.desde
    
    def interseccion(self, otro):
        '''
        Implementar el métodointerseccion que recibe otro intervalo y devuelve un nuevo intervalo resultante
        de la intersección entre ambos, o lanzar una excepción si la intersección es nula.
        '''
        inicio = max(self.desde, otro.desde)
        fin = min(self.hasta, otro.hasta)

        if inicio < fin:
            return Intervalo(inicio, fin)
        else:
            raise ValueError("No hay interseccion entre los intervalos")
        
    def union(self, otro):
        '''
        Implementar el método union que recibe otro intervalo. Si los intervalos no son adyacentes ni
        intersectan, debe lanzar una excepción. En caso contrario devuelve un nuevo intervalo resultante
        de la unión entre ambos.
        '''
        if self.hasta < otro.desde or otro.hasta < self.desde:
            raise ValueError("Los intervalos no son adyacentes ni intersectan")
        else:
            inicio = min(self.desde, otro.desde)
            fin = max(self.hasta, otro.hasta)
            return Intervalo(inicio, fin)


def main():
    intervalo1 = Intervalo(10, 30)
    intervalo2 = Intervalo(20, 50)

    print(f"Intervalo 1: ({intervalo1}), Intervalo 2: ({intervalo2})")

    duracion1 = intervalo1.duracion()
    duracion2 = intervalo2.duracion()
    print(f"Duracion 1: {duracion1}, Duracion 2: {duracion2}")

    interseccion = intervalo1.interseccion(intervalo2)
    print(f"Interseccion: {interseccion}")

    union = intervalo1.union(intervalo2)
    print(f"Union: {union}")

main()