from vectores import norma, diferencia, producto_vectorial

def area_triangulo(x1, y1, z1, x2, y2, z2, x3, y3, z3):
    '''Recibe las coordenadas de 3 puntos en R3 y devuelve el area
    del triangulo que conforman'''
    ABx, ABy, ABz = diferencia(x1, y1, z1, x2, y2, z2)
    ACx, ACy, ACz = diferencia(x1, y1, z1, x3, y3, z3)
    prod_vec_x, prod_vec_y, prod_vec_z = producto_vectorial(ABx, ABy, ABz, ACx, ACy, ACz)
    area = norma(prod_vec_x, prod_vec_y, prod_vec_z) /2
    return int(area)

assert area_triangulo(6, 8, -2, -2, 10, 4, -8, 6, 0) == (41)
assert area_triangulo(10, 5, -8, 7, 63, 48, 23, 9, 11) == (702)
assert area_triangulo(12, 54, 32, 6, 8, 9, 1, 34, 5) == (438)
