# Funcion que recibe las coordenadas de un vector en R3 y devuelve la norma del vector
def norma(x, y, z):
    norma = ((x**2) + (y**2) + (z**2)) ** (1/2)
    return norma

#print(norma(3, 2, -4))

# Funcion que recibe las coordenadas de dos vectores en R3 y devuelve las coordenadas de la diferencia
def diferencia(x1, y1, z1, x2, y2, z2):
    x = x1 - x2
    y = y1 - y2
    z = z1 - z2
    return x, y, z

#print(diferencia(8, 7, -3, 5, 3, 2))

# Funcion que recibe las coordenadas de dos vectores en R3 y devuelve las coordenadas del producto vectorial
def producto_vec(x1, y1, z1, x2, y2, z2):
    x = y1 * z2 - y2 * z1
    y = - (x1 * z2 - x2 * z1)
    z = x1 * y2 - x2 * y1
    return x, y, z

#print(producto_vec(1, 4, -2, 3, -1, 0))

# Funcion que recibe las coordenadas de 3 puntos en R3 y devuelve el area del triangulo
def area_triangulo(x1, y1, z1, x2, y2, z2, x3, y3, z3):
    # A es 1, B es 2, C es 3
    ABx, ABy, ABz = diferencia(x1, y1, z1, x2, y2, z2)
    ACx, ACy, ACz = diferencia(x1, y1, z1, x3, y3, z3)
    prod_vec_x, prod_vec_y, prod_vec_z = producto_vec(ABx, ABy, ABz, ACx, ACy, ACz)
    area = norma(prod_vec_x, prod_vec_y, prod_vec_z) /2
    return area

#print((area_triangulo(10, 5, -8, 7, 63, 48, 23, 9, 11)))

# Funcion que recibe las coordenadas de 4 puntos en R2 y devuelva el area del cuadrilatero
def area_cuadrilatero(x1, y1, x2, y2, x3, y3, x4, y4):
    # A es 1, B es 2, C es 3, D es 4
    # Suma del area de dos triangulos AB AC y AD AC
    ABx, ABy, ABz = diferencia(x1, y1, 0, x2, y2, 0)
    ACx, ACy, ACz = diferencia(x1, y1, 0, x3, y3, 0)
    ADx, ADy, ADz = diferencia(x1, y1, 0, x4, y4, 0)
    prod_vec_x1, prod_vec_y1, prod_vec_z1 = producto_vec(ABx, ABy, ABz, ACx, ACy, ACz)
    prod_vec_x2, prod_vec_y2, prod_vec_z2 = producto_vec(ACx, ACy, ACz, ADx, ADy, ADz)
    area1 = norma(prod_vec_x1, prod_vec_y1, prod_vec_z1) /2
    area2 = norma(prod_vec_x2, prod_vec_y2, prod_vec_z2) /2
    area_total = area1 + area2
    return area_total

#print(area_cuadrilatero(4, 3, 5, 10, -2, 8, -3, -5))
