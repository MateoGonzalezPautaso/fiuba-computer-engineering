import unittest

def es_primo(n):
    if n < 2:
        return False
    
    for i in range(2, n):
        if n % i == 0:
            return False

    return True

def es_par(n):
    return n % 2 == 0

def primos_entre(a, b):
    primos = []
    for numero in range(a, b):
        if es_primo(numero):
            primos.append(numero)
    return primos

class TestPrimos(unittest.TestCase):

    def test_par_no_es_primo(self):
        self.assertFalse(es_primo(8))
        self.assertTrue(es_par(8))

    def test_impar_no_es_primo(self):
        self.assertFalse(es_primo(9))
        self.assertFalse(es_par(9))


    def test_primo(self):
        self.assertTrue(es_primo(13))

    def test_primos_hasta_20(self):
        self.assertEqual(primos_entre(1, 20), [2, 3, 5, 7, 11, 13, 17, 19])