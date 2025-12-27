def verificar_subcadena(cadena, subcadena):
    # Verifica si la cadena esta dentro de la subcadena
    if subcadena in cadena:
        return True
    return False

#print(verificar_subcadena("subcadena", "cadena"))

def orden_alfabetico(cadena1, cadena2):
# Devuelve la cadena que sea anterior en orden alfabetico
    abecedario= "abcdefghijklmnñopqrstuvwxyz"
    
    c = 0
    for i in range(c, len(abecedario)):
        posicion_cadena1 = abecedario.index(cadena1[i])
        posicion_cadena2 = abecedario.index(cadena2[i])
        if posicion_cadena1 == posicion_cadena2:
            c +=1
        elif posicion_cadena1 > posicion_cadena2:
            return cadena2
        else:
            return cadena1

cadena = orden_alfabetico("fruta", "frutilla")

def orden_alfabetico(una_cadena, otra_cadena):
    cadenas = [una_cadena, otra_cadena]
    cadenas.sort()
    return cadenas[0]

def orden_alfabetico(una_cadena, otra_cadena):
    return min(una_cadena, otra_cadena)