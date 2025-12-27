def valor_abs(n):
    # Devuelve el valor absoluto del n recibido
    abs = (n **2) **(1/2)
    return abs

assert valor_abs(-9) == 9
assert valor_abs(9) == 9
assert valor_abs(-17) == 17
assert valor_abs(17) == 17