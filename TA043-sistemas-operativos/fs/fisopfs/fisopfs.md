# TP - filesystem grupo 33

## Las estructuras en memoria que almacenarán los archivos, directorios y sus metadatos

La imagen a continuación muestra la estructura del filesystem.

![image](images/filesystem.svg)

`filesystem_t`

```c
typedef struct filesystem {
    inode_t inodes[MAX_INODES];
    bool inode_bitmap[MAX_INODES];
    int32_t used_inodes;
} filesystem_t;
```

El filesystem cuenta con un array de `inode_t`, que representan los archivos y directorios del filesystem. Erl primer inodo presente en el array representa al directorio root `\` , el resto se van a ir completando con los datos de los archivos y directorios que son posteriormente creados.
Tambien se cuenta con un bitmap de valores booleanos, donde cada posicion corresponde al mismo inodo en el array de `inode_t`, donde un valor `true` representa que el inodo es válido y un valor `false` que es invalido.
Se cuenta con un contador de todos los inodos que esan en us (cantidad de valores `true` en el bitmap).

---

La imagen a continuación muestra la estructura de un inodo.

![image](images/inodo.svg)

`inode_t`

```c
typedef enum file_type {
    REGULAR_FILE,
    DIRECTORY
} file_type_t;

typedef struct inode {
    file_type_t file_type;
    char path[MAX_PATH];
    char data[BLOCK_SIZE];
    
    ino_t ino;
    nlink_t nlink;
    mode_t mode;
    
    uid_t uid;
    gid_t gid;
    off_t size;
    
    time_t atime;
    time_t mtime;
    time_t ctime;
} inode_t;
```

La estructura en memoria del `inode_t` va a depender de si se estan guardando los datos de un directorio o de un archivo. 
+ Caso directorio: dentro del array de bytes `data` se van a almacenar todos los path relativos a todos lo inodos dentro de si mismo y ordenadamente, por ejemplo:
	La estructura 
```
/
├── dir1/
├── img/
└── a.txt/

```

va a mostrar la data del inodo `/` como:

```
d | i | r | 1 | \0 | i | m | g | \0 | a | . | t | x | t | 0 | ...
```
+ Caso regular file: dentro del array de bytes data se van a almacenar los datos en bruto, incluso en forma binaria que fueron escritos al archivo.

Ademas de esta diferenciacion importante entre los dos casos, tambien cada inodo guarda la metadata relevante a nuestro caso, siendo los mas relevantes:
+ el path absoluto
+ el modo
+ el numero de inodo
+ el offset
+ los ultimos tiempos de acceso, modificacion y cambios
+ entre otros.


#### Decisiones de diseño 
Al almacenar un nuevo inodo dentro del filesystem, siempre se va a guardar en la primera posicion que se corresponda a un valor `false` dentro del bitmap, comenzando a recorrer el array desde el root. 

El valor de MAX_PATH se fija en 100 caracteres para cubrir la mayoría de rutas típicas sin desperdiciar demasiada memoria ni complicar la lógica de gestión.

El valor de BLOCK_SIZE se fija en 4096 Bytes o 4KB y coincide con el tamaño de página de memoria de la mayoría de sistemas operativos. Esto optimiza lectura/escritura en bloque y simplifica la gestión de almacenamiento al trabajar en múltiplos de páginas. Además bloques de tamaño uniforme facilitan la asignación, liberación y recuento de espacio libre. También simplifican la implementación de operaciones como read(), write(), truncate(), etc.

## Cómo el sistema de archivos encuentra un archivo específico dado un path
Cada estructura `inode_t` almacena su path dentro de sus datos. El filesystem busca el inodo dado su path usando la funcion auxiliar `inode_index_from_path` definida dentro de `utils.h`. 
Esta funcion recorre todos los `inode_t` presentes en el `fylesystem_t` que están marcados como `true` en el bitmap del filesystem. Si en alguno de los `inode_t` que recorre se da una igualdad entre el path buscado y el path almacenado en el inodo, entonces se encontró el mismo a traves de su path. Si se recorren todo los `inode_t` que guardan un true en el bitmap del filesystem y nunca se da la coincidencia, entonces el path es inexistente dentro del filesystem.

## El formato de serialización del sistema de archivos en disco

El formato de serialización del sistema de archivos en disco es una copia directa en bruto de la estructura filesystem en memoria.
- Se guarda tal cual está en RAM usando fwrite(&filesystem, sizeof(filesystem), 1, fs).
- Luego se recupera con fread(&filesystem, sizeof(filesystem), 1, fs).
No hay ningún tipo de transformación, compresión o codificación: lo que se guarda es el layout de memoria completo de la estructura filesystem  en binario en el archivo de persistencia. Por esta razón, es que se utilizan estructuras de datos estáticas.

## Cualquier otra decisión/información que crean relevante
Separamos las funciones auxiliares en archivos aparte `utils.h` y `utils.c` para mejorar la legibilidad del codigo. Por esta modificacion tambien se realizarion cambios en el makefile. 
Para la implementacion de pruebas de caja negra elegimos usar python debido a su legibilidad y la capacidad de implementar pruebas concisas. Ademas de que el uso de python permite reducir sustancialmente el manejo de errores al manejar archivos en comparacion a otros lenguajes como `C`. 

## Como correr los tests
Para correr los tests correctamente primero hay que asegurarse de montar el FUSE (para que el contenedor soporte python para correr los tests se modificó el Dockerfile)

```
./dock build
./dock run
./fisopfs dir
python3 tests_fisopfs.py
``` 