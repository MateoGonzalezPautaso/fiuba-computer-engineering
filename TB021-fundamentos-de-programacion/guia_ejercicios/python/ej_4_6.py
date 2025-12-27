def dia_semana(n_dia):
    dia = n_dia % 7
    semana = ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"]
    return semana[dia-1]

dia = dia_semana(9)
#print(dia)