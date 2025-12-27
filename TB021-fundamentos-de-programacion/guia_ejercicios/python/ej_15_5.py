def par(n):
    if n == 1:
        return False
    else:
        return impar(n-1)

def impar(n):
    if n == 1:
        return True
    else:
        return par(n-1)