def bisiesto(year):
    # Indica si un año es bisiesto
    '''if year % 4 == 0 and (year % 100 != 0 or year % 400 == 0):
        return True
    return False'''
    return year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)

#es_bisiesto=bisiesto(2004)
#print(es_bisiesto)

def cantidad_dias(mes, año):
    # Dado un mes y año, devuelve la cantidad de dias
    año = 365
    if bisiesto(año):
        año = 366
        if mes == 2:
            dias = 29
            return dias, año
    
    if mes in [1, 3, 5, 7, 8, 10, 12]:
        dias = 31
    elif mes in [4, 6, 9, 11]:
        dias = 30
    else:
        dias = 28
    return dias, año

#dias, año = cantidad_dias(7, 2004)
#print(f"El año tiene {año} dias y el mes {dias} dias")

def fecha_valida(d, m, a):
    # Dada una fecha, indica si es valida
    if m in range(1, 13):
        dias, año = cantidad_dias(m, a)
        if d in range(1, dias+1):
            return True
    
    return False

#validez = fecha_valida(9, 7, 2003)
#print(validez)

def dias_faltantes(d, m, a):
    # Dada una fecha, indica los dias que faltan hasta fin de mes
    valida = fecha_valida(d, m, a)
    if valida:
        dias, año = cantidad_dias(m ,a)
        fin_de_mes = dias - d
        return fin_de_mes

#fin_de_mes = dias_faltantes(9, 7, 2003)
#print(fin_de_mes)

def fin_año(d, m, a):
    # Dada una fecha, indica los dias que faltan hasta fin de año
    valida = fecha_valida(d, m, a)
    if valida:
        total_dias = dias_faltantes(d, m, a)
        for meses in range(m+1, 13):
            dias, año = cantidad_dias(meses ,a)
            total_dias += dias
        return total_dias
        
#total_dias = fin_año(9, 7, 2003)
#print(type(total_dias))

def dias_transcurridos(d, m, a):
    # Dada una fecha, indica los dias transcurridos
    valida = fecha_valida(d, m, a)
    if valida:
        dias_transcurridos = d
        for meses in range(1, m):
            dias, año = cantidad_dias(meses ,a)
            dias_transcurridos += dias
            
        return dias_transcurridos
    
#dias_transcurridos = dias_transcurridos(9, 7, 2003)
#print(type(dias_transcurridos))

def diferencia_fechas(d1, m1, a1, d2, m2, a2):
    # Dada una fecha, indica el tiempo transcurrido entre ambas en dias, meses, años
    faltantes = fin_año(d1, m1, a1)
    transcurridos = dias_transcurridos(d2, m2, a2)
    dias = faltantes + transcurridos
    for año in range(a1+1, a2):
        if bisiesto(año):
            dias += 366
        else:
            dias += 365
    años = dias / 365
    meses = años *12
    return dias, meses, años

#dias, meses, años = diferencia_fechas(9, 7, 2003, 10, 8, 2005)
#print(dias, meses, años)