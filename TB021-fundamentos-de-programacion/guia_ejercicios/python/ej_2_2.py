import ej_2_1

def main():
    cantidad_pesos = int(input("Cuantos pesos desea invertir?: "))
    tasa_interes = int(input("Cual seria la tasa de interes?: "))
    anios = int(input("Cuantos años duraria?: "))
    monto_final = ej_2_1.plazo_fijo(cantidad_pesos, tasa_interes, anios)
    print(f"El plazo fijo es de: ${monto_final}")

main()