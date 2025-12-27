#include "vector.h"

vector_t *vector_crear(size_t tam) {
    if (tam == 0) {
        return NULL;
    }

    vector_t *vector = malloc(sizeof(vector_t)); // asigno memoria al vector

    if (vector == NULL) {
        return NULL;
    }

    vector->tam = tam;
    vector->valores = malloc(tam * sizeof(int)); // asigno memoria a valores

    if (vector->valores == NULL) { // si falla valores, libero la memoria de vector
        free(vector);
        return NULL;
    }

    return vector;
}


void vector_destruir(vector_t* vector) {
    free(vector->valores);
    free(vector);
}


bool vector_guardar(vector_t *vector, size_t pos, int valor) {
    if (vector->tam <= pos) { // size_t es unsigned, como mínimo es 0
        return false;
    }

    vector->valores[pos] = valor;
    return true;
}


bool vector_obtener(vector_t *vector, size_t pos, int *valor) {
    if (vector->tam <= pos) { // size_t es unsigned, como mínimo es 0
        return false;
    }

    *valor = vector->valores[pos]; // valor es una direccion de memoria en pruebas, donde guardo el dato
    return true;
}


size_t vector_largo(vector_t *vector) {
    return vector->tam;
}


void vector_por_escalar(vector_t *vector, int k) {
    for (size_t i = 0; i < vector->tam; i++) { // i es size_t para poder comparar con vector->tam
        vector->valores[i] *= k;
    }
}


vector_t* vector_sumar(vector_t *vector1, vector_t *vector2) {
    if (vector1->tam != vector2->tam) {
        return NULL;
    }
    
    vector_t* vector = vector_crear(vector1->tam);

    if (vector == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < vector->tam; i++) {
        vector->valores[i] = vector1->valores[i] + vector2->valores[i];
    }

    return vector;
}


bool vector_redimensionar(vector_t *vector, size_t nuevo_tam) {
    if (nuevo_tam == 0) {
        return false;
    }

    int *nuevo_valores = malloc(nuevo_tam * sizeof(int)); // asigno memoria al nuevo puntero

    if (nuevo_valores == NULL) {
        return false;
    }

    for (size_t i = 0; i < nuevo_tam; i++) {
        if (i == vector->tam || i == nuevo_tam) { // corto la ejecucion cuando i sea igual al de menor cantidad
            break;
        }

        nuevo_valores[i] = vector->valores[i]; // copio valores
    }

    free(vector->valores); // libero el puntero de valores viejo
    vector->valores = nuevo_valores; // asigno al puntero la nueva direccion de memoria
    vector->tam = nuevo_tam;

    return true;
}