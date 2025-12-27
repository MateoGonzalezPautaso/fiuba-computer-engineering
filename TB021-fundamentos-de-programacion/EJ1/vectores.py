def norma(x, y, z):
    """Recibe un vector en R3 y devuelve su norma"""
    return (x**2 + y**2 + z**2) ** 0.5

assert norma(-60, -60, -70) == 110.0
assert norma(26, 94, -17) == 99.0
assert norma(34, 18, -69) == 79.0
assert norma(-34, 63, -42) == 83.0
assert norma(0, 35, 84) == 91.0
assert norma(6, -7, 6) == 11.0
assert norma(94, -3, -42) == 103.0
assert norma(0, 42, -40) == 58.0
assert norma(48, -33, 24) == 63.0
assert norma(0, 0, 0) == 0

z = -85
assert norma(-70, 14, z) == 111.0


def diferencia(x1, y1, z1, x2, y2, z2):
    """Recibe las coordenadas de dos vectores en R3 y devuelve su diferencia"""
    dif_x = x1 - x2
    dif_y = y1 - y2
    dif_z = z1 - z2
    return dif_x, dif_y, dif_z

# Agregar pruebas

assert diferencia(1, 2, 3, 1, 2, 3) == (0, 0, 0)

assert diferencia(55, 90, -31, 16, -72, -52) == (39, 162, 21)
assert diferencia(-39, -162, -21, 16, -72, -52) == (-55, -90, 31)

assert diferencia(38, 62, -12, 55, -88, -75) == (-17, 150, 63)
assert diferencia(17, -150, -63, 55, -88, -75) == (-38, -62, 12)


def producto_vectorial(x1, y1, z1, x2, y2, z2):
    """Recibe las coordenadas de dos vectores en R3 y devuelve el producto vectorial"""
    x = y1*z2 - z1*y2
    y = z1*x2 - x1*z2
    z = x1*y2 - y1*x2
    return x, y, z

assert producto_vectorial(54, 12, 29, 1, 11, 12) == (-175, -619, 582)
assert producto_vectorial(71, 52, 24, 1, 11, 6) == (48, -402, 729)
assert producto_vectorial(726, 434, 110, 488, 962, 820) == (250060, -541640, 486620)
assert producto_vectorial(62, 12, 198, 380, 334, 490) == (-60252, 44860, 16148)
assert producto_vectorial(-85, 807, 964, 462, 101, 474) == (285154, 485658, -381419)
assert producto_vectorial(746, 466, 396, 910, 138, 289) == (80026, 144766, -321112)
assert producto_vectorial(-15, 53, 105, 413, 149, 270) == (-1335, 47415, -24124)
assert producto_vectorial(291, 413, 227, 166, 638, 284) == (-27534, -44962, 117100)
assert producto_vectorial(192, 362, 397, 249, 598, 50) == (-219306, 89253, 24678)
assert producto_vectorial(781, 520, 996, 348, 68, 215) == (44072, 178693, -127852)
assert producto_vectorial(459, 971, 201, 582, 569, 703) == (568244, -205695, -303951)
assert producto_vectorial(754, 968, 956, 231, 901, -31) == (-891364, 244210, 455746)
