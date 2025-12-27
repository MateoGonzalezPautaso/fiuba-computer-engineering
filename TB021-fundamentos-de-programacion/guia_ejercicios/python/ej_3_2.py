import ej_3_1

def main():
    h1 = int(input("Ingrese la cantidad de horas del intervalo 1: "))
    m1 = int(input("Ingrese la cantidad de minutos del intervalo 1: "))
    s1 = int(input("Ingrese la cantidad de segundos del intervalo 1: "))
    h2 = int(input("Ingrese la cantidad de horas del intervalo 2: "))
    m2 = int(input("Ingrese la cantidad de minutos del intervalo 2: "))
    s2 = int(input("Ingrese la cantidad de segundos del intervalo 2: "))
    hms_1 = ej_3_1.hms_to_s(h1, m1, s1)
    hms_2 = ej_3_1.hms_to_s(h2, s2, m2)
    segundos_total = hms_1 + hms_2
    h_total, m_total, s_total = ej_3_1.s_to_hms(segundos_total)
    print(h_total, m_total, s_total)

main()