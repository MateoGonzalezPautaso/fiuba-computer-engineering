#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct archivo_csv {
	FILE *archivo;
	char separador;
};

struct pokedex {
	struct pokemon *pokemones;
	size_t cantidad_pokemones;
	size_t size;
};

/**
 * Recibe la pokedex y un arreglo de enteros, cuenta los pokemones por tipo y
 * los ordena con cierto formato
 * No devuelve nada, solo copia las cantidades por tipo
 */
void contar_pokemon_segun_tipo(struct pokedex *pokedex, int cantidad_tipo[])
{
	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		switch (pokedex->pokemones[i].tipo) {
		case TIPO_AGUA:
			cantidad_tipo[0]++;
			break;
		case TIPO_FUEGO:
			cantidad_tipo[1]++;
			break;
		case TIPO_PLANTA:
			cantidad_tipo[2]++;
			break;
		case TIPO_ROCA:
			cantidad_tipo[3]++;
			break;
		case TIPO_ELECTRICO:
			cantidad_tipo[4]++;
			break;
		case TIPO_NORMAL:
			cantidad_tipo[5]++;
			break;
		case TIPO_LUCHA:
			cantidad_tipo[6]++;
			break;
		}
	}
}

/**
 * Recibe la pokedex e imprime el formato pedido por el enunciado
 * No devuelve nada, solo imprime
 */
void imprimir_pokedex(struct pokedex *pokedex)
{
	int cantidad_tipo[7] = { 0, 0, 0, 0, 0, 0, 0 };
	contar_pokemon_segun_tipo(pokedex, cantidad_tipo);

	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		printf("Nombre %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
		       pokedex->pokemones[i].nombre, pokedex->pokemones[i].tipo,
		       pokedex->pokemones[i].fuerza,
		       pokedex->pokemones[i].destreza,
		       pokedex->pokemones[i].resistencia);
	}

	printf("Cantidad de pokemones de cada tipo:\n");
	printf("Agua: %d\n", cantidad_tipo[0]);
	printf("Fuego: %d\n", cantidad_tipo[1]);
	printf("Planta: %d\n", cantidad_tipo[2]);
	printf("Roca: %d\n", cantidad_tipo[3]);
	printf("Electrico: %d\n", cantidad_tipo[4]);
	printf("Normal: %d\n", cantidad_tipo[5]);
	printf("Lucha: %d\n", cantidad_tipo[6]);
}

/**
 * Recibe un string y el ctx, asigna memoria para el nuevo string en un char*,
 * lo copia al ctx y luego lo castea a char**
 * Devuelve true si pudo crearlo o false en caso de fallo
 */
bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL) {
		return false;
	}

	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

/**
 * Recibe un caracter y el ctx, lo copia al ctx y luego lo castea a char*
 * Devuelve true si pudo copiarlo
 */
bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *str;
	return true;
}

/**
 * Recibe un string y el ctx. La funcion sscanf recibe un *str,
 * el formato y lo copia al ctx pero formateado a int*
 * Devuelve true si pudo leerlo o false en caso de fallo
 */
bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("No ingresaste una ruta o nombre de archivo\n");
		return 1;
	}

	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], ';');
	struct pokedex *pokedex = pokedex_crear();
	if (!archivo || !pokedex)
		return 1;

	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };
	int fuerza, destreza, resistencia;
	char tipo;
	char *nombre = NULL;

	void *ctx[5] = { &nombre, &tipo, &fuerza, &destreza, &resistencia };

	while (leer_linea_csv(archivo, 5, funciones, ctx) == 5) {
		struct pokemon pokemon = { nombre, tipo, fuerza, destreza,
					   resistencia };

		if (!pokedex_agregar_pokemon(pokedex, pokemon)) {
			free(nombre);
			break;
		}

		free(nombre);
	}

	imprimir_pokedex(pokedex);

	cerrar_archivo_csv(archivo);
	pokedex_destruir(pokedex);
	return 0;
}