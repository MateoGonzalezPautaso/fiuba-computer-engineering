class Materia:
    def __init__(self, codigo, nombre, creditos):
        self.codigo = codigo
        self.nombre = nombre
        self.creditos = creditos
        self.nota = 0


class Carrera:
    def __init__(self, materias):
        self.materias = materias

    def materias_aprobadas(self):
        aprobadas = []
        for materia in self.materias:
            if materia.nota >=4:
                aprobadas.append(materia)
        return aprobadas

    def promedio(self):
        nota_total = 0
        materias_aprobadas = 0
        for materia in self.materias:
            if materia.nota >= 4:
                nota_total += materia.nota
                materias_aprobadas += 1
        if materias_aprobadas == 0:
            raise ValueError("No hay materias aprobadas")
        return nota_total / materias_aprobadas

    def aprobar(self, codigo, nota):
        for materia in self.materias:
            if materia.codigo == codigo:
                materia.nota = nota
                return
        raise ValueError(f"La materia {codigo} no es parte del plan de estudios")

    def creditos_obtenidos(self):
        creditos = 0
        for materia in self.materias:
            if materia.nota >= 4:
                creditos += materia.creditos
        return creditos
