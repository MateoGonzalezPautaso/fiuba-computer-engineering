def fib(n):
    serie = {0: 0, 1: 1}
    return _fib(n, serie)

def _fib(n, serie):
    if n in serie:
        return serie[n]
    
    if n-1 not in serie:
        serie[n-1] = _fib(n-1, serie)

    return serie[n-1] + serie[n-2]


def fibonacci(n):
    serie = {0: 0, 1: 1}
    return _fibonacci(n, serie)

def _fibonacci(n, serie):
    if n in serie:
        return serie[n]
    serie[n] = _fibonacci(n-1) + _fibonacci(n-2)
    return serie[n]