<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA ABB

## Alumno: Mateo Gonzalez Pautaso - 111699 - magonzalezp@fi.uba.ar

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c tp_abb.c -o abb
```

- Para ejecutar:

```bash
./abb ejemplos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./abb ejemplos/pokedex.csv
```

---

##  Funcionamiento

<div align="center">
<img width="70%" src="img/flujo_programa.svg">
</div>
&nbsp;

El programa recibe el nombre de un archivo por parametro, verificando que efectivamente se haya pasado uno y en el caso que no se haya hecho, imprimira un mensaje de error y terminara la ejecución del programa. Luego lo abre con la función abrir_archivo_csv() asignandole memoria, la funcion retorna un struct archivo_csv donde se almacena el separador y un FILE* a un archivo csv.

Posterior a esta tarea se crea una pokedex con abb_crear() y se asigna memoria nuevamente, dicha funcion retorna un struct abb.

Como ambas funciones que crean las estructuras asignan memoria, verificamos que esta misma no haya fallado y seguimos con la ejecución de nuestro programa.

<div align="center">
<img width="70%" src="img/struct_tp.svg">
</div>
&nbsp;

Seguidamente se crea un arreglo de punteros a funciones, con estas mismas se castearan las columnas del archivo csv a los datos requeridos por el programa. Dichas funciones deben estar en el mismo orden de aparición que las columnas del archivo a procesar para evitar problemas de tipos de datos distintos.

**Pikachu;E;20;15;17**

Como nuestro archivo tiene lineas de este formato, el orden de aparicion de las funciones debe ser tal cual estan implementadas en tp_abb.c, si nuestro archivo tuviese distinta disposición habría que ajustar el orden. Luego de esto, se crean las variables donde se copiara la informacion de las columnas de los archivos. Cuando creamos el arreglo de punteros a ctx almacenamos las direcciones de memoria de las variables para cargar los pokemones al abb pokedex una vez sean parseadas correctamente.

Al poner la función leer_linea_csv() que devuelve la cantidad de columnas leidas correctamente, el programa se ejecutara hasta que se produzca una falla o se llegue al final del archivo. Pero esta función no solo retorna este dato sino que también se encarga de leer linea a linea el archivo, separar estas mismas segun el separador y armar un char **split_strings donde estaran los datos de las variables de void \*ctx[5]. Una vez finalizadas estas tareas, libera la memoria del char\*\* y retorna el dato esperado. En el caso que alguna asignación de memoria falle, alguna función sea NULL o el parseo no se ejecute correctamente, finaliza la ejecución y retorna en que columna fallo.

<div align="center">
<img width="70%" src="img/diagrama_split.svg">
</div>
&nbsp;

Una vez los datos fueron cargados a las variables, se asigna memoria para el struct pokemon * para poder ser agregado al abb pokedex. Los datos de las variables y el pokemon son pasados por parametro a la funcion asignar_datos_pokemones() y luego este pokemon es pasado a abb_insertar(). Se repite el ciclo while sucesivamente hasta terminar de leer todo el archivo csv.

Al momento de salir del while, se recurre a la funcion cerrar_archivo_csv() para liberar toda la memoria utilizada por el archivo csv. Luego se llama a la funcion menu_usuario() que se encarga de:
  - Pedir al usuario que ingrese un nombre y buscarlo en la Pokedex ABB.
  - Imprimir los pokemones por pantalla en un formato agradable.
  - Salir del programa.

<div align="center">
<img width="70%" src="img/menu_usuario.png">
</div>
&nbsp;

Una vez se finaliza la ejecucion del menu, se recurre a la funcion abb_destruir_todo() que recibe al ABB Pokedex y a la funcion destructora liberar_pokemon() para vaciar el contenido del nodo y liberar toda memoria utilizada.

En cuanto al desarrollo del trabajo practicamente todas las funciones tienen su version recursiva, que es el nombre de la version y se le agrega recursivo al final. Esto es debido a que es mas comodo ir iterando sobre nodos a que manipular el arbol directamente, las funciones sirven de "fachada" para declarar variables y pasarselas por parametro a la recursividad. En cuanto al usuario el no se entera de esto, ya que son implementaciones internas de abb.c, simplemente tiene que usar las funciones del abb.h.

La funcion con la que tuve mas complicaciones definitivamente fue abb_quitar() a diferencia del resto, en un principio no hacía verificaciones una vez guardado el contenido entonces este se sobreescribia con el del predecesor. Luego use nodos auxiliares pero tampoco podia solucionarlo ya que liberaba la memoria y luego queria acceder a esta, entonces valgrind siempre tiraba errores para acceder a tal direccion. Otro proboema que tuve pero totalmente por apurado fue leer rapido el enunciado y en vez de utilizar al precesor inmediato, utilizaba al sucesor inmedianto, claramente fallaban todas las pruebas. La solución final para esta funcion fue implementar muchas partes que había hecho por separado y llegar a una conclusión final para que funcione, las mayorias de las entregas al bot eran por este motivo. Implemente muchas mas funciones para probarla hasta que pase las mias y las de la catedra.

Otra funcion que tuve complicaciones fue para vectorizar, en un principio no había reutilizado las funciones de iterar porque no me di cuenta pero luego en clase nombraron este caso. Por lo que tuve que implementar una funcion auxiliar para pasarsela al iterador por parametro, pase de un void* a un struct por temas de legibilidad y comodidad. En un principio no tenía problemas pero cuando hice el cambio de estructura, como las de iteracion devuelven los nodos iterador, devolvía 1 iteracion "demas". Despues de implementar pruebas me di cuenta que tenia que devolver la posicion en vez de la cantidad iterada, una vez realizado el cambio pasaron todas las pruebas.

Con el resto de las funciones no tuve muchos mas problemas que pensar un rato y hacer bocetos de funciones hasta llegar a la version final.

## Respuestas a las preguntas teóricas

<div align="center">
<img width="70%" src="img/arboles.svg">
</div>
&nbsp;

Es muy importante la distincion entre estas estructuras de datos para nuestras implementaciones, porque depende el proyecto o necesidades del mismo nos va a convenir utilizar una u otra. Cada estructura tiene su ventaja respecto a la otra y es lo que hay que considerar para futuras aplicaciones.

## Arbol n-ario o general

Un arbol cuenta con una jerarquia en la estructura de datos, es una coleccion de nodos conectados entre si y cada uno puede tener hijos que a su vez tienen mas conexiones y asi sucesivamente. La cantidad de hijos es un numero arbitrario que una vez definido, hay que respetarlo. Estos arboles suelen ser utilizados en aplicaciones como sistemas de archivos en donde un directorio puede tener muchas subcarpetas o en estructuras mas complejas, sacrificamos eficiencia en las funciones por personalizacion. Los arboles tienen las siguientes características:

  -   Raíz: nodo mas alto o en el primer nivel del arbol, desde este punto se recorre y es al unico que se tiene acceso directo
  -   Nodo: es el elemento del arbol, dentro de este se pueden almacenar los elementos y las conecciones a los demas nodos
  -   Subarbol: nos paramos en un nodo y podemos ver mas arboles debajo de este 
  -   Padre: es el nodo superior del cual estan conectados los hijos
  -   Hijo: los nodos debajo de un nodo se los llama de esta forma
  -   Hoja: son los nodos sin hijos
  -   Altura de un arbol: son los niveles de nodos vistos verticalmente, si la raiz es nivel 1, su hijo sera nivel 2 y asi sucesivamente

La raíz va a tener cero o muchos subarboles no vacios T1, T2, ..., Tk.

__crear__

La complejidad temporal de una funcion para crear un arbol de este estilo es O(1), ya que solo hay que asignar memoria y guardar los contenidos en las variables.

__destruir__

Destruir un arbol implica recorrer todos los hijos del mismo e ir liberando la memoria de los nodos, por lo que la complejidad sería O(c) siendo c la cantidad de hijos, asi formaría parte de la familia O(n).

__insertar__

Para la funcion de insertar hay que asumir un criterio a la hora de insertar, sino no podríamos definir la complejidad de la misma. Supongamos que es un array como en un heap y lo queremos insertar al final de este, la complejidad sería de O(c) siendo c la cantidad de nodos que debe recorrer, por lo que la complejidad sería O(n). El criterio podría variar, podría insertarse en el primer nodo disponible, usarse un criterio de ABB o alguna otra personalizacion.

__borrar__

Si consideramos la estructura mencionada anteriormente, a la hora de borrar el recorrido sería muy parecido ya que hay que recorrer todos los nodos y en caso de tener hijos, reconectarlos. Por esto mismo la complejidad seria O(c) siendo c la cantidad de nodos y formaria parte de O(n). También habría que tener en cuenta la funcion comparadora para ver si el elemento a borrar es ese efectivamente, para estos casos suponemos que es O(1).

__buscar__

A la hora de buscar hay que comparar el contenido de los nodos con el buscado, por lo que en el peor de los casos hay que recorrer todos los nodos. Suponiendo que la complejidad de la funcion comparadora es O(1) y c la cantidad de nodos dentro del arbol, la complejidad sería O(c).

__vacio__

La complejidad de esta funcion es facil ya que sería solo recurrir al valor que lleva la cuenta de los nodos o ver si la raíz es nula, por lo que sería O(1).

__recorrer__

La funcion recorrer tiene distintas implementaciones dependiendo si es recorrido preorden, inorden o postorden. De todos modos es necesario recorrer cada nodo del arbol para cumplir con los requisitos, por lo que la complejidad seria como fue mencionada en otros casos O(c), formando parte de O(n).

## Arbol binario

Son arboles muy parecidos a los mencionados anteriormente con la diferencia que los nodos de estos tienen conexiones a dos nodos, derecho e izquierdo. No siempre tiene que tener hijos pero como maximo va a tener dos y asi aumenta la eficiencia de las funciones a implementar.

__crear__

Como fue explicado en arbol, la complejidad es la misma, siendo esta O(1).

__destruir__

Como fue explicado en arbol, la complejidad es la misma ya que de todos modos hay que recorrer a los nodos, entonces la complejidad sería O(n).

__insertar__

A diferencia de ABB, no hay un criterio de insercion por lo que tenemos que definir uno, si supieramos donde hay que insertarlo especificamente sería O(1) pero si seguimos una estructura parecida a los ABB, la complejidad de insercion seria O(h). h serían los niveles o nodos que recorre antes de encontrar donde insertarse, por lo que la complejidad seria O(n).

__borrar__

Si consideramos la estructura del ABB, hay que tener en cuenta si el nodo tiene cero, uno o dos hijos ya que esto modificaría la complejidad. En todos los casos hay que considerar la peor situacion, donde el nodo tiene dos hijos, ya que hay que buscar al predecesor inmediato y asignarlo. Por lo que la complejidad se iria a O(n).

__buscar__

Para buscar un elemento en una estructura de ABB por suposicion, hay que comparar el elemento con el del nodo actual e ir redireccionando segun si es mayor o menor. Hasta dar con el objetivo hay que recorrer h niveles, si la funcion comparadora es O(1) la complejidad es O(h) y forma parte de O(n).

__vacio__

La complejidad de esta funcion es facil ya que sería solo recurrir al valor que lleva la cuenta de los nodos o ver si la raíz es nula, por lo que sería O(1).

__recorrer__

La funcion para recorrer el arbol binario con una estructura ABB necesita iterar cada nodo, por lo que si necesita recorrer cada uno de estos, la complejidad seria O(c) siendo c la cantidad de nodos y conviertiendose en O(n).

## Arbol binario de busqueda

Es similar al arbol binario pero con la diferencia que en este los nodos estan organizados segun un criterio, esto nos permite poder comparar elementos y buscarlos de una forma mas eficiente aun. Los elementos mas grandes van a los subarboles derechos y los elementos mas chicos van en los subarboles izquierdos. Estos arboles son muy utilizados para busquedas binarias, en el caso que el arbol este balanceado este proceso es todavia aun mas rapido llegando a una complejidad de O(log(n)), por ejemplo para buscar una direccion de correo en una agenda digital.

Las complejidades de las funciones basicas para un ABB ya estas explicadas en el apartado de __ABB__.

### ABB

__typedef struct abb abb_t__

Es la estructura utilizada para describir el arbol binario de busqueda, tiene un size_t nodos para llevar cuenta de la cantidad de los mismos dentro del arbol y un nodo_t *raiz para apuntar a la raiz. Finalmente cuenta con una funcion int (\*comparador)(void\*, void\*) para poder comparar los contenidos a la hora de ser ingresados al arbol y poder seguir un formato preestablecido.

__typedef struct nodo nodo_t__

Es la estructura utilizada para describir el nodo, tiene un void *elemento para apuntar al contenido y dos struct nodo * donde uno apunta a la rama derecha y otro a la izquierda para formar el arbol.

__abb_t* abb_crear(int (\*comparador)(void\*, void\*))__

La funcion se encarga de crear el arbol, primero revisa si la funcion comparadora es no nula y luego asigna la memoria para el mismo. En caso que esta falle, retorna NULL, en caso contrario almacena la funcion comparadora y retorna la estructura. Como calloc es O(1) y el resto son instrucciones simples, la funcion tiene una complejidad O(1).

__void destruir_todo_recursivo(nodo_t \*nodo, void (\*destructor)(void \*))__

La funcion se encarga de liberar la memoria ocupada por el arbol mediante un recorrido postorden recursivo del mismo, si la funcion destructora es no nula libera el contenido del nodo y luego pasa a liberar al mismo. Esto lo hace recorriendo el nodo izquierdo, derecho y luego el actual. La complejidad temporal depende de la funcion destructora y de la cantidad de nodos, como la implementacion de la destructora es O(1), la funcion tiene una complejidad O(n).

__void abb_destruir(abb_t\* abb)__

La funcion se encarga de destruir el arbol binario cuando no se asigna memoria para el contenido del nodo, para esto se llama a la funcion recursiva destruir_todo_recursivo() pasandole por parametro la raiz del nodo y una funcion nula comparadora. Como la complejidad de la funcion recursiva es O(n) y free() es O(1), la funcion seria O(n). 

__void abb_destruir_todo(abb_t\* abb, void (\*destructor)(void\*))__

La funcion tiene la misma implementacion que abb_destruir() con la diferencia que cuando llama a destruir_todo_recursivo() aparte de pasarle la raiz, tambien le pasa una funcion destructora no nula para que pueda ser utilizada a la hora de liberar el contenido del nodo. Como la complejidad de la funcion recursiva es O(n) y free() es O(1), la funcion seria O(n).

__nodo_t \*buscar_predecesor_inmediato(nodo_t \*nodo)__

La funcion se encarga de buscar el predecesor inmediato de la rama izquierda del nodo pasado por parametro, se usa para tener referencia para reconectar el arbol cuando se quita un nodo. La complejidad de esta funcion depende de la cantidad de nodos de la rama derecha o la altura de la misma, por lo que la complejidad seria O(h) siendo h la altura y formaria parte de la familia O(n).

__nodo_t \*borrar_nodo_recursivo(nodo_t \*nodo, void \*buscado, int (\*comparador)(void \*, void \*), void **encontrado, bool \*centinela)__

La funcion busca al nodo recursivamente comparando el contenido del mismo con el contenido buscado, si el buscado es mayor al del nodo lo redirige a la rama derecha o viceversa. Una vez encontrado guarda el contenido si no es nulo y analiza los casos donde el nodo tenga cero, uno o dos hijos. En caso que tenga cero o uno hijos retorna la rama contraria usando un puntero auxiliar y libera el nodo, si tiene dos hijos el caso es mas complicado. Para eliminar un nodo con dos hijos es necesario busca el predecesor inmediato, luego reasignar el elemento del nodo al del predecesor y llamar nuevamente a la funcion con el elemento del predecesor y con encontrado en NULL para que no se reasigne el contenido en encontrado. La complejidad de la funcion dependera de los hijos del nodo, si tiene cero o uno es una complejidad de O(1) pero en el peor de los casos con dos hijos se llama a buscar_predecesor_inmediato() que tiene complejidad O(n). Por lo que la complejidad de la funcion seria O(n).

__bool abb_quitar(abb_t \*abb, void \*buscado, void **encontrado)__

La funcion se encarga de borrar al nodo llamando a la funcion recursiva mencionada anteriormente, luego reasigna la raiz y resta la cantidad de nodos dentro del arbol. La complejidad depende de la funcion recursiva que es O(n) por lo que la complejidad seria (n).

__nodo_t \*insertar_recursivo(nodo_t \*raiz, void \*elemento, int (\*comparador)(void \*, void \*), bool \*centinela)__

La funcion inserta el nodo comparando el contenido a ingresar con el contenido del nodo, si el elemento es mayor lo redirecciona a la rama derecha o viceversa. Una vez llega al objetivo, el nodo en esa posicion es nulo por lo que asigna memoría para este y guarda el contenido dentro de el retornando el nodo. La complejidad de la funcion es O(c) siendo c la cantidad de nodos a recorrer hasta llegar a destino, o la altura recorrida, por lo que la complejidad de la funcion es O(n).

__bool abb_insertar(abb_t \*abb, void \*elemento)__

La funcion se encarga de insertar un nodo llamando a la funcion recursiva mencionada anteriormente, luego reasignala raiz y suma la cantidad de nodos dentro del arbol. La complejidad depende de la funcion recursiva que es O(n), por lo que la complejidad de esta sería O(n) también.

__void \*obtener_recursivo(nodo_t \*nodo, void \*elemento, int (\*comparador)(void \*, void \*))__

La funcion busca el elemento en alguno de los nodos, compara el elemento del mismo con el buscado, si la comparacion es igual a cero significa que lo encontro. Si la comparacion da distinto de cero lo redirecciona a sus respectivas ramas, en caso que la condicion de igualdad nunca se cumpla retorna NULL. La complejidad de la funcion es O(c) siendo c la cantidad de nodos a recorrer hasta llegar a destino, o la altura recorrida, por lo que la complejidad de la funcion es O(n).

__void *abb_obtener(abb_t \*abb, void \*elemento)__

La funcion se encarga de obtener el nodo llamando a la funcion recursiva mencionada anteriormente, si se encuentra devuelve el contenido y sino retorna NULL. Como la complejidad de obtener_recursivo() es O(n), la de esta funcion tambien es O(n).

__size_t abb_cantidad(abb_t \*abb)__

La funcion retorna la cantidad de nodos presentes en el arbol, retorna el valor almacenado en el ABB, por lo que la complejidad de la funcion es O(1).

__size_t iterar_inorden_recursivo(nodo_t \*nodo, bool (\*f)(void \*, void \*), void \*ctx, bool \*centinela)__

La funcion se encarga de iterar el arbol en orden recursivo e ir aplicandole la funcion f al elemento del nodo junto con el ctx, esta misma va a indicar si se sigue iterando o no mediante un centinela y retornando false. La complejidad de la funcion va a depender de f y de la cantidad de nodos a recorrer, si suponemos que f tiene una complejidad O(n) y el recorrido una complejidad de O(c) siendo c la altura del arbol, la complejidad de la funcion seria O(n^2). En cambio si f es O(1), la funcion tendría una complejidad de O(n).

__size_t abb_iterar_inorden(abb_t \*abb, bool (\*f)(void \*, void \*), void \*ctx)__

La funcion se encarga de iterar el arbol llamando a la funcion recursiva mencionada anteriormente y pasandole el centinela, como la complejidad de esta funcion depende de la otra, sería O(n^2) o O(n).

__size_t iterar_preorden_recursivo(nodo_t \*nodo, bool (\*f)(void \*, void \*), void \*ctx, bool \*centinela)__
__size_t abb_iterar_preorden(abb_t \*abb, bool (\*f)(void \*, void \*), void \*ctx)__
__size_t iterar_postorden_recursivo(nodo_t \*nodo, bool (\*f)(void \*, void \*), void \*ctx, bool \*centinela)__
__size_t abb_iterar_postorden(abb_t \*abb, bool (\*f)(void \*, void \*), void \*ctx)__

Las funciones son iguales a las descriptas en la seccion de arriba, la unica diferencia es la posicion de las lineas para cambiar el orden de iteracion. La complejidad de las mismas tambien es igual a las de arriba.

__typedef struct vector vector_t__

Es la estructura utilizada para describir al vector usado por las funciones de vectorizar, esta cuenta con un void **vector para almacenar los contenidos, un size_t *posicion para ir iterando sobre la misma y un size_t tamaño del vector para tener una referencia del mismo.

__bool llenar\_vector(void \*elemento, void \*\_ctx)__

La funcion se encarga de llenar el vector de la estructura vector_t, esta misma recibe por parametro el elemento del nodo y el _ctx que es la estructura ya nombrada. Si la posicion es invalida, es decir, es mayor o igual al tamaño del vector devuelve false. En caso contrario, itera sobre el vector, asignando el elemento en la posicon adecuada y aumentando esta misma. Retorna true para que las funciones de iteracion pueda seguir ejecutandose. La complejidad de esta funcion es O(1) ya que son todas instrucciones simples.

__size_t abb_vectorizar_inorden(abb_t \*abb, void \**vector, size_t tamaño)__

La funcion se encarga de definir la estructura vector_t e invocar a la funcion de iteracion pasandole por parametro un puntero al ctx, una vez termina este proceso devolvemos el valor de la posicion desreferenciandolo. La complejidad de esta funcion depende de abb_iterar_inorden() y de llenar_vector(), estas son O(n) y O(1) respectivamente, por lo que la funcion es O(n).

__size_t abb_vectorizar_preorden(abb_t \*abb, void \**vector, size_t tamaño)__
__size_t abb_vectorizar_postorden(abb_t \*abb, void \**vector, size_t tamaño)__

Las funciones son iguales a las descriptas en la seccion de arriba, la unica diferencia es la funcion de iteracion utilizada para vectorizar. La complejidad de las mismas tambien es igual a las de arriba.

## Menu

__bool crear_string_nuevo(const char *str, void *ctx)__

Explicada en el TP1

__bool leer_caracter(const char *str, void *ctx)__

Explicada en el TP1

__bool leer_int(const char *str, void *ctx)__

Explicada en el TP1

__void menu_usuario(ABB *pokedex)__

La funcion es muy parecida a la de TDA Lista con la diferencia de la estructura utilizada, se busca el elemento con abb_obtener() y asi sucesivamente.

## Pokemon

__int comparar_nombre_pokemon(void \*\_p1, void \*\_p2)__

La funcion fue explicada en TDA Lista y se mantiene igual.

__void asignar_datos_pokemones(struct pokemon *pokemon, char *nombre, char tipo, int fuerza, int destreza, int resistencia)__

La funcion fue explicada en TDA Lista y se mantiene igual.

__bool contar\_imprimir\_pokemon(void \*\_p1, void \*\_cantidad\_tipo)__

La funcion recibe por parametro el pokemon y el vector de enteros para contarlos por tipo, imprime las caracteristicas del mismo y luego recurre a un switch para almacenar los valores. Finalmente retorna true para que pueda seguir iterando las funciones de recorrido. Esta funcion tiene complejidad O(1).

__void imprimir_pokedex(abb_t *abb)__

La funcion recibe el ABB y usando la funcion para iterar, se le pasa por parametro una funcion para contar los pokemones por tipo e imprimirlo. Luego de salir del iterador, imprime la cantidad de pokemones por tipo y asi logra un formato agradable para el usuario. La complejidad de la funcion depende de contar_imprimir_pokemon() y de abb_iterar_inorden(), como estas son O(1) y O(n), la funcion tiene una complejidad de O(n).

__void liberar_pokemon(void *contenido)__

La funcion fue explicada en TDA Lista y se mantiene igual.

## CSV

Toda la implementacion y explicacion de estas funciones esta explicado en el informe del TP1.