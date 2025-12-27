def encajar_dominos(ficha1, ficha2):
    # Recibe dos fichas de domino e indica si encajan
    return ficha1[0] in ficha2 or ficha1[1] in ficha2
    
assert encajar_dominos((3, 4), (5, 4)) == True
assert encajar_dominos((3, 4), (4, 5)) == True
assert encajar_dominos((5, 6), (6, 1)) == True
assert encajar_dominos((3, 3), (5, 4)) == False
assert encajar_dominos((3, 2), (4, 5)) == False
assert encajar_dominos((5, 6), (2, 1)) == False

def encajar_dominos(cadena):
    # Recibe dos fichas de domino e indica si encajan
    fichas = cadena.split()
    ficha1 = fichas[0].split("-")
    return ficha1[0] in fichas[1] or ficha1[1] in fichas[1]

assert encajar_dominos("3-4 5-4") == True
assert encajar_dominos("3-4 4-5") == True
assert encajar_dominos("5-6 6-1") == True
assert encajar_dominos("3-3 5-4") == False
assert encajar_dominos("3-2 4-5") == False
assert encajar_dominos("3-4 2-5") == False
