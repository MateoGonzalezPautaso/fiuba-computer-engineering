def max_o_min(a, b, c):
    # Recibe los coeficientes de un polinomio de segundo grado y encuentra maximos o minimos
    y = c - (b**2)/(4*a)
    x = - b / (2*a)
    if a > 0:
        return print(f"El mínimo de la funcion estan en ({x} , {y})")
    return print(f"El maximo de la funcion estan en ({x} , {y})")

resultado = max_o_min(-1, 1, 1)

def raiz_polinomio(a, b, c):
    # Las raices reales o complejas de un polinomio de segundo grado
    w = abs(((b**2 - 4*a*c) **(1/2)) / (2*a))
    z = (-b) / (2*a)
    z1 = f"Raíz: {z} + {w}i"
    z2 = f"Raíz: {z} + {-w}i"
    return z1, z2

z1,z2 = raiz_polinomio(1, 2, 10)
#print(f"{z1}, {z2}")

def interseccion_rectas(m1, b1, m2, b2):
    # Encontrar la interseccion de dos rectas
    while (m1 % m2) != 0:
        x = (b2 - b1) / (m1 - m2)
        y = x + b1
        return f"Punto de interseccion: ({x}, {y})"
    return "Son rectas paralelas"

interseccion = interseccion_rectas(8, 3, 10, 8)
#print(interseccion)