import unittest
from contraseña import Contraseña

class TestContraseña(unittest.TestCase):

    def test_validar_contraseña(self):
        contraseña = Contraseña()
        self.assertTrue(contraseña.validar_contraseña_condiciones("mateo123!#"), True)
        self.assertFalse(contraseña.validar_contraseña_condiciones("mateo1!"), False)
        self.assertTrue(contraseña.validar_contraseña_condiciones("mateogp1!!"), True)
        self.assertFalse(contraseña.validar_contraseña_condiciones("mgp1#"), False)

    def test_validar_contraseña_regex(self):
        contraseña = Contraseña()
        self.assertTrue(contraseña.validar_contraseña_regex("mateo123!#"), True)
        self.assertFalse(contraseña.validar_contraseña_regex("mateo1!"), False)
        self.assertTrue(contraseña.validar_contraseña_regex("mateogp1!!"), True)
        self.assertFalse(contraseña.validar_contraseña_regex("mgp1#"), False)


if __name__ == '__main__':
    unittest.main()