<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP2

## Alumno: Mateo Gonzalez Pautaso - 111699 - magonzalezp@fi.uba.ar

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c tp2.c engine.o -o tp2
```

- Para ejecutar:

```bash
./tp2
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./tp2
```

##  Funcionamiento

Basicamente el codigo de tp2.c es el siguiente, intente modularizar la mayor cantidad de codigo en TDAs o librerias para que en esta parte sea lo mas legible posible. La funcion juego_crear() crea todas las variables y parametros necesarios para el juego, luego la funcion juego_menu() lee los ingresos por teclado del usuario y se ejecute hasta que el mismo quiera salir. Finalmente liberamos toda la memoria con juego_destruir y finalizamos la ejecucion del programa.

```c
#include "src/logica.h"

int main()
{
	juego_t *juego = juego_crear();
	juego_menu(juego);
	juego_destruir(juego);
	return 0;
}
```

El flujo del programa queda explicado en el siguiente diagrama

<div align="center">
<img width="70%" src="img/flujo_programa.svg">
</div>
&nbsp;

Los TDA implementados tienen sus pruebas en el respectivo apartado.

A lo largo del desarrollo del TP no fue tanta la tarea de debugging, claramente hubo momentos donde necesite hacerlo, pero mas que nada fue sentarse a pensar como encarar los problemas. No escribir tanto codigo a lo loco sino realmente escribir lo que queria e ir probado versiones, hasta llegara los objetivos logrando que el tp funcione.

## TDA Menu

Para el Menu decidi hacer un TDA basandome en el trabajo de Hash, ya que en cuanto a complejidades temporales es el mas rapido a la hora de buscar y ejecutar el valor asociado a la clave. Entonces todas las funciones del menu, basicamente son funciones de hash con algunas adaptaciones para ajustarlo a nuestros requerimientos.

__typedef struct menu menu_t__

Es la estructura utilizada para describir el menu, basicamente es un hash por dentro pero lo llamamos menu_t para que cumpla la funcion de tda. El usuario no conoce la estructura del mismo.

__typedef struct funcion funcion_t__

Es la estructura usada para guardar la funcion a ejecutar y el identificador de la misma, ya que al no poder guardar la funcion directamente por problemas del compilador, estamos obligados a usar esta estructura.

__menu_t *menu_crear()__

La funcion se encarga de asignar memoria para la estructura del menu y luego crea el hash utilizando la funcion del mismo. En caso de algun fallo, se libera toda la memoria y retorna NULL. La complejidad de la funcion es O(1).

__void funcion_destruir(void *funcion)__

La funcion recibe la funcion_t con la funcion destructora para poder liberar el identificador y posteriormente la funcion asociada a esta, es decir el par clave-valor del hash. La complejidad de la funcion es O(1),

__void menu_destruir(menu_t *menu)__

La funcion libera la memoria utilizada por el hash y luego la utilizada por el menu, por lo que la complejidad de la funcion es O(n).

__bool menu_agregar_opcion(menu_t \*menu, char \*opcion, char \*identificador, void (\*f)(void \*))__

La funcion se encarga de asignar memoria para funcion_t y para el identificador de la misma, copiando la informacion pasada por parametro. Posterior a esto se inserta en el hash la clave pasada por parametro como opcion asociada al valor funcion_t. Ante cualquier falla se libera la memoria y devuelve false. La complejidad de la funcion es O(n).

__bool menu_ejecutar_opcion(menu_t \*menu, char \*opcion, void \*ctx)__

La funcion busca el valor asociado a la clave pasada por parametro, si hay una funcion asociada a esta la ejecuta junto al contexto pasado por parametro, sino retorna false. La complejidad de la funcion es O(n).

__bool opcion_imprimir(char \*opcion, void \*valor, void \*ctx)__

La funcion se encarga de imprimir las opciones de la tabla de hash, es decir la opcion junto al identificador de la funcion. Esta funcion es pasada por parametro a la iteradora del hash, la complejidad de esta funcion es O(1).

__void menu_imprimir(menu_t \*menu, char \*titulo)__

La funcion imprime el titulo del menu, luego itera el hash aplicando la funcion mencionada anteriormente a cada par clave-valor para poder ser visualizado por pantalla, asi el usuario es capaz de ver las opciones disponibles. La complejidad de la funcion es O(n).

## TDA Pokedex

Para la Pokedex decidi hacer un TDA basandome en el trabajo de ABB, mas que nada porque un requerimiento a la hora de imprimir la pokedex era que sea en orden alfabetico. En principio lo había planteado con una lista, pero me di cuenta que tenia que hacer mas funciones auxiliares para lograr el objetivo. Entonces simplemente con recorrer el arbol inorden lograba lo mismo, porque los pokemones eran ingresados segun el nombre. Aparte no solo me beneficiaba de eso, sino que tambien las funciones del ABB tienen mejor complejidad temporal que las de lista.

__typedef struct pokedex pokedex_t__

Es la estructura utilizada para describir la pokedex, basicamente es un abb por dentro pero la llamamos pokedex_t para que cumpla la funcion de tda. El usuario no conoce la estructura del mismo.

__typedef struct pokemon pokemon_t__

Es la estructura utilizada para guardar los datos del pokemon y tambien la estructura a seguir por el archivo csv para que sea cargado correctamente.

__typedef struct posicion posicion_t__

Es la estructura utilizada para iterar sobre la pokedex, contiene la posicion actual y la buscada, ademas de un pokemon_t para guardar el mismo.

__pokedex_t *pokedex_crear()__

La funcion se encarga de asignar memoria para la estructura de la pokedex y luego crea el abb utilizando la funcion del mismo, ademas crea una tabla de hash con los colores para poder imprimir ocn formato. En caso de algun fallo, se libera toda la memoria y retorna NULL. La complejidad de la funcion es O(n), debido a la creacion de la tabla de colores.

__void liberar_pokemon(void *contenido)__

La funcion se encarga de liberar toda la memoria ocupada por el pokemon, es decir, su nombre, color y patron de movimiento. Finalmente libera el struct, la complejidad de la funcion es O(1).

__void pokedex_destruir(pokedex_t *pokedex)__

La funcion se encarga de liberar toda la memoria del abb, lo itera y a cada nodo le aplica la funcion mencionada anteriormente. Luego, libera toda la memoria ocupada por la tabla de colores y finalmente libera la pokedex. La complejidad de la funcion es O(n).

__bool pokedex_agregar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon)__

La funcion basicamente invoca a abb_insertar pasandole por parametro el pokemon, por lo que tiene una complejidad de O(n).

__bool pokedex_cargar_csv(pokedex_t *pokedex, const char *nombre_archivo, char separador)__

La funcion recibe la pokedex por parametro, junto al nombre del archivo y su separador. Recorre todas las lineas del archivo parseandolas, asigna los datos al pokemon y lo inserta en la pokedex. En caso de algun fallo siempre libera memoria, finalmente cierra el archivo. Para este momento la pokedex ya esta cargada con nuestros pokemones, la complejidad de la funcion es O(n^2).

__pokemon_t *pokedex_buscar_pokemon(pokedex_t *pokedex, char *nombre)__

La funcion busca el pokemon en el abb, recibe la pokedex y el nombre que se lo asigna a un pokemon_t auxiliar. Luego simplemente retorna el valor de abb_obtener casteado, por lo que la complejidad es O(n).

__bool iterar_hasta_posicion(void *pokemon, void *ctx)__

Es una funcion que itera hasta la posicion pasada por parametro, cuando llega al indice deseado asigna los datos al pokemon de la estructura y retorna false para frenar el recorrido del ABB. La complejidad de esta funcion es O(1).

__pokemon_t *pokedex_obtener_aleatorio(pokedex_t *pokedex)__

La funcion calcula una posicion aleatoria mediante rand() % abb_cantidad() para obtener un indice dentro de los rangos de la Pokedex, esta posicion obtenida es copiada a la estructura mencionada anteriormente. Luego se llama a la funcion abb_iterar_inorden() y finalmente se retorna el pokemon. La complejidad de la funcion es O(n).

__bool pokemon_imprimir(void *pokemon, void *colores)__

Esta funcion cumple un rol muy parecido a iterar_hasta_posicion() ya que es para pasarsela a la iteradora del abb, la funcion busca el valor asociado al nombre del color en la tabla de hash de colores. En caso que se encuentre el color, lo agrega al formato para imprimirlo, sino simplemente lo omite. Finalmente retorna true y la complejidad de la funcion es O(1), ya que el hash no sufre de rehash.

__void pokedex_imprimir(pokedex_t *pokedex)__

La funcion se encarga de imprimir todos los pokemones con el formato necesario, esto lo logra llamando a abb_iterar_inorden() con la funcion mencionada anteriormente. La complejidad de esta funcion es O(n).

## Utilidades

Este apartado no cumple la funcion de un TDA, sino mas de una libreria para poder modularizar el codigo principal de logica y que no quede tan cargado.

__int max(int a, int b) y int min(int a, int b)__

Las funciones solamente retornan el mayor o menor valor entre los dos pasados por parametro, las complejidades son O(1).

__char convertir_a_mayuscula(char c)__

La funcion convierte a mayuscula el caracter pasado por parametro, en un principio estaba usando toupper() pero luego decidi cambiar por esta. Si el caracter esta entre los valores ASCII de letras, resta al valor del caracter el inicio 'a' menos el final 'A'. Asi obtenemos el valor de la mayuscula y lo retornamos, la complejidad de la funcion es O(1).

__void lista_vaciar_sin_destruir(Lista \*lista, void (\*destructor)(void \*))__

La funcion se encarga de vaciar la lista para poder reinicar el juego, mientras la lista tenga elementos va a quitarlos desde el principio para que tenga la menor complejidad posible. Quitandolos desde el principio evitamos recorrer toda la lista, ademas si la funcion destructora es valida se la aplica al elemento quitado. La complejidad de la funcion es O(n).

__bool lista_eliminar(Lista *lista, void \*elemento)__

La funcion elimina un elemento de la lista, esta primitiva no estaba en el TDA lista por lo que tuve que crearla. Primero recorre la lista llamando a la funcion lista_obtener_elemento(), en caso que coincida el elemento encontrado con el que queremos eliminar llama a lista_quitar_elemento(). A esta funcion le pasamos la posicion que obtenemos con el iterador para poder eliminarlo. La complejidad de la funcion es O(n^2) ya que primero obtiene el elemento y luego lo quita.

__hash_t *hash_colores()__

La funcion crea la tabla de colores, utiliza el color como clave y el valor asociado a este es la clave ANSI del mismo. Esta se usa en todo el programa para poder imprimir con colores y que quede un formato vistoso. La complejidad de la funcion es O(1).

## Logica

__typedef struct juego juego_t__

Es la estructura utilizada para guardar toda la informacion del juego, desde las listas de pokemones, el menu, la semilla, la pokedex, etc. Poner todo en una estructura facilita que las funciones reciban el juego en si y no todos los elementos individuales.

__typedef struct pokemon_tablero pokemon_tablero_t__

Es la estructura utilizada para operar sobre los pokemones en la logica del juego, en esta guardamos la posicion del mismo, el indice del patron para poder seguir al mismo en los movimientos y basicamente los mismos datos que en la pokedex.

__typedef struct jugador jugador_t__

Es la estructura utilizada para guardar los datos sobre el jugador, sobre todo la posicion y las iteraciones del mismo para mostrar por pantalla. El bool movimiento es para asegurarse que los pokemones se muevan solo cuando el jugador se mueve, ademas esta el ultimo pokemon capturado para poder imprimirlo por pantalla.

__typedef struct combo combo_t__

Es la estructura utilizada para guardar los indices de la racha mas larga, asi luego cuando la iteramos tenemos desde donde hasta donde imprimir la lista de pokemone atrapados.

__typedef struct elemento elemento_t__

Es la estructura utilizada para guardar el elemento en cada posicion de la matriz, esto es para que sea mas sencilla la forma de impresion y pasaje de parametros. Tenemos el caracter, el color y el elemento, que en este caso puede ser el jugador o un pokemon_tablero.

__juego_t *juego_crear()__

La funcion basicamente se encarga de asignar toda la memoria necesaria para la estructura del juego y los componentes de la misma, claramente en caso de fallo se libera toda la memoria y retorna NULL. Posterior a esto se asignan las variables tanto del jugador como del juego y se carga el csv de la pokedex a la misma, se agregan las opciones y finalmente se retorna el juego.

__void iniciar_juego(juego_t *juego, jugador_t *jugador)__

La funcion se encarga de asignar la mayoria de las variables al jugador y juego, mas que nada las inicializa en valores false, NULL o 0 para evitar problemas cuando se acceda a ellas.

__void juego_destruir(juego_t *juego)__

La funcion libera toda la memoria utilizada por los componentes del juego y el jugador en si, la misma se utiliza cuando se finaliza la ejecucion o en caso de fallo.

__void juego_menu(juego_t *juego)__

Es la funcion asociada a recibir la entrada por teclado del usuario de la opcion del menu a ejecutar, primero imprime el menu con el titulo y lee la entrada, en caso que sea valida la convierte a mayuscula ya que el menu debe ser case insensitive. Si la opcion coincide con una del menu la ejecuta, sino nos muestra que no es valida y vuelve al inicio. Cuando ejecuta la opcion, entra a las funciones asociadas a la misma.

__void mostrar_pokedex(void *ctx)__

Cuando en el menu se ingresa la opcion P, se ejecuta esta funcion asociada a esa clave. Esta funcion imprime el titulo, llama a pokedex_imprimir() y finaliza su ejecucion volviendo al menu.

__void salir(void *ctx)__

Cuando en el menu se ingresa la opcion Q, se ejecuta esta funcion que solo imprime ese mensaje por consola pero cuando vuelve al menu, como coincide con la condicion de corte se finaliza la ejecucion.

__void jugar_con_semilla(void *ctx)__

Cuando el usuario ingresa S, significa que quiere jugar con una semilla conocida para repetir alguna partida. El usuario ingresa la semilla por consola y hasta que no coincide con el formato no se considera valida, cuando si coincide sale del while. Finalmente se llama a la funcion jugar() junto con la semilla ingresada.

__void jugar_sin_semilla(void *ctx)__

Cuando el usuario ingresa J, se llama a jugar() con la semilla siendo 0 para calcularla en la funcion mencionada.

__void jugar(juego_t *juego, long int semilla)__

Si la semilla es 0 porque la opcion fue J, se calcula una semilla y se elige un valor random para que sea mas aleatorio y no tan lineal como cuando depende del tiempo. Una vez con la semilla, sea calculada o pasada por parametro, se inicializa el srand() y se asigna la variable. Luego se inicializa la lista de pokemones para alimentar el tablero y llama a la funcion que se encarga del loop del juego game_loop(), una vez finalizada la partida imprime el scoreboard con los datos requeridos. Al llamar a la funcion iniciar_juego() reinciamos las estadisticas para futuras partidas y se vacian ambas listas, la de pokemones y la de pokemones atrapados.

__void destruir_pokemones_tablero(Lista *pokemones_tablero, Lista *pokemones_atrapados)__

Basicamente la funcion se encarga de destruir las listas de pokemones y pokemones atrapados, esta funcion se usa en caso de fallo en las asignaciones de memoria, ya que si no ocurre esto simplemente la vaciamos.

__pokemon_tablero_t *iniciar_pokemon(juego_t *juego)__

La funcion se encarga de reservar la memoria para el pokemon que va a estar en el tablero, primero obtiene un pokemon aleatorio de la Pokedex y luego copia las referencias de las variables a nuestro pokemon_tablero_t. Finalmente retorna la variable.

__void iniciar_pokemones(Lista *pokemones_tablero, juego_t *juego)__

Utilizando la funcion modularizada mencionada anteriormente, recorre un ciclo y asigna la memoria para la cantidad de pokemones requeridos dentro del tablero. A medida que obtiene cada pokemon lo agrega al final de la lista de pokemones, siempre en caso de fallo se libera la memoria.

__void mover_pokemon(pokemon_tablero_t *pokemon, int movimiento_jugador_x, int movimiento_jugador_y)__

Como dice su nombre, mueve al pokemon segun su patron de movimiento. Para esto va iterando sobre este con el indice y lo divide por el modulo del largo del string. Una vez obtenemos la letra para el movimiento hacemos un switch case para moverlo, tambien obtenemos los movimientos del jugador por si hay que replicarlos. En este caso decidi hacer un switch case ya que una tabla de hash me parecia agregar demasiada complejidad para algo sencillo. Finalmente actualiza las variables de posicion del pokemon.

__void mover_pokemones(Lista *pokemones, int movimiento_jugador_x, int movimiento_jugador_y)__

Utilizando la funcion modularizada mencionada anteriormente, recorre la lista de los pokemones presentes en el tablero con un iterador y los va moviendo hasta llegar al fin de la lista. 

__bool combo(pokemon_tablero_t *p1, pokemon_tablero_t *p2)__

Es una funcion para simplificar codigo, ya que hay que revisar varias veces si hay un combo, es decir misma inicial y/o color de pokemon para aumentar el multiplicador. Si ambos pokemones son validos y si las variables son true, hay combo y devuelve true, en otro caso devuelve false. 

__void actualizar_puntaje(juego_t *juego, pokemon_tablero_t *pokemon, int indice_pokemon)__

Se encarga de actualizar los puntajes del juego, si el jugador no capturo ningun pokemon asigna al multiplicador como 1 y el combo como 0. Una vez que el jugador capturo algo, verifica que haya combo, en caso de haberlo aumenta el multiplicador y la longitud del maximo combo. Si lo capturado no produce combo, reinicia el multiplicador y el combo.

Una vez salido de estas condiciones suma los puntos del pokemon multiplicados y los añade al contador del juego, ademas de actualizar el ultimo pokemon capturado.

__void procesar_entrada_jugador(int entrada, juego_t *juego)__

Es una de las funciones principales del juego, verifica si la entrada por teclado coincide con los valores de algunas de las flechas, si es asi modifica el valor de movimiento del jugador. Si estos valores son distintos de 0, es decir se movio, aumenta las iteraciones y asigna true al bool de movimiento para poder mover los pokemones mas adelante.

Luego pasa a iterar la lista de pokemones del tablero, en caso que alguno comparta posicion con el jugador, lo atrapa. Al pasar esto lo elimina de la lista de pokemones del tablero y lo inserta en la lista de pokemones atrapados, posteriormente obtiene un nuevo pokemon aleatorio y lo inserta al tablero. Finalmente actualiza los puntajes y destruye el iterador.

Para finalizar esta funcion, si hubo movimiento por parte del jugador, llama a la funcion encargada de mover los pokemones y reinicia la variable de movimiento.

__void imprimir_cabecera(juego_t *juego)__

La funcion se encarga de imprimir la cabecera del tablero, basicamente imprime las instrucciones, la semilla utilizada para el usuario y los valores de la partida como iteraciones y tiempo restante. Ademas aprovechamos para calcular el tiempo transcurrido.

__void imprimir_tablero(juego_t *juego)__

La funcion se encarga de iniciar la matriz de elemento_t mediante memset, pone todos los valores en 0, en la posicion del jugador pone su elemento asociado. Luego de esto itera la lista de pokemones a estar presentes en el tablero y para cada uno de estos crea un elemento_t asignandole las variables. Una vez termina de iterar la lista, la matriz ya queda lista para impresion.

El proximo paso es imprimir los bordes superiores del tablero, luego se encarga de imprimir todas las filas dentro de los parametros. Si en la posicion iterada hay un caracter, lo imprime con el color deseado segun la tabla, en caso contrario imprime un espacio vacio. Cuando termina de recorrer todos los espacios imprime el borde inferior. Ademas en caso de tener un ultimo pokemon capturado lo imprime.

__void imprimir_racha(juego_t *juego, combo_t *combo)__

La funcion se encarga de imprimir la racha una vez finalizado el juego, itera la lista de pokemones atrapados y si nos encontramos entre los indices del combo_t imprime el pokemon asociado a este, ademas del puntaje multiplicado que nos proporciono.

__void imprimir_final(juego_t *juego)__

La funcion se encarga de imprimir toda la informacion cuando se finaliza la partida, si no se atrapo ningun pokemon lo imprime por pantalla y simplemente finaliza la ejecucion. En caso contrario, imprime el maximo multiplicador alcanzado con el total de puntos. Luego imprime el titulo para la racha de pokemones y pasa a iterar la lista de pokemones atrapados para obtener los indices. Si hay combo entre los pokemones, incrementa la longitud del combo_actual y si no lo hay (finalizo la racha) verifica cual de las iteraciones es la mas grande. Asi obtiene la mejor de todas las rachas, cada vez que esta finaliza reinicia las longitudes e indices.

Una vez obtenidos los indices los guarda en combo_t y se lo pasa por parametro a la funcion mencionada anteriormente para imprimir los pokemones en si. Esta funcion aunque parezca sencilla diria que es de las que mas me costo del trabajo, intente buscar mejores formas para hacerla pero realmente me quede con iterar la lista dos veces.

__int jugar_logica(int entrada, void *ctx)__

Es la funcion principal para el juego, es donde todas las demas funciones descriptas convergen para darle vida al proyecto. Primero que nada limpia la pantalla y procesa la entrada del jugador, en caso de movimiento tambien se mueven los pokemones. Esta funcion se llama dentro de game_loop que tiene una tasa de 5 calls por segundo, por lo que el tiempo no seria igual al contador. Por esto cuando imprimimos la cabecera, dividimos al contador en 5 para obtener un aproximado del tiempo real escurrido.

Luego pasa a imprimir la cabecera del tablero y el tablero en si, ademas se encarga de esconder el cursor que va a volver a aparecer una vez salido del juego. Al principio cuando tenia bugs haciendo el codigo, tenia que estar ejecutando "reset -c" desde la terminal porque me desaparecian los caracteres que escribia. Tarde un tiempo en darme cuenta de este bug, había comentado la funcion de mostrar el cursor sin querer, por lo que claramente nunca iba a reaparecer.

Si el tiempo llega a 60 segundos, retorno un 1 simulando que se ingreso una q por teclado, asi se sale del loop, se imprimen los valores finales y vuelve al menu.