# Taller de Microarquitectura
# Organización del Computador

El presente taller consiste en analizar y extender una micro-arquitectura diseñada sobre el simulador *Logisim-evolution*. Se buscará codificar programas simples en ensamblador, modificar parte de la arquitectura y diseñar nuevas instrucciones.

El simulador [logisim-evolution](https://github.com/logisim-evolution/logisim-evolution/) se ejecuta desde una terminal con el siguiente comando: `logisim-evolution`.

Para este taller utilizaremos mayoritariamente el modo simulación. Sobre todo las opciones de _Enable clock ticks_.

Además utilizaremos el componente memoria RAM, que inicia con todas sus posiciones en 0 y dos memorias ROM cuyo valor puede ser cargado desde un archivo desde la opción _Contents→Open..._.

Para la entrega de las respuestas a preguntas de elaboración se debe utilizar un archivo en formato Markdown llamado `SOLUCION.md` (crearlo en la carpeta principal del TP). Pueden encontrar una guía al formato en [aquí](https://docs.github.com/es/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax). En ese formato es posible también generar gráficos mediante el complemento Mermaid. Quienes deseen utilizarlo pueden encontrar una guía en [aquí](https://github.blog/2022-02-14-include-diagrams-markdown-files-mermaid/).

## Procesador OrgaSmall

Las características del procesador **OrgaSmall** son las siguientes:

- Arquitectura *von Neumann*, memoria de datos e instrucciones compartida.
- 8 registros de propósito general, `R0` a `R7`.
- 1 registro de propósito específico PC.
- Tamaño de palabra de 8 bits y de instrucciones 16 bits.
- Direcciones de 8 bits.
- Direccionamiento a Byte.
- Bus de 8 bits.
- Diseño microprogramado.

Se adjunta como parte de este taller las hojas de [documentación](documentacion/img/arquitectura_micro.pdf) del procesador **OrgaSmall**. En ellas se detalla el funcionamiento de los distintos módulos que lo componen. 

## Secuenciales

**Transferencia entre registros (repaso de secuenciales)**. 

El componente llamado `regBank` disponible en el archivo `secuenciales.circ` presenta la composición de varios componentes.  Tiene internamente 3 instancias del componente llamado `regZ`.

  Analizar el componente `regZ` y responder:
  1. ¿Cuáles son y qué representa cada entrada y cada salida del componente? ¿Cuáles entradas deben ser consideradas como de control?
  2. Las entradas `input_bit` y `en_input_bit` sirven para poder introducir en el circuito un valor arbitrario. Escribir una secuencia de activación y desactivación de entradas para que el registro `R1` pase a tener el valor `1`.

**NOTA:** Entregar la secuencia de activación de señales utilizando la herramienta [Wavedrom](https://wavedrom.com/tutorial.html). Esta herramienta permite graficar señales digitales y temporales. Para utilizarla, se debe ingresar el código en formato JSON en la página web y luego exportar la imagen. Dichas imágenes deben ser incluidas en el archivo `SOLUCION.md`.

  3. Dar una secuencia de activaciones que inicialmente ponga un valor `1` en `R0`, luego que este valor se transfiera a `R1`, luego que el valor de `R2` pase a `R0` y finalmente el valor de `R1` a `R2`.

## OrgaSmall

### 1. Análisis

- Recorrer la máquina y la hoja de datos, estudiar el funcionamiento de los circuitos indicados y responder las siguientes preguntas:
   * ¿Cuál es el tamaño de la memoria?
   * ¿Qué tamaño tiene el `PC`?
   * Observando el formato de instrucción y los CodOp de la hoja de datos: ¿Cuántas instrucciones nuevas se podrían agregar respetando el formato de instrucción indicado?

- Mirando los módulos indicados de hardware:

   * **`PC` (Contador de Programa):** ¿Qué función cumple la señal `inc`?
   * **`ALU` (Unidad Aritmético Lógica):** ¿Qué función cumple la señal `opW`?
   * **`microOrgaSmall` (`DataPath`):** ¿Para qué sirve la señal `DE_enOutImm`? ¿Qué parte del circuito indica que registro se va a leer y escribir?
   * **`ControlUnit` (Unidad de control):** ¿Cómo se resuelven los saltos condicionales? Describir el mecanismo.


## 2. Ensamblar y correr

Escribir en un archivo, compilar y cargar el siguiente programa:

```asm
JMP seguir

seguir:
SET R0, 0xFF
SET R1, 0x11

siguiente:
ADD R0, R1
JC siguiente

halt:
JMP halt
```

Para ensamblar un archivo `.asm` ejecutar el comando:

```sh
python assembler.py <archivo>.asm
```
    
Esto generará un archivo `.mem` que puede ser cargado en la memoria RAM de la máquina.

* Antes de correr el programa, identificar el comportamiento esperado.
* ¿Qué lugar ocupará cada instrucción en la memoria? Detallar por qué valor se reemplazarán las etiquetas.
* Ejecutar y controlar ¿cuántos ciclos de clock son necesarios para que este código llegue a la instrucción `JMP halt`?
* ¿Cuántas microinstrucciones son necesarias para realizar el ADD? ¿Cuántas para el salto?


## 3. Ampliando la máquina

Vamos a agregar nueva funcionalidad mediante instrucciones nuevas

> Nota1: Los siguientes ítems deben ser presentados mediante un código de ejemplo que pruebe la funcionalidad agregada. 

> Nota2: Tener en cuenta que si se agrega una operación, será necesario agregar el nombre mnemotécnico y el opcode en el archivo `assembler.py` y si se agregan operaciones en la ALU, de la misma manera agregarlas en el archivo `buildMicroOps.py`.

  Para generar un nuevo *set* de micro-instrucciones, generar un archivo `.ops` y traducirlo con el comando:

  ```sh
  python buildMicroOps.py <archivo>.ops
  ```
  Esto generará un archivo `.mem` que puede ser cargado en la memoria ROM de la unidad de control.

  * Sin agregar circuitos nuevos, agregar la instrucción `SIG`, que dado un registro aumenta su valor en 1. Esta operación **no** modifica los flags. Utilizar como código de operación el `0x09`.
  * Implementar un circuito que dados dos números $A_{7-0}$ y $B_{7-0}$ los combine de forma tal que el resultado sea $B_{1} A_{6} B_{3} A_{4} B_{5} A_{2} B_{7} A_{0}$, siendo el MSB $B_{1}$. Agregar la instrucción `MIX` que aplique dicha operación entre dos registros, asignándole un código de operación a elección.

### Opcionales

Otras modificaciones interesantes:
  * Sin agregar circuitos nuevos, agregar la instrucción `NEG` que obtenga el inverso aditivo de un número sin modificar los flags. Nota: el inverso aditivo de un número se puede obtener como `xor(XX, 0xFF) + 0x01`. Utilizar como código de operación el `0x0A`.
  * Modificar las instrucciones `JC`, `JZ`, `JN` y `JMP` para que tomen como parámetro un registro.
  * Agregar las instrucciones `CALL` y `RET`. Considerar que uno de los parámetros de ambas instrucciones es un índice de registro que se utilizará como *Stack Pointer*. Además, la instrucción `CALL` toma como parámetro un inmediato de 8 bits que indica la dirección de memoria a donde saltar.
  * Modificar el circuito agregando las conexiones necesarias para codificar las instrucciones `STR [RX+cte5], Ry` y `LOAD Ry, [RX+cte5]`. Este par de instrucciones son modificaciones a las existentes, considerando que `cte5` es una constante de 5 bits en complemento a dos.
  * Agregar instrucciones que permitan leer y escribir los `flags`. Describir las modificaciones realizadas sobre el circuito.
