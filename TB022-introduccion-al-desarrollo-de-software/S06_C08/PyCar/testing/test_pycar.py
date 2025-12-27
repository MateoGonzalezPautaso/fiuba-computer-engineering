import unittest
from pycar import PyCar

class TestPyCar(unittest.TestCase):
    def test_encender(self):
        auto = PyCar()
        self.assertTrue(auto.encender())

    def test_apagar(self):
        auto = PyCar()
        self.assertFalse(auto.apagar())

    def test_acelerar(self):
        auto = PyCar()
        auto.acelerar()
        self.assertGreater(auto.velocidad, 0)

    def test_frenar(self):
        auto = PyCar()
        auto.frenar()
        self.assertEqual(auto.velocidad, 0)

    def test_doblar_izquierda(self):
        auto = PyCar()
        auto.acelerar()
        auto.doblar_izquierda()
        self.assertGreater(auto.velocidad, 0)
        self.assertEqual(auto.direccion, "izquierda")

    def test_doblar_derecha(self):
        auto = PyCar()
        auto.acelerar()
        auto.doblar_derecha()
        self.assertGreater(auto.velocidad, 0)
        self.assertEqual(auto.direccion, "derecha")

    def test_retroceder(self):
        auto = PyCar()
        auto.frenar()
        auto.retroceder()
        self.assertEqual(auto.velocidad, 0)
        self.assertEqual(auto.direccion, "reversa")


if __name__ == '__main__':
    unittest.main()