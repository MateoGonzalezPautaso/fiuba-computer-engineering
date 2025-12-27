class Pila:
    def __init__(self):
        self.items = []

    def apilar(self, item):
        self.items.append(item)

    def desapilar(self):
        if not self.esta_vacia():
            return self.items.pop()
        else:
            raise IndexError("La pila está vacía")

    def esta_vacia(self):
        return len(self.items) == 0

def contar_elementos(pila):
    if pila.esta_vacia():
        return 0
    
    elemento = pila.desapilar()
    conteo = 1 + contar_elementos(pila)
    
    pila.apilar(elemento)
    
    return conteo