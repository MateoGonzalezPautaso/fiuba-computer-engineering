import unittest
from sumar_enteros import Suma

class TestSumar(unittest.TestCase):

    def test_sumar_positivos(self):
        suma = Suma()
        self.assertEqual(suma.sumar(1, 2), 3)

    def test_sumar_negativos(self):
        suma = Suma()
        self.assertEqual(suma.sumar(-1, -2), -3)

    def test_sumar_ceros(self):
        suma = Suma()
        self.assertEqual(suma.sumar(0, 0), 0)



if __name__ == '__main__':
    unittest.main()