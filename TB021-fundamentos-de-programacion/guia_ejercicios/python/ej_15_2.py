import random

def simular_experimento():
    n = random.randint(1, 3)
    if n == 1:
        return 3 + simular_experimento()
    elif n == 2:
        return 5 + simular_experimento()
    else:
        return 7