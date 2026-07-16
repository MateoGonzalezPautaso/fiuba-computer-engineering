# Threads

## Créditos

La implementación de las clases `Socket`, `Resolver`, `LibError` y `ResolverError`
está basada en el código provisto por la cátedra:

https://github.com/eldipa/sockets-en-cpp

Licencia: GPL v2

La implementación de las clases `Thread` y `Queue` está basada en el código provisto por la cátedra:

https://github.com/eldipa/hands-on-threads

Licencia: GPL v2

## Compilación
Para compilar el proyecto hay que ejecutar lo siguiente en la terminal:
```bash
make -f MakefileThreads
```

Para limpiar y eliminar los archivos compilados y ejecutables viejos:
```bash
make -f MakefileThreads clean
```

## Tests
Para ejecutar las pruebas contra tu código y generar tu directorio de salidas (`casos/`):
```bash
./run_tests.sh ./ casos/ multi-client no-valgrind 60 10 yes
```
(Si se quiere ejecutar con valgrind, simplemente cambiar "no-valgrind" por "valgrind" y remover el "yes" del final)

Para comparar tus salidas con los resultados esperados por la cátedra (`salidas/`):
```bash
./compare_outputs.sh casos/ salidas/
```

## Documentación

Las `Queue` utilizadas en el diseño de este trabajo (provista por la cátedra) son técnicamente `Bounded Queue`, pero la forma en las que las inicializamos genera que se comporten como `Unbounded Queue`. Reciben un atributo `max_size` pero al utilizar el constructor por defecto, sin este parámetro, se inicializa con `UINT_MAX - 1`.

La `Queue` del gameloop **Queue\<PlayerCommand\>** no debe quedarse esperando comandos, sino la simulación no seguiría y no habría mas "ticks", es por esto que usamos `try_pop()` que retorna inmediatamente si no hay nada.

La `Queue` de eventos por cada cliente **Queue\<GameEvent\>** hace `pop()`, ya que la unica tarea de `Sender` es esperar eventos y enviarlos. La separación en una queue por cliente evita que un cliente lento bloquee a los demás.


![threads](docs/threads.svg)

Receiver y Sender comparten Socket ya que el primero solo lee y el segundo solo escribe, ClientHandler es el dueño del mismo. Acceptor es dueño de su propio Socket listener.

En cuanto a `ClientListMonitor` y el uso de `player_id`, fue una decisión para garantizar que clientes con el mismo nombre no se pisen entre si. Al ser una clave única, además de usar un mutex para proteger el acceso concurrente al map, nos aseguramos de poder agregar nuevos clientes mientras el `GameLoop` realiza el broadcast.

También la variable `_already_stopped` de Sender es atómica ya que el metodo stop() puede ser llamado simultáneamente por el `Receiver` o por `ClientHandler`.

Opté por el uso de new para `ClientHandler` ya que es necesario guardarlo en un mapa (mediante punteros) y la clase `Thread` deshabilita los constructores por movimiento, entonces hay que hacer un manejo manual de la memoria. El destructor de esta clase garantiza stop() y join(), junto con el monitor que garantiza delete.
