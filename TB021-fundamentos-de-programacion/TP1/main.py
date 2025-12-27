import sixteen

DIMENSION_MINIMO = 2
DIMENSION_MAXIMO = 9

DIRECCIONES = ["w", "s", "a", "d"]

CARACTER_GUION = "-"
CARACTER_ESPACIO = " "
ESPACIADO_MAXIMO = 5
ESPACIADO_MEDIO = 3
ESPACIADO_MINIMO = 2


def pedir_dimensiones_tablero():
    """
    Indica si los valores de alto y ancho son validos para crear un tablero,
    en caso de no serlos se le pide al usuario que vuelva a ingresarlos hasta
    que lo sean.

    POSTCONDICIONES:
        - Si n_filas y n_columnas cumplen son validas, las retorna para poder
        ser utilizadas
    """

    while True:

        n_filas = input("Ingrese el alto del juego [2-9]: ")
        n_columnas = input("Ingrese el ancho del juego [2-9]: ")

        if n_filas.isdigit() and n_columnas.isdigit() and (DIMENSION_MINIMO <= int(n_filas) <= DIMENSION_MAXIMO) and (DIMENSION_MINIMO <= int(n_columnas) <= DIMENSION_MAXIMO):
            print("-", "\nBienvenido a Sixteen!")
            return int(n_filas), int(n_columnas)

        print("Ingreso invalido, intentelo nuevamente")


def imprimir_tablero(tablero):
    """
    Imprime el tablero ya mezclado para que el jugador pueda visualizarlo por
    pantalla y decidir que movimientos hacer

    POSTCONDICIONES:
        - Debe imprimir el tablero en un formato agrdable
    """

    filas = len(tablero)
    columnas = len(tablero[0])

    numero_maximo = filas * columnas
    largo_numero_maximo = len(str(numero_maximo))

    print(f"{CARACTER_ESPACIO*ESPACIADO_MAXIMO}", end="")

    for columna in range(columnas):

        print(f"{columna}{CARACTER_ESPACIO*(ESPACIADO_MINIMO + largo_numero_maximo)}", end="")

    print(f"\n{CARACTER_ESPACIO*ESPACIADO_MEDIO}{(CARACTER_GUION*(ESPACIADO_MEDIO + largo_numero_maximo))*columnas}", end="")
    print(CARACTER_GUION)

    for fila in range(filas):
        print(f"{fila}{CARACTER_ESPACIO*ESPACIADO_MINIMO}|", end="")

        for columna in range(columnas):
            
            numero_actual = tablero[fila][columna]
            largo_numero_actual = len(str(numero_actual))

            print(f" {numero_actual}{CARACTER_ESPACIO*(largo_numero_maximo - largo_numero_actual)} |", end="")
            
        print()

    print(f"{CARACTER_ESPACIO*ESPACIADO_MEDIO}{(CARACTER_GUION*(ESPACIADO_MEDIO + largo_numero_maximo))*columnas}", end="")
    print(CARACTER_GUION)


def validar_movimiento(tablero):
    """
    Indica si el numero de fila o columna junto al movimiento elegido son
    validos, en caso de no serlos se le pide al usuario que vuelva a ingresarlos hasta
    que lo sean. Recibe el tablero para corroborar que los parametros de fila y columna
    esten en los rangos correctos

    POSTCONDICIONES:
        - Si n y dir son validas, las retorna para poder ser utilizadas y
        efectuar el movimiento
    """

    filas = len(tablero)
    columnas = len(tablero[0])

    print("Direcciones: w (arriba), s (abajo), a (izquierda), d (derecha)")
    while True:

        ingreso = input("Ingrese el movimiento <n, dir> o 'q' para salir: ")

        if ingreso == "q":
            return ingreso
        
        if not ingreso:
            print("No ingreso nada")
            continue

        ingreso = ingreso.split(",")


        if len(ingreso) != 2:
            print("Ingreso invalido")
            continue

        n, dir = ingreso
        n, dir = n.strip(), dir.strip()

        if not n.isdigit() or not dir.isalpha():
            print("Direccion desconocida")
            continue
        
        if dir in DIRECCIONES[:2] and (sixteen.COLUMNA_MINIMO <= int(n) < columnas):
            return int(n), dir
                
        elif dir in DIRECCIONES[2:] and (sixteen.FILA_MINIMO <= int(n) < filas):
            return int(n), dir
        
        else:
            print("Direccion desconocida")


def realizar_movimiento(tablero, n, dir):
    """
    Recibe el tablero para realizar los movimientos de fila o columna
    ingresados por el usuario

    PRECONDICIONES:
        - La fila o columna es un numero entero dentro del rango del tablero y
        la direccion es una de las 4 validas

    POSTCONDICIONES:
        - Si n y dir son validas, las retorna para poder ser utilizadas y
        efectuar el movimiento
    """

    if dir == DIRECCIONES[0]:
        sixteen.rotar_arriba(tablero, n)

    elif dir == DIRECCIONES[1]:
        sixteen.rotar_abajo(tablero, n)

    elif dir == DIRECCIONES[2]:
        sixteen.rotar_izquierda(tablero, n)

    else:
        sixteen.rotar_derecha(tablero, n)


def main():

    n_filas, n_columnas = pedir_dimensiones_tablero()

    tablero = sixteen.crear_tablero(n_filas, n_columnas)

    sixteen.mezclar_tablero(tablero)

    while True:

        imprimir_tablero(tablero)

        ingreso = validar_movimiento(tablero)

        if ingreso == "q":
            print("Salir")
            break

        n, dir = ingreso
        realizar_movimiento(tablero, n, dir)

        if sixteen.esta_ordenado(tablero):
            imprimir_tablero(tablero)
            print("Felicitaciones!!!")
            break

main()