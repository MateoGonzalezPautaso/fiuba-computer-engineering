#include "csv.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE *archivo;
	char separador;
};

/**
 * Recibe los parametros desde donde hasta donde copiar y agrega el
 * caracter al final para ser tratado como string
 */
void slice(const char *string, char *substring, size_t inicio, size_t fin)
{
	strncpy(substring, string + inicio, fin - inicio);
	substring[fin - inicio] = '\0';
}

/**
 * Libera toda la memoria utilizada por el char **split_strings
 */
void liberar_partes(char **split_strings, size_t columnas)
{
	if (!split_strings)
		return;

	for (size_t i = 0; i < columnas; i++) {
		free(split_strings[i]);
	}
	free(split_strings);
}

/**
 * Recibe el buffer donde se copio la linea, el separador del archivo y la cantidad de columnas
 * Itera sobre el buffer hasta encontrar las posiciones del separador, cuando la encuentra
 * copia los substrings correspondientes hasta llegar al final
 * Devuelve un char** a un char* de strings en caso de éxito, o NULL en caso de error.
 */
char **split(char *buffer, char separador, size_t columnas)
{
	char **split_strings = malloc(sizeof(char *) * columnas);

	if (!split_strings)
		return NULL;

	size_t longitud_buffer = strlen(buffer);
	size_t i = 0;
	size_t fin = 0;
	size_t inicio = 0;

	for (fin = 0; fin < longitud_buffer; fin++) {
		if (buffer[fin] == separador || fin == longitud_buffer - 1) {
			split_strings[i] =
				malloc((fin - inicio + 1) * sizeof(char));

			if (split_strings[i] == NULL) {
				liberar_partes(split_strings, columnas);
				return NULL;
			}

			slice(buffer, split_strings[i], inicio, fin);
			i++;
			inicio = fin + 1;
		}
	}

	return split_strings;
}

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	if (!nombre_archivo || separador == '\0')
		return NULL;

	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (!archivo)
		return NULL;

	archivo->archivo = fopen(nombre_archivo, "r");
	if (archivo->archivo == NULL) {
		free(archivo);
		return NULL;
	}

	archivo->separador = separador;
	return archivo;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (!archivo || columnas == 0)
		return 0;

	char buffer[250];
	if (!fgets(buffer, sizeof(buffer), archivo->archivo))
		return 0;

	char **split_strings = split(buffer, archivo->separador, columnas);
	if (!split_strings)
		return 0;

	size_t columnas_leidas = 0;

	for (size_t i = 0; i < columnas; i++) {
		if (funciones[i] == NULL ||
		    !funciones[i](split_strings[i], ctx[i])) {
			liberar_partes(split_strings, columnas);
			return columnas_leidas;
		}
		columnas_leidas++;
	}

	liberar_partes(split_strings, columnas);
	return columnas_leidas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo && archivo->archivo)
		fclose(archivo->archivo);

	free(archivo);
}