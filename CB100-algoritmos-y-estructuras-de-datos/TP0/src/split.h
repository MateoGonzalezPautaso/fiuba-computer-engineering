#ifndef SPLIT_H_
#define SPLIT_H_

#include <stdlib.h>

struct Partes {
  size_t cantidad;
  char **string;
};

/**
 * Recibe un string y un separador y devuelve un struct con la informacion de
 * los strings separados.
 */
struct Partes *dividir_string(const char *string, char separador);

/**
 * Recibe un string y un separador y devuelve la cantidad de partes en las que
 * se separara
 */
size_t contar_partes(const char *string, char separador);

/**
 * Recibe un string y un substring, segun los parametros del slice es lo que se
 * copia al substring
 */
void slice(const char *string, char *substring, size_t inicio, size_t fin);

/**
 * Libera TODA la memoria utilizada por el struct Partes.
 */
void liberar_partes(struct Partes *partes);

#endif // SPLIT_H_
