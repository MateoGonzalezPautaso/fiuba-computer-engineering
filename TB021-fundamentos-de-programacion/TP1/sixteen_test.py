import pprint
import sys
import traceback

import sixteen

# Si las pruebas se ven mal en tu terminal, probá cambiando el valor
# de esta constante a True para desactivar los colores ANSI.
TERMINAL_SIN_COLOR = False


def validar_estado(desc: list[list[int]], tablero: list[list[int]]):
    """Asegura que `tablero` tenga un estado similar a `desc`. Se prueba que:
    - El tipo de cada elemento, en todos sus niveles, sea el mismo
    - Las dimensiones sean las mismas
    - El contenido sea el mismo
    """
    x = None
    y = None
    ancho, alto = len(desc[0]), len(desc)
    try:
        assert type(desc) is type(tablero), (
            "Valor en `tablero` no es del tipo lista"
        )
        assert len(tablero) > 0, "Lista en `tablero` está vacía"
        assert (ancho, alto) == (len(tablero[0]), len(tablero)), (
            f"Dimension obtenida ({ancho}, {alto}) no es la esperada "
            f"({len(desc[0])}, {len(desc)})"
        )
        for y in range(alto):
            assert type(desc[y]) is type(tablero[y]), (
                f"Valor en `tablero[{y}]` no es del tipo lista"
            )
            for x in range(ancho):
                assert type(desc[y][x]) is type(tablero[y][x]), (
                    f"Valor en `tablero[{y}][{x}]` no es del tipo entero"
                )
                assert desc[y][x] == tablero[y][x]
    except AssertionError as exc:
        error_msg = "Estado esperado:\n"
        error_msg += pprint.pformat(desc) + "\n"
        error_msg += "\n"
        error_msg += "Estado actual:\n"
        error_msg += pprint.pformat(tablero) + "\n\n"
        if x is not None and y is not None:
            error_msg += f"Error en columna = {x}, fila = {y}:\n"
            error_msg += f"\tValor esperado: {desc[y][x]}\n"
            error_msg += f"\tValor encontrado: {tablero[y][x]}\n"
        raise AssertionError(error_msg + str(exc)) from exc


def test_01_crear_tablero_cuadrado():
    """Crea un nuevo tablero básico de sixteen de dimensiones simétricas 4x4"""
    desc = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16],
    ]
    tablero = sixteen.crear_tablero(4, 4)
    validar_estado(desc, tablero)


def test_02_crear_tablero_rectangular():
    """Crea un nuevo juego básico de sixteen de dimensiones 3x6"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [7, 8, 9, 10, 11, 12],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    validar_estado(desc, tablero)


def test_03_rotar_izquierda_tablero_cuadrado():
    """Valida el funcionamiento de la función `rotar_izquierda` considerando un
    tablero cuadrado."""
    desc = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [10, 11, 12, 9],
        [13, 14, 15, 16],
    ]
    tablero = sixteen.crear_tablero(4, 4)
    assert sixteen.rotar_izquierda(tablero, 2), (
        "Llamada válida a función de rotar con índice "
        "fila=2 devolvió `False`"
    )
    validar_estado(desc, tablero)


def test_04_rotar_izquierda_tableros_rectangulares():
    """Valida el funcionamiento de la función `rotar_izquierda` considerando
    un par de tableros rectangulares"""
    desc1 = [
        [1, 2, 3, 4, 5, 6],
        [8, 9, 10, 11, 12, 7],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero1 = sixteen.crear_tablero(3, 6)
    assert sixteen.rotar_izquierda(tablero1, 1), (
        "Llamada válida a función de rotar con índice "
        "fila=1 devolvió `False`"
    )
    validar_estado(desc1, tablero1)

    desc2 = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
        [10, 11, 12],
        [13, 14, 15],
        [17, 18, 16],
    ]
    tablero2 = sixteen.crear_tablero(6, 3)
    assert sixteen.rotar_izquierda(tablero2, 5), (
        "Llamada válida a función de rotar con índice "
        "fila=5 devolvió `False`"
    )
    validar_estado(desc2, tablero2)


def test_05_rotar_izquierda_con_fila_invalida():
    """Asegura que rotar a la izquierda no pueda completarse si el indice
    indicado es inválido"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [7, 8, 9, 10, 11, 12],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    assert not sixteen.rotar_izquierda(tablero, 5), (
        "Llamada inválida a función de rotar con índice "
        "fila=5 devolvió `True`"
    )
    assert not sixteen.rotar_izquierda(tablero, -1), (
        "Llamada inválida a función de rotar con índice "
        "fila=-1 devolvió `True`"
    )
    validar_estado(desc, tablero)


def test_06_rotar_izquierda_consecutivo():
    """Valida el funcionamiento de la función `rotar_izquierda` considerando
    llamadas consecutivas sobre la misma fila"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [11, 12, 7, 8, 9, 10],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    for _ in range(4):
        assert sixteen.rotar_izquierda(tablero, 1), (
            "Llamada válida a función de rotar con índice "
            "fila=1 devolvió `False`"
        )
    validar_estado(desc, tablero)


def test_07_rotar_derecha_tablero_cuadrado():
    """Valida el funcionamiento de la función `rotar_derecha` considerando un
    tablero cuadrado."""
    desc = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [12, 9, 10, 11],
        [13, 14, 15, 16],
    ]
    tablero = sixteen.crear_tablero(4, 4)
    assert sixteen.rotar_derecha(tablero, 2), (
        "Llamada válida a función de rotar con índice "
        "fila=2 devolvió `False`"
    )
    validar_estado(desc, tablero)


def test_08_rotar_derecha_tableros_rectangulares():
    """Valida el funcionamiento de la función `rotar_derecha` considerando
    un par de tableros rectangulares"""
    desc1 = [
        [1, 2, 3, 4, 5, 6],
        [12, 7, 8, 9, 10, 11],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero1 = sixteen.crear_tablero(3, 6)
    assert sixteen.rotar_derecha(tablero1, 1), (
        "Llamada válida a función de rotar con índice "
        "fila=1 devolvió `False`"
    )
    validar_estado(desc1, tablero1)

    desc2 = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
        [10, 11, 12],
        [13, 14, 15],
        [18, 16, 17],
    ]
    tablero2 = sixteen.crear_tablero(6, 3)
    assert sixteen.rotar_derecha(tablero2, 5), (
        "Llamada válida a función de rotar con índice "
        "fila=5 devolvió `False`"
    )
    validar_estado(desc2, tablero2)


def test_09_rotar_derecha_con_fila_invalida():
    """Asegura que rotar a la derecha no pueda completarse si el indice
    indicado es inválido"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [7, 8, 9, 10, 11, 12],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    assert not sixteen.rotar_derecha(tablero, 5), (
        "Llamada inválida a función de rotar con índice "
        "fila=5 devolvió `True`"
    )
    assert not sixteen.rotar_derecha(tablero, -1), (
        "Llamada inválida a función de rotar con índice "
        "fila=-1 devolvió `True`"
    )
    validar_estado(desc, tablero)


def test_10_rotar_derecha_consecutivo():
    """Valida el funcionamiento de la función `rotar_derecha` considerando
    llamadas consecutivas sobre la misma fila"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [9, 10, 11, 12, 7, 8],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    for _ in range(4):
        assert sixteen.rotar_derecha(tablero, 1), (
            "Llamada válida a función de rotar con índice "
            "fila=1 devolvió `False`"
        )
    validar_estado(desc, tablero)


def test_11_rotar_arriba_tablero_cuadrado():
    """Valida el funcionamiento de la función `rotar_arriba` considerando un
    tablero cuadrado."""
    desc = [
        [1, 2, 7, 4],
        [5, 6, 11, 8],
        [9, 10, 15, 12],
        [13, 14, 3, 16],
    ]
    tablero = sixteen.crear_tablero(4, 4)
    assert sixteen.rotar_arriba(tablero, 2), (
        "Llamada válida a función de rotar con índice "
        "columna=2 devolvió `False`"
    )
    validar_estado(desc, tablero)


def test_12_rotar_arriba_tableros_rectangulares():
    """Valida el funcionamiento de la función `rotar_arriba` considerando
    un par de tableros rectangulares"""
    desc1 = [
        [1, 2, 3, 4, 11, 6],
        [7, 8, 9, 10, 17, 12],
        [13, 14, 15, 16, 5, 18],
    ]
    tablero1 = sixteen.crear_tablero(3, 6)
    assert sixteen.rotar_arriba(tablero1, 4), (
        "Llamada válida a función de rotar con índice "
        "columna=4 devolvió `False`"
    )
    validar_estado(desc1, tablero1)

    desc2 = [
        [1, 5, 3],
        [4, 8, 6],
        [7, 11, 9],
        [10, 14, 12],
        [13, 17, 15],
        [16, 2, 18],
    ]
    tablero2 = sixteen.crear_tablero(6, 3)
    assert sixteen.rotar_arriba(tablero2, 1), (
        "Llamada válida a función de rotar con índice "
        "columna=1 devolvió `False`"
    )
    validar_estado(desc2, tablero2)


def test_13_rotar_arriba_con_fila_invalida():
    """Asegura que rotar a la arriba no pueda completarse si el indice
    indicado es inválido"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [7, 8, 9, 10, 11, 12],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    assert not sixteen.rotar_arriba(tablero, 6), (
        "Llamada inválida a función de rotar con índice "
        "columna=6 devolvió `True`"
    )
    assert not sixteen.rotar_arriba(tablero, -1), (
        "Llamada inválida a función de rotar con índice "
        "columna=-1 devolvió `True`"
    )
    validar_estado(desc, tablero)


def test_14_rotar_arriba_consecutivo():
    """Valida el funcionamiento de la función `rotar_arriba` considerando
    llamadas consecutivas sobre la misma columna"""
    desc = [
        [1, 14, 3],
        [4, 17, 6],
        [7, 2, 9],
        [10, 5, 12],
        [13, 8, 15],
        [16, 11, 18],
    ]
    tablero = sixteen.crear_tablero(6, 3)
    for _ in range(4):
        assert sixteen.rotar_arriba(tablero, 1), (
            "Llamada válida a función de rotar con índice "
            "columna=1 devolvió `False`"
        )
    validar_estado(desc, tablero)


def test_15_rotar_abajo_tablero_cuadrado():
    """Valida el funcionamiento de la función `rotar_abajo` considerando un
    tablero cuadrado."""
    desc = [
        [1, 2, 15, 4],
        [5, 6, 3, 8],
        [9, 10, 7, 12],
        [13, 14, 11, 16],
    ]
    tablero = sixteen.crear_tablero(4, 4)
    assert sixteen.rotar_abajo(tablero, 2), (
        "Llamada válida a función de rotar con índice "
        "columna=2 devolvió `False`"
    )
    validar_estado(desc, tablero)


def test_16_rotar_abajo_tableros_rectangulares():
    """Valida el funcionamiento de la función `rotar_abajo` considerando
    un par de tableros rectangulares"""
    desc1 = [
        [1, 2, 3, 4, 17, 6],
        [7, 8, 9, 10, 5, 12],
        [13, 14, 15, 16, 11, 18],
    ]
    tablero1 = sixteen.crear_tablero(3, 6)
    assert sixteen.rotar_abajo(tablero1, 4), (
        "Llamada válida a función de rotar con índice "
        "columna=4 devolvió `False`"
    )
    validar_estado(desc1, tablero1)

    desc2 = [
        [1, 17, 3],
        [4, 2, 6],
        [7, 5, 9],
        [10, 8, 12],
        [13, 11, 15],
        [16, 14, 18],
    ]
    tablero2 = sixteen.crear_tablero(6, 3)
    assert sixteen.rotar_abajo(tablero2, 1), (
        "Llamada válida a función de rotar con índice "
        "columna=1 devolvió `False`"
    )
    validar_estado(desc2, tablero2)


def test_17_rotar_abajo_con_fila_invalida():
    """Asegura que rotar a la abajo no pueda completarse si el indice
    indicado es inválido"""
    desc = [
        [1, 2, 3, 4, 5, 6],
        [7, 8, 9, 10, 11, 12],
        [13, 14, 15, 16, 17, 18],
    ]
    tablero = sixteen.crear_tablero(3, 6)
    assert not sixteen.rotar_abajo(tablero, 6), (
        "Llamada inválida a función de rotar con índice "
        "columna=6 devolvió `True`"
    )
    assert not sixteen.rotar_abajo(tablero, -1), (
        "Llamada inválida a función de rotar con índice "
        "columna=-1 devolvió `True`"
    )
    validar_estado(desc, tablero)


def test_18_rotar_abajo_consecutivo():
    """Valida el funcionamiento de la función `rotar_abajo` considerando
    llamadas consecutivas sobre la misma columna"""
    desc = [
        [1, 8, 3],
        [4, 11, 6],
        [7, 14, 9],
        [10, 17, 12],
        [13, 2, 15],
        [16, 5, 18],
    ]
    tablero = sixteen.crear_tablero(6, 3)
    for _ in range(4):
        assert sixteen.rotar_abajo(tablero, 1), (
            "Llamada válida a función de rotar con índice "
            "columna=1 devolvió `False`"
        )
    validar_estado(desc, tablero)


def test_19_mantener_dos_tableros_en_paralelo():
    """Crea un tablero 3x3 y uno 5x6. Realiza diferentes operaciones en cada
    uno y luego valida que cada tablero tenga su estado correspondiente.
    Si falla esta prueba, probablemente se estén usando variables globales en
    alguna parte del código realizado, prohibido por el enunciado del TP1.
    """
    tablero1 = sixteen.crear_tablero(3, 3)
    sixteen.rotar_izquierda(tablero1, 2)

    tablero2 = sixteen.crear_tablero(5, 6)
    sixteen.rotar_arriba(tablero2, 3)
    sixteen.rotar_arriba(tablero2, 3)

    desc1 = [
        [1, 2, 3],
        [4, 5, 6],
        [8, 9, 7],
    ]
    desc2 = [
        [1, 2, 3, 16, 5, 6],
        [7, 8, 9, 22, 11, 12],
        [13, 14, 15, 28, 17, 18],
        [19, 20, 21, 4, 23, 24],
        [25, 26, 27, 10, 29, 30],
    ]
    validar_estado(desc1, tablero1)
    validar_estado(desc2, tablero2)


def test_20_tablero_esta_ordenado():
    """Verifica algunos casos donde la función `esta_ordenado` devuelva `True`.
    """
    tablero = sixteen.crear_tablero(3, 3)
    tablero2 = [
        [1, 2, 3, 4, 5],
        [6, 7, 8, 9, 10],
        [11, 12, 13, 14, 15],
    ]
    assert sixteen.esta_ordenado(tablero), (
        "`esta_ordenado` devolvió `False` para el siguiente tablero:"
        f"{pprint.pformat(tablero)}"
    )
    assert sixteen.esta_ordenado(tablero2), (
        "`esta_ordenado` devolvió `False` para el siguiente tablero:"
        f"{pprint.pformat(tablero2)}"
    )


def test_21_tablero_no_esta_ordenado():
    """Verifica algunos casos donde la función `esta_ordenado` devuelva `False`.
    """
    tablero = sixteen.crear_tablero(3, 3)
    sixteen.rotar_izquierda(tablero, 1)
    tablero2 = [
        [1, 2, 3, 9, 5],
        [6, 7, 8, 14, 10],
        [11, 12, 13, 4, 15],
    ]
    assert not sixteen.esta_ordenado(tablero), (
        "`esta_ordenado` devolvió `True` para el siguiente tablero:"
        f"{pprint.pformat(tablero)}"
    )
    assert not sixteen.esta_ordenado(tablero2), (
        "`esta_ordenado` devolvió `True` para el siguiente tablero:"
        f"{pprint.pformat(tablero2)}"
    )


def test_22_mezclar_tablero():
    """Crea un nuevo juego 5x8 y luego mezcla su contenido. Valida que el
    tablero haya sido modificado.
    Al ser una prueba que depende de un factor aleatorio, solo se comprueba que
    el contenido inicial no sea igual al contenido final."""
    desc = sixteen.crear_tablero(5, 8)
    tablero = sixteen.crear_tablero(5, 8)
    sixteen.mezclar_tablero(tablero)
    assert desc != tablero, "Tablero no fue mezclado correctamente."


# Sólo se van a correr aquellos tests que estén mencionados dentro de la
# siguiente constante
TESTS = (
    test_01_crear_tablero_cuadrado,
    test_02_crear_tablero_rectangular,
    test_03_rotar_izquierda_tablero_cuadrado,
    test_04_rotar_izquierda_tableros_rectangulares,
    test_05_rotar_izquierda_con_fila_invalida,
    test_06_rotar_izquierda_consecutivo,
    test_07_rotar_derecha_tablero_cuadrado,
    test_08_rotar_derecha_tableros_rectangulares,
    test_09_rotar_derecha_con_fila_invalida,
    test_10_rotar_derecha_consecutivo,
    test_11_rotar_arriba_tablero_cuadrado,
    test_12_rotar_arriba_tableros_rectangulares,
    test_13_rotar_arriba_con_fila_invalida,
    test_14_rotar_arriba_consecutivo,
    test_15_rotar_abajo_tablero_cuadrado,
    test_16_rotar_abajo_tableros_rectangulares,
    test_17_rotar_abajo_con_fila_invalida,
    test_18_rotar_abajo_consecutivo,
    test_19_mantener_dos_tableros_en_paralelo,
    test_20_tablero_esta_ordenado,
    test_21_tablero_no_esta_ordenado,
    test_22_mezclar_tablero,
)

# El código que viene abajo tiene algunas *magias* para simplificar la corrida
# de los tests y proveer la mayor información posible sobre los errores que se
# produzcan. ¡No te preocupes si no lo entendés completamente!

# Colores ANSI para una salida más agradable en las terminales que lo permitan
COLOR_OK = "\033[1m\033[92m"
COLOR_ERR = "\033[1m\033[91m"
COLOR_RESET = "\033[0m"


def print_color(color: str, *args, **kwargs):
    """
    Mismo comportamiento que `print` pero con un
    primer parámetro para indicar de qué color se
    imprimirá el texto.

    Si la constante TERMINAL_SIN_COLOR es True,
    esta función será exactamente equivalente
    a utilizar `print`.
    """
    if TERMINAL_SIN_COLOR:
        print(*args, **kwargs)
    else:
        print(color, end="")
        print(*args, **kwargs)
        print(COLOR_RESET, end="", flush=True)


def main():
    tests_fallidos = []
    tests_a_correr = [int(t) for t in sys.argv[1:]]
    for i, test in [
        (i, test)
        for i, test in enumerate(TESTS)
        if not tests_a_correr or i + 1 in tests_a_correr
    ]:
        print(f"Prueba {i + 1 :02} - {test.__name__}: ", end="", flush=True)
        try:
            test()
            print_color(COLOR_OK, "[OK]")
        except AssertionError as e:
            tests_fallidos.append(test.__name__)
            print_color(COLOR_ERR, "[ERROR]")
            print_color(COLOR_ERR, " >", *e.args)
            break
        except Exception:
            tests_fallidos.append(test.__name__)
            print_color(COLOR_ERR, "[BOOM - Explotó]")
            print("\n--------------- Python dijo: ---------------")
            traceback.print_exc()
            print("--------------------------------------------\n")
            break

    if not tests_fallidos:
        print()
        print_color(COLOR_OK, "###########")
        print_color(COLOR_OK, "# TODO OK #")
        print_color(COLOR_OK, "###########")
        print()
    else:
        print()
        print_color(COLOR_ERR, "##################################")
        print_color(COLOR_ERR, "              ¡ERROR!             ")
        print_color(COLOR_ERR, "Falló el siguiente test:")
        for test_con_error in tests_fallidos:
            print_color(COLOR_ERR, " - " + test_con_error)
        print_color(COLOR_ERR, "##################################")
        print(
            "TIP: Si la información de arriba no es suficiente para entender "
            "el error, revisá el código de las pruebas que fallaron en el "
            "archivo sixteen_test.py."
        )


main()