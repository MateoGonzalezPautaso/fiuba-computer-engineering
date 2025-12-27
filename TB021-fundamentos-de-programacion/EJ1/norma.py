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
