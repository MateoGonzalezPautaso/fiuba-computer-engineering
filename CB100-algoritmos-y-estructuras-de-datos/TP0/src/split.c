#include "split.h"
#include <stdlib.h>
#include <string.h>

void slice(const char *string, char *substring, size_t inicio, size_t fin)
{
	// Recibe los parametros de inicio a fin para copiar y agrega '\0'
	strncpy(substring, string + inicio, fin - inicio);
	substring[fin - inicio] = '\0';
}

size_t contar_partes(const char *string, char separador)
{
	// Siempre va a haber una parte mas que cantidad de separadores
	size_t i = 0;
	size_t cantidad_partes =
		1; // si el string es no nulo, minimo tiene 1 parte
	while (string[i] != '\0') {
		if (string[i] == separador) {
			cantidad_partes++;
		}
		i++;
	}
	return cantidad_partes;
}

struct Partes *dividir_string(const char *string, char separador)
{
	struct Partes *partes = malloc(sizeof(struct Partes));
	if (partes == NULL) {
		return NULL;
	}

	if (string == NULL) {
		partes->cantidad = 0;
		partes->string = NULL;
		return partes;
	}

	partes->cantidad = contar_partes(string, separador);
	partes->string = malloc(sizeof(char *) * partes->cantidad);

	if (partes->string == NULL) {
		free(partes);
		return NULL;
	}

	size_t longitud_string = strlen(string);
	size_t n_parte = 0;
	size_t fin = 0; // posicion del separador
	size_t inicio = 0; // desde donde copiar

	for (fin = 0; fin <= longitud_string; fin++) {
		if (string[fin] == separador || fin == longitud_string) {
			partes->string[n_parte] =
				malloc((fin - inicio + 1) *
				       sizeof(char)); // +1 para '\0'

			if (partes->string[n_parte] == NULL) {
				liberar_partes(partes);
				return NULL;
			}

			slice(string, partes->string[n_parte], inicio, fin);
			n_parte++;
			inicio = fin + 1; // posicion proxima al separador
		}
	}
	return partes;
}

void liberar_partes(struct Partes *partes)
{
	if (partes == NULL) {
		return;
	}

	for (size_t i = 0; i < partes->cantidad; i++) {
		free(partes->string[i]);
	}
	free(partes->string);
	free(partes);
}