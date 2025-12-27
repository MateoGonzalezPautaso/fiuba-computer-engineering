# shell

### Búsqueda en $PATH

##### ¿Cuáles son las diferencias entre la syscall execve(2) y la familia de wrappers proporcionados por la librería estándar de C (libc) exec(3)?

Las diferencias entre la syscall y la familia de wrappers es la capa de abstracción que manejan. Los wrappers reciben ciertos argumentos e internamente llaman a la syscall. Esto con el objetivo de facilitar el uso de execve, por ejemplo:
+ execve recibe por parámetro la ruta absoluta al binario del programa que va a ejecutarse. Por otro lado los wrappers que cuentan con una `p` en su nombre buscan los binarios en los directorios $PATH si no se especifica una ruta absoluta
+ Algunos wrappers (los que contienen la `e` en su nombre) permiten el uso de variables de entorno personalizadas, mientras otras heredan las del proceso padre. Esto es para simplificar las llamadas a las funciones en caso de no querer modificar el entorno.


##### ¿Puede la llamada a exec(3) fallar? ¿Cómo se comporta la implementación de la shell en ese caso?

Sí, la llamada exec(3) puede fallar. En caso de que la llamada falle, no se cambia la imagen del proceso (memoria virtual, entorno, argumentos), por lo que continúa ejecutándose la función `exec_cmd`, terminando por enviar un mensaje por la salida estándar de error para luego finalizar el proceso con `exit(-1)`.


---

### Flujo estándar

##### Responder: Investigar el significado de 2>&1, explicar cómo funciona su forma general. Mostrar qué sucede con la salida de cat out.txt en el ejemplo. Luego repetirlo, invirtiendo el orden de las redirecciones (es decir, 2>&1 >out.txt). ¿Cambió algo? Compararlo con el comportamiento en bash(1).


Para entender el significado de la redirección `2>&1` hay que conocer como funcionan los *file descriptors* en los procesos de *Unix*.
Cuando inicia un proceso se abren 3 *file descriptors* por defecto:
+ 0: Para la entrada estándar (stdin)
+ 1: Para la salida estándar (stdout)
+ 2: Para la salida de error estándar (stderr)

Cuando se usan las redirecciones del flujo estándar, se indica un cambio en uno de esos *file descriptors*, cambiando sus valores por el del archivo destino de la redirección.

La redirección `2>&1` indica que el *file descriptor* 2  (stderr) va a ser redirigido al mismo archivo al que esta apuntando el *file descriptor* 1 (generalmente stdout, a menos que también se este redirigiendo), provocando que ambas salidas desemboquen en el mismo archivo.

Cómo funciona:
 - 2> indica la redirección del stderr
 - & significa que lo que sigue es un *file descriptor*, no un nombre de archivo
 - 1 indica el *file descriptor* 1 

Con la salida de 
```shell
    $ ls -C /home /noexiste >out.txt 2>&1
    $ cat out.txt
```
sucede lo siguiente: 
```shell
    ls: cannot access '/noexiste': No such file or directory
    /home:
    <nombre_del_usuario>
```
En este caso, al ejecutarse el comando `ls` se está redirigiendo la salida estándar *stdout* hacia `out.txt`, y luego se redirige la salida estándar de error *stderr* al mismo lugar que *stdout*, es decir, `out.txt`. Lo que termina en que toda la salida del comando, tanto la estándar como la de error terminan volcadas en `out.txt`.

Y con las redirecciones invertidas:
```shell
    $ ls -C /home /noexiste 2>&1 >out.txt
    $ cat out.txt
```
+ **Caso bash**: En `out.txt` va a quedar la salida de `ls -C /home`, que es la salida del comando. Sin embargo, el mensaje de error va a salir por stdout, es decir, por consola. Esto ocurre debido a que la redirección de la salida estándar de error se hace antes que la redirección de stdout, quedando stdout como la salida estándar de error y out.txt como la salida estándar.
+ **Implementación de esta shell**: En esta implementación no se diferencian las posiciones de las redirecciones al momento de parsear. Por eso siempre se va a redirigir primero el `stdout` y despues el `stderr` al mismo file descriptor al que fue redirigido el primero.

---

### Tuberías múltiples

##### Responder: Investigar qué ocurre con el exit code reportado por la shell si se ejecuta un pipe ¿Cambia en algo?

En esta implementacion de la shell no se muestran los exit code de los comandos luego de ejecutar un pipe. Esto no depende de si la tuberia es simple o multiple.
Sin embargo si se muestran los exit code de los comandos ejecutados sin pipes.

##### Qué ocurre si, en un pipe, alguno de los comandos falla? Mostrar evidencia (e.g. salidas de terminal) de este comportamiento usando bash. Comparar con su implementación.

En esta implementacion de la terminal si alguno de los comandos del pipe falla siempre se actualiza el status a 0.
En cambio, en bash el status se actualiza a la salida del ultimo comando ejecutado en los pipes.

**bash**
```bash
    $ ls | wc
        1       1       6
    $ echo $?
        0
    $ ls | false
    $ echo $?
        1 
```


**Esta implementacion del shell**
```bash
    $ ls | wc
        10      11      81
    (/home/agustin) 
    $ echo $?
        0
        Program: [echo $?] exited, status: 0 
        (/home/agustin) 
    $ ls | false
        (/home/agustin) 
    $ echo $?
        0
        Program: [echo $?] exited, status: 0 
```

---

### Variables de entorno temporarias

##### Responder: ¿Por qué es necesario hacerlo luego de la llamada a fork(2)?

Cuando la shell hace la llamada a `fork` para crear el proceso hijo que ejecutará el comando, se crea un nuevo proceso que es una copia del proceso padre, lo que significa que tambien es una copia de su entorno.
La diferencia es que al hacer la extensión de las variables de entorno en hijo, estas no van a cambiar el entorno del padre.
Si primero se setean las variables de entorno, luego se hace el fork y despues la ejecución, se estarían ubicando las variables temporales en el proceso a ejecutar, pero tambien estaría modificando el entorno de la `shell`, cosa que no queremos.

##### Responder: En algunos de los wrappers de la familia de funciones de exec(3) (las que finalizan con la letra e), se les puede pasar un tercer argumento (o una lista de argumentos dependiendo del caso), con nuevas variables de entorno para la ejecución de ese proceso. Supongamos, entonces, que en vez de utilizar setenv(3) por cada una de las variables, se guardan en un arreglo y se lo coloca en el tercer argumento de una de las funciones de exec(3). 
+ ##### ¿El comportamiento resultante es el mismo que en el primer caso? Explicar qué sucede y por qué.

    No, los resultados no son los mismos. Cuando se llama a un wrapper de `exec(3)` que permite pasarle por parametro el arreglo de variables de entorno, este proceso va a ejecutar el programa pasado por parámetro con un entorno compuesto exclusivamente por las variables de entorno que están en el arreglo.
    En el otro caso, cuando se hace un fork y después se agregan las variables de entorno usando `setenv(3)`, cuando se hace el `exec` el entorno del proceso va a estar compuesto por las variables que se setearon con `setenv` pero tambien por todas las variables de entorno que estaban en el proceso padre, ya que fueron heredadas despues de usar el fork. 

+ ##### Describir brevemente (sin implementar) una posible implementación para que el comportamiento sea el mismo.

    Para que el comportamiento sea el mismo, primero se debe crear el arreglo de variables de entorno que se va a pasar por parámetro al wrapper de `exec`.
    Luego, se recorren las variables de entorno que están presentes en el environ, es decir, donde están guardadas las variables de entorno ya seteadas. 
    Lo siguiente es agregar las nuevas variables de entorno que se quieran usar.
    Finalmente se llama a fork y dentro del proceso hijo se llama al wrapper de `exec` pasandole por parámetro el arreglo con las variables. Así al ejecutar el programa pasado por parámetro a exec, este va a tener el entorno compuesto por las variables que estaban en el padre y también las agregadas. 
    
---

### Pseudo-variables

##### Responder: Investigar al menos otras tres variables mágicas estándar, y describir su propósito. Incluir un ejemplo de su uso en bash (u otra terminal similar).

Ejemplos de otras variables mágicas:
1. **$RANDOM**: Genera un número aleatorio entre 0 y 32767

```bash
$ echo $RANDOM
    8522
```
2. **$$**: Devuelve el número del PID actual
```bash
$ echo $$
    11291       # El proceso de la shell
```
3. **$!**: Devuelve el PID del último proceso en segundo plano
```bash
$ echo $!

$ sleep 5 &
    [1] 20707
$ echo $!
    20707
$ true   
[1]+  Done                    sleep 5
$ 
```
### Comandos built-in

##### Responder: ¿Entre cd y pwd, alguno de los dos se podría implementar sin necesidad de ser built-in? ¿Por qué? 
##### ¿Si la respuesta es sí, cuál es el motivo, entonces, de hacerlo como built-in? (para esta última pregunta pensar en los built-in como true y false)

Cd no se podría implementar sin necesidad de ser built-in porque un programa externo no podría cambiar el directorio del proceso shell desde el que fue ejecutado sino que sólo podría cambiar su propio directorio y, luego de esto, terminar.
Por otro lado, pwd no tiene que ser obligatoriamente un built-in ya que sólo lee el directorio actual utilizando la system call getcwd()(generalmente). Debido a que no necesita modificar nada del entorno de la shell, podría implementarse perfectamente sin ser un comando built-in.

El motivo de hacerlo como built-in es por un tema de performance por el motivo de que llamar a un comando externo implica hacer un fork y un exec. Lo cual es mucho más costoso que simplemente llamar a la syscall getcwd() desde el mismo proceso del shell.

### Procesos en segundo plano

##### Responder: ¿Por qué es necesario el uso de señales?

El uso de señales es necesario para administrar los procesos ejecutados en segundo plano de forma eficiente, especialmente en una shell, donde estamos constantemente creando procesos hijos mediante la ejecución de comandos, 

Cuando un comando se ejecuta en primer plano, el proceso padre tiene que esperar activamente a que el hijo termine, con syscalls como wait() o waitpid(). Durante este proceso el usuario no puede hacer más que esperar.

En cambio, cuando un comando se ejecuta en segundo plano, el proceso padre no se queda esperando a que el mismo termine, vuelve a ejecutar distintas tareas. La shell necesita una forma de saber cuando el proceso hijo termina para liberar sus recursos, ya que si no se hace nada el mismo queda en estado zombie.

Mediante la señal SIGCHLD, enviada por el sistema operativo cuando un hijo termina correctamente o por un error, y la función sigaction() somos capaces de configurar un handler de señales. Este manejador de señales se ejecuta automaticamente cada vez que recibimos la señal, en nuestro caso llama a waitpid() con la opcion WNOHANG para verificar la finalizacion del hijo, sin bloquear la shell.

Tanto los procesos en primer plano como en segundo plano generan SIGCHLD al finalizar. Por eso, es necesario distinguir entre ambos para que el handler no recoja procesos en primer plano. Para lograr esto, agrupamos todos los procesos en segundo plano en un mismo grupo de procesos utilizando setpgid(), y dentro del handler usamos waitpid() con un valor numérico específico (por ejemplo, 0) que solo nos permite acceder a los procesos de ese grupo.

##### Explicar detalladamente el mecanismo completo utilizado.

Primero antes que nada hay que preparar el handler del SIGCHLD con una estructura sigaction limpia, asignándole memoria seteada en 0 para evitar que haya basura.
```c
struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

struct sigaction estructura;
memset(&estructura, 0, sizeof(struct sigaction));
```

Una vez asignada la memoria, tenemos que asignar las variables de la estructura.
 - sa_handler: tenemos que asignar la funcion que se invocara cada vez que llegue la señal SIGCHLD.
 - sa_flags: asignamos la flag SA_RESTART para asegurarnos que las syscalls interrumpidas por la señal se reinicien automaticamente
```c
estructura.sa_handler = sigchild_handler;
estructura.sa_flags = SA_RESTART;
```

Luego utilizamos la funcion sigaction() para cambiar la accion realizada por un proceso al recibir la señal  SIGCHLD y verificamos que no falle. En el parametro **signum** especificamos la señal, en **act** la nueva acción para la misma y si **oldact** no fuese NULL se guardaría la acción antigua.
```c
int sigaction(  int signum,
                const struct sigaction *_Nullable restrict act,
                struct sigaction *_Nullable restrict oldact);

if( sigaction(SIGCHLD,&estructura,NULL) != 0 ){
		perror("Error al ejecutar sigaction");
		exit(-1);
	}
```

Después en runcmd.c cuando hay un proceso foreground, se cambia su pgid a su propio pid asi no comparten pgid con los background
```c
if(parsed->type != BACK) {
	setpgid(p, 0);
}
```

Cada vez que un hijo termina, se dispara la señal y se ejecuta nuestro handler. La implementacion fue explicada en el apartado anterior, lo que hacemos ademas de esperar a los procesos con el mismo PGID sin bloquear la shell es notificar por la terminal el PID y STATUS del proceso terminado. En un handler solo están permitidas las funciones **async-signal-safe**, por lo que tenemos que usar funciones seguras como write() y write_numer() en lugar de printf.


