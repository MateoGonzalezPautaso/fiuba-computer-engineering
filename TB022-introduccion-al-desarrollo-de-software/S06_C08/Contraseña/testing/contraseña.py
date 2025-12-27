import re

class Contraseña:

    def validar_contraseña_condiciones(self, contraseña: str) -> bool:
        if len(contraseña) >= 8:
            alfanumerico = 0
            caracter_especial = 0

            for letra in contraseña:
                if letra.isdigit() or letra.isalpha():
                    alfanumerico += 1
                
                if letra in ["!", "#", "$"]:
                    caracter_especial += 1

            if alfanumerico > 0 and caracter_especial > 1:
                return True
        
        return False
    
    def validar_contraseña_regex(self, contraseña: str) -> bool:
        patron = r"^(?=.*[a-zA-Z\d])(?=.*[\W_].*[\W_])[a-zA-Z\d\W_]{8,}$"
        return re.match(patron, contraseña)