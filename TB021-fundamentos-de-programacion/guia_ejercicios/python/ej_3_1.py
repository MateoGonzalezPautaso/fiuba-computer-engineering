# Funcion que transforma horas, minutos y segundos a solo segundos
def hms_to_s(h, m, s):
    segundos = h *3600 + m *60 + s
    return segundos

#print(hms_to_s(2, 15, 15))

# Funcion que transforma segundos a horas, minutos y segundos
def s_to_hms(segundos):
    h = segundos // 3600
    m = (segundos % 3600) // 60
    s = (segundos % 3600) % 60
    return h, m, s

#print(s_to_hms(8115))