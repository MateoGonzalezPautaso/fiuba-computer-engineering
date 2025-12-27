# Funcion que recibe cantidad de pesos, tasa de interes y numero de años para devolver un monto final
def plazo_fijo(cantidad_pesos, tasa_interes, anios):
    monto_final = cantidad_pesos * ((1+(tasa_interes/100))**anios)
    return monto_final

monto_final = plazo_fijo(1000, 5, 10)
#print(f"El plazo fijo es de: ${monto_final}")