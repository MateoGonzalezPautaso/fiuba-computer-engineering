# Sockets

## Créditos

La implementación de las clases `Socket`, `Resolver`, `LibError` y `ResolverError`
está basada en el código provisto por la cátedra:
https://github.com/eldipa/sockets-en-cpp

Licencia: GPL v2

## Compilación
Para compilar el proyecto hay que ejecutar lo siguiente en la terminal:
```bash
make -f MakefileSockets
```

Para limpiar y eliminar los archivos compilados y ejecutables viejos:
```bash
make -f MakefileSockets clean
```

## Cómo funciona 
Primero debe iniciarse el servidor, indicando el puerto, el archivo con los ítems de la tienda y el protocolo a usar:
```bash
./server <servname> <ruta-archivo> <binario|texto>
```

Luego, en otra terminal, se inicia el cliente:
```bash
./client <hostname> <servname> <username>
```

#### Ejemplo de uso

En la terminal del servidor 
```bash
./server 5000 tienda.csv texto
```

En la terminal del cliente 
```bash
./client localhost 5000 Mateo
```

## Tests
Para ejecutar las pruebas contra tu código y generar tu directorio de salidas (`casos/`):
```bash
./run_tests.sh . casos/ single-client no-valgrind 60 10 no
```
(Si se quiere ejecutar con valgrind, simplemente cambiar "no-valgrind" por "valgrind" y remover el "no" del final)

Para comparar tus salidas con los resultados esperados por la cátedra (`salidas/`):
```bash
./compare_outputs.sh casos/ salidas/
```