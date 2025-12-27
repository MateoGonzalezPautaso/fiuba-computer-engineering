#ifndef __UTILIDADES_H__
#define __UTILIDADES_H__

#include "lista.h"
#include "hash.h"
#include "../extra/ansi.h"

/**
 * Devuelve el numero maximo entre dos enteros
 */
int max(int a, int b);

/**
 * Devuelve el numero minimo entre dos enteros
 */
int min(int a, int b);

/**
 * Convierte el caracter ingresado a mayuscula para
 * que el menu no tenga problemas, ya que es Case Insensitive
 */
char convertir_a_mayuscula(char c);

/**
 * Libera todo el contenido de la lista menos esta para poder
 * ser reutilizada nuevamente
 */
void lista_vaciar_sin_destruir(Lista *lista, void (*destructor)(void *));

/**
 * Elimina un elemento de la lista sin que sepamos su posicion,
 * busca la misma y luego lo libera
 */
bool lista_eliminar(Lista *lista, void *elemento);

/**
 * Funcion para crear e insertar todos los colores a la tabla
 * de hash junto a su codigo ANSI
 */
hash_t *hash_colores();

#endif /* __UTILIDADES_H__ */