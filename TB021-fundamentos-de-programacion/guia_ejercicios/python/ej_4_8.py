def astrologia(dia, mes):
    if (mes == 3 and dia >= 21) or (mes == 4 and dia <= 20):
        return "Aries"
    if (mes == 5 and dia >= 21) or (mes == 6 and dia <= 21):
        return "Geminis"
    if (mes == 7 and dia >= 24) or (mes == 8 and dia <= 23):
        return "Leo"
    if (mes == 9 and dia >= 24) or (mes == 10 and dia <= 22):
        return "Libra"
    if (mes == 11 and dia >= 23) or (mes == 12 and dia <= 21):
        return "Sagitario"
    if (mes == 1 and dia >= 21) or (mes == 2 and dia <= 19):
        return "Acuario"
    if (mes == 4 and dia >= 21) or (mes == 5 and dia <= 20):
        return "Tauro"
    if (mes == 6 and dia >= 22) or (mes == 7 and dia <= 23):
        return "Cancer"
    if (mes == 8 and dia >= 24) or (mes == 9 and dia <= 23):
        return "Virgo"
    if (mes == 10 and dia >= 23) or (mes == 11 and dia <= 22):
        return "Escorpio"
    if (mes == 12 and dia >= 22) or (mes == 1 and dia <= 20):
        return "Capricornio"
    if (mes == 2 and dia >= 20) or (mes == 3 and dia <= 20):
        return "Piscis"

dia = int(input("Ingrese su día (1-31): "))
mes = int(input("Ingrese su mes (1-12): "))
signo = astrologia(dia, mes)
#print(signo)
