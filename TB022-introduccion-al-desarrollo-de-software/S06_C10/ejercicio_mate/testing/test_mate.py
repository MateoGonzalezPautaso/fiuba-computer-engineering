import unittest

class Mate:

    def __init__(self, cantidad_cebadas, temperatura_agua):
        self.cantidad_cebadas = cantidad_cebadas
        self.temperatura_agua = temperatura_agua

    def cebar(self):
        self.temperatura_agua -= 1
        if self.cantidad_cebadas > 0:
            self.cantidad_cebadas -= 1
        else:
            print("Como en las invasiones inglesas. Puro palo y agua...")

    def tomar(self):
        if self.temperatura_agua > 80:
            mensaje = "Esta que pela!"
        elif self.temperatura_agua < 65:
            mensaje = "No sabia que era terere"
        else:
            mensaje = "Tomando el mate"

        print(mensaje)
        return mensaje

    def cambiar_yerba(self, cantidad_cebadas):
        self.cantidad_cebadas = cantidad_cebadas

    def cambiar_agua(self, temperatura_agua):
        self.temperatura_agua = temperatura_agua


class TestMate(unittest.TestCase):

    def test_cebar(self):
        mate = Mate(10, 80)
        mate.cebar()
        self.assertEqual(mate.cantidad_cebadas, 9)
        self.assertEqual(mate.temperatura_agua, 79)

    def test_tomar_normal(self):
        mate = Mate(10, 80)
        mensaje = mate.tomar()
        self.assertEqual(mensaje, "Tomando el mate")

    def test_tomar_terere(self):
        mate = Mate(10, 60)
        mensaje = mate.tomar()
        self.assertEqual(mensaje, "No sabia que era terere")

    def test_tomar_caliente(self):
        mate = Mate(10, 90)
        mensaje = mate.tomar()
        self.assertEqual(mensaje, "Esta que pela!")


    def test_cambiar_yerba(self):
        mate = Mate(9, 80)
        mate.cambiar_yerba(5)
        self.assertEqual(mate.cantidad_cebadas, 5)

    def test_cambiar_agua(self):
        mate = Mate(10, 80)
        mate.cambiar_agua(60)
        self.assertEqual(mate.temperatura_agua, 60)
