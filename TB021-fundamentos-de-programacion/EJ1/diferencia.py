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