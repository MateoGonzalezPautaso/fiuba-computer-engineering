# datalab

# Taller :: representación de datos

_Nota:_ esta es una traducción libre y concisa de las instrucciones originales
(en inglés) de los autores del lab. Dichas instrucciones se pueden encontrar en
el archivo [README.orig] en el repositorio.

## Manejo del repositorio

Para las instrucciones genéricas sobre cómo manejar el repositorio y realizar
la entrega, consultar el documento [Instrucciones de entrega](https://orgacomp.github.io/9557/entregas).
La información específica para esta consigna es:

  - rama que aloja el esqueleto: _datalab_
  - _pull request_ para la corrección: _compare: su-rama, base: datalab_
  - se permite `git push` a _head_: no

## Tarea

El archivo [bits.c] incluido en el esqueleto tiene una cantidad de funciones que
se deben implementar.  Cada una de estas funciones implementa una cierta
operación sobre enteros o números en punto flotante. Es el único archivo que se
debe modificar.

Las funciones aparecen en el archivo en orden de dificultad creciente. Se
incluye, para cada función en el archivo _bits.c_, una cabecera con los
siguientes apartados:

  - **Legal ops**: la lista de operadores permitidos
  - **Max ops**: el número máximo de operaciones
  - **Rating**: cantidad de puntos que la función contribuye al total de
    puntos del lab.


### Restricciones

El archivo _bits.c_ incluye al principio una explicación detallada de la
totalidad de las reglas (o restricciones) de programación. A modo de resumen:

  - se permite usar variables locales sin restricción (pero no variables
    globales). Esto quiere decir que no es necesario intentar “comprimir” la
    mayor cantidad de operaciones en una sola línea. **La asignación no
    contabiliza como “operación” para _max ops_.** Por ejemplo, a continuación
    se listan dos soluciones igualmente válidas para el mismo problema,
    calcular `2^x + 4`:

    ```c
    // Versión 1.
    // Max ops: 2.
    int pow2plus4(int x) {
        return (1 << x) + 4;
    }

    // Versión 2.
    // Max ops: 2.
    int pow2plus4(int x) {
        int potencia = (1 << x);
        int suma = potencia + 4;
        return suma;
    }
    ```

    (En este caso particular la primera versión es apropiada, pero para
    ejercicios de mayor puntaje se recomienda el uso de variables locales para
    mejorar la legibilidad.)

  - de necesitar el uso de constantes numéricas, solo se las permite en el
    rango de valores de 0 a 255 (inclusive)

**No se permite:**

  - estructuras de control: `if`, `while`, `for`, etc.
  - definir, o usar, macros
  - definir, o realizar llamadas a, funciones
  - el uso de conversiones explícitas entre tipos _(casts)_
  - uso de variables de tipo distinto a `int` (o `unsigned` para las funciones
    de punto flotante)
  - **cualquier operador no incluido en la lista de _Legal ops_ de la función.**


### Restricciones relajadas para _float_

Sí se permite el uso de estructuras de control para las funciones de tipo
_float_ (las últimas del archivo). **Las constantes numéricas no pueden
ser de tipo _float_.**


## Pruebas automáticas

**Importante**: Instalen el siguiente paquete para poder compilar adecuadamente:

```
$ sudo apt install gcc-multilib
```

Se incluye en el archivo [tests.c] un número de pruebas para cada función. Las
mismas se pueden correr usando `make test`:

```
$ make test
...
Total points: ../33
```

### Comprobación de restricciones

Se incluye en el lab un programa llamado `dlc` que puede usarse para verificar
que la implementación de una función cumple con las restricciones de
programación. En otras palabras, `dlc` comprobará que solo se hace uso de
operadores permitidos, y que no se excede el máximo permitido:

```
$ ./dlc bits.c
dlc:bits.c:181:bitAnd: Illegal operator (||)
```

Se puede combinar `dlc` con `test` usando `make grade`:

```
$ make grade
1. Running './dlc -z' to identify coding rules violations.
2. Compiling and running './btest -g' to determine correctness score.
3. Running './dlc -Z' to identify operator count violations.
4. Compiling and running './btest -g -r 2' to determine performance score.
5. Running './dlc -e' to get operator count of each function.

Score = ../59 [../33 Corr + ../26 Perf] (.. total operators)
```

**IMPORTANTE:** `dlc` solo admite variables declaradas a comienzo de bloque.
Un error tal que:

```
$ ./dlc -z bits.c
bits.c:149: parse error
bits.c:150: undeclared variable `z'
```

significa que se declaró una variable a mitad de función, por ejemplo:

```c
int fun(int x, int y) {
    x += 1;
    y += 2;
    int z = ~x | ~y;  // ERROR: Variable a mitad de bloque
    return z;
}
```

La variable `z` debería declararse al comienzo:

```c
int fun(int x, int y) {
    int z;  // OK: Variable definida a comienzo de bloque
    x += 1;
    y += 2;
    z = ~x | ~y;
    return z;
}
```

**IMPORTANTE:** Si usan printf para debuggear, bien. Pero recuerden 2 cosas:
- No dejen los print's al momento de la entrega
- No es necesario que incluyan `<stdio.h>` en `bits.c`. Si lo hacen, va a traer problemas con `dlc`.

## Herramientas adicionales

Se incluyen dos programas adicionales, `ishow` y `fshow` que muestran la
representación de enteros y números en punto flotante, respectivamente. Es
particularmente útil para estos últimos pues se muestra la representación en
bits, así como el exponente, etc.

```
$ make
...
$ ./ishow 0x27
Hex = 0x00000027,	Signed = 39,	Unsigned = 39

$ ./ishow 27
Hex = 0x0000001b,	Signed = 27,	Unsigned = 27

$ ./fshow 0x15213243
Floating point value 3.255334057e-26
Bit Representation 0x15213243, sign = 0, exponent = 0x2a, fraction = 0x213243
Normalized.  +1.2593463659 X 2^(-85)

$ ./fshow 15213243
Floating point value 2.131829405e-38
Bit Representation 0x00e822bb, sign = 0, exponent = 0x01, fraction = 0x6822bb
Normalized.  +1.8135598898 X 2^(-126)
```

[bits.c]: ./datalab/bits.c
[tests.c]: ./datalab/tests.c
[README.orig]: ./datalab/README.orig
