def encontrar_digito(d, n):
    # Decide si el digito se encuentra en el numero
    if str(d) in str(n):
        return "El digito se encuentra en el numero"
    else:
        return "El digito no se encuentra en el numero"

assert encontrar_digito(90, 2900) == "El digito se encuentra en el numero"
assert encontrar_digito(10, 29) == "El digito no se encuentra en el numero"
assert encontrar_digito(1, 11) == "El digito se encuentra en el numero"