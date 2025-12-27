#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************
 *                DEFINICIÓN DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct vector {
    size_t tam;
    int *valores;
} vector_t;


/*******************************************************************
 *                    FUNCIONES DEL VECTOR
 ******************************************************************/

// Crea un vector de tamaño `tam`.
// POST: devuelve un puntero a un `vector_t` de tamaño `tam`. Si alguna
// solicitud de memoria falló o si `tam == 0`, devuelve `NULL` y libera toda la
// memoria que sí se llegó a solicitar.
vector_t *vector_crear(size_t tam);

// Destruye el vector y libera su memoria utilizada.
// PRE: el vector fue creado.
// POST: se eliminaron todos los elementos del vector.
void vector_destruir(vector_t *vector);

// Almacena en valor el dato guardado en la posición pos del vector.
// PRE: el vector fue creado.
// POST: se almacenó en el puntero `valor` el dato en la posición `pos`.
// Devuelve `false` si la posición es inválida (fuera del rango del vector, que
// va de 0 a `tamaño-1`).
bool vector_obtener(vector_t *vector, size_t pos, int *valor);

// Almacena el valor en la posición `pos`.
// PRE: el vector fue creado.
// POST: se almacenó el valor en la posición `pos`. Devuelve `false` si la
// posición es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y
// `true` si se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, size_t pos, int valor);

// Devuelve el tamaño del vector.
// PRE: el vector fue creado.
size_t vector_largo(vector_t *vector);

// Multiplica el vector por un escalar.
// PRE: el vector fue creado.
// POST: modifica el contenido del vector multiplicando cada elemento por `k`.
void vector_por_escalar(vector_t *vector, int k);

// Devuelve un nuevo vector con suma de los vectores `vector1` y `vector2`.
// PRE: los vectores fueron creados.
// POST: devuelve un puntero a un nuevo vector cuyo contenido corresponde a la
// suma de los vectores. Si los vectores no tienen el mismo tamaño o la
// solicitud de memoria para crear un nuevo vector falló, devuelve NULL.
vector_t* vector_sumar(vector_t *vector1, vector_t *vector2);

// Cambia el tamaño del vector a la cantidad solicitada.
// PRE: el vector fue creado.
// POST: si la operación fue exitosa, devuelve `true` y el vector tendrá la
// nueva capacidad especificada. Si el nuevo tamaño es menor que la capacidad
// del vector actual, se perderán los elementos de los últimos índices para
// cumplir con la capacidad nueva. Si la solicitud de memoria falló o `nuevo_tam
// == 0`, devuelve `false`.
bool vector_redimensionar(vector_t *vector, size_t nuevo_tam);


#endif  // _VECTOR_H
