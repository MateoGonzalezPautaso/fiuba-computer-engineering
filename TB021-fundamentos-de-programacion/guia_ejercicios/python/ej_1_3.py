# De la libreria math importo el numero pi y la raiz cuadrada
from math import pi, sqrt

# Funcion que devuelve todo lo solicitado del rectangulo
def rectangulo(x, y):
    perimetro_rectangulo = (x + y)*2
    area_rectangulo = (x * y)
    return perimetro_rectangulo, area_rectangulo

# Funcion que devuelve todo lo solicitado del circulo y esfera
def circulo(r):
    perimetro_circulo = (2 * pi * r)
    area_circulo = (pi * (r**2))
    volumen_esfera = ((4/3) * pi * (r**3))
    return perimetro_circulo, area_circulo, volumen_esfera

# Funcion que devuelve todo lo solicitado del triangulo
def triangulo(a, b):
    hipotenusa = sqrt((a**2) + (b**2))  # En vez de sqrt se puede hacer **0.5
    return hipotenusa

perimetro_rectangulo, area_rectangulo = rectangulo(8, 3)
print(perimetro_rectangulo, area_rectangulo)
perimetro_circulo, area_circulo, volumen_esfera = circulo(5)
print(perimetro_circulo, area_circulo, volumen_esfera)
hipotenusa = triangulo(2, 3)
print(hipotenusa)