def corregir_examenes(ejercicios, porcentaje_necesario):
    ejercicios_resueltos = input("Ingrese la cantidad de ejercicios resueltos correctamente: ")
    
    while ejercicios_resueltos != "*":
        porcentaje_resuelto = (int(ejercicios_resueltos) * 100) / ejercicios
        print(f"El alumno resolvio el {porcentaje_resuelto}% de {ejercicios} ejercicios")
        if porcentaje_resuelto >= porcentaje_necesario:
            print("Por lo tanto el alumno aprobo")
        else:
            print("Por lo tanto el alumno desaprobo")
        
        ejercicios_resueltos = input("Ingrese la cantidad de ejercicios resueltos correctamente o * para salir: ")

#corregir_examenes(10, 70)