def insertar_caracter(cadena, caracter):
    # Inserta el caracter entre cada letra de la cadena
    return caracter.join((list(cadena)))

nueva_cadena = insertar_caracter("separar", ",")
assert insertar_caracter("separar", ",") == "s,e,p,a,r,a,r"

def reemplazar_espacios(cadena, caracter):
    # Reemplaza todos los espacios por el caracter
    return caracter.join((cadena.split()))

nueva_cadena = reemplazar_espacios("mi archivo de texto.txt", "_")
assert reemplazar_espacios("mi archivo de texto.txt", "_") == "mi_archivo_de_texto.txt"

def reemplazar_digitos(cadena, caracter):
    # Reemplaza todos los dígitos en la cadena por el caracter
    nueva_cadena = ""
    for car in cadena:
        if car.isdecimal():
            nueva_cadena += caracter
        else:
            nueva_cadena += car

    return nueva_cadena

nueva_cadena = reemplazar_digitos("su clave es: 1540", "X")
assert reemplazar_digitos("su clave es: 1540", "X") == "su clave es: XXXX"


'''
CHECK
'''
def insertar_caracter(cadena, caracter):
    # Inserta el caracter cada 3 dígitos en la cadena
    nueva_cadena = ""
    i = 0
    for car in cadena:
        if i %3 == 0 and i != 0:
            nueva_cadena += caracter
            nueva_cadena += car

        else:
            nueva_cadena += car
        i += 1
    
    return nueva_cadena

nueva_cadena = insertar_caracter("2552552550", ".")
assert insertar_caracter("2552552550", ".") == "255.255.255.0"