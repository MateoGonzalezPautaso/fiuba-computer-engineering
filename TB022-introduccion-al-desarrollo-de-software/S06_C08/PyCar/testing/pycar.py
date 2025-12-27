class PyCar:

    velocidad: int
    direccion: str

    def encender(self):
        return True
    
    def apagar(self):
        return False
    
    def acelerar(self):
        self.velocidad = 5

    def frenar(self):
        self.velocidad = 0

    def doblar_izquierda(self):
        self.direccion = "izquierda"

    def doblar_derecha(self):
        self.direccion = "derecha"

    def retroceder(self):
        self.direccion = "reversa"
