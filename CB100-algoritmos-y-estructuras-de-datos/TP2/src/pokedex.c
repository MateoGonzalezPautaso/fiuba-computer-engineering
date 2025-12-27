#include "pokedex.h"
#include "csv.h"
#include "abb.h"
#include "hash.h"
#include "../extra/ansi.h"
#include "utilidades.h"
#include <string.h>
#include <stdio.h>

struct pokedex {
	abb_t *pokemones;
	hash_t *colores;
};

typedef struct posicion {
	size_t posicion_actual;
	size_t posicion_buscada;
	pokemon_t *pokemon;
} posicion_t;

/**
 * Recibe un string y el ctx, asigna memoria para el nuevo string en un char*,
 * lo copia al ctx y luego lo castea a char**
 * Devuelve true si pudo crearlo o false en caso de fallo
 */
bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;

	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

/**
 * Recibe un string y el ctx. La funcion sscanf recibe un *str,
 * el formato y lo copia al ctx pero formateado a int*
 * Devuelve true si pudo leerlo o false en caso de fallo
 */
bool leer_size_t(const char *str, void *ctx)
{
	return sscanf(str, "%zu", (size_t *)ctx) == 1;
}

/**
 * Compara los nombres de los pokemones para poder comprobar
 * si son iguales o no mediante strcmp.
 */
int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	pokemon_t *p1 = (pokemon_t *)_p1;
	pokemon_t *p2 = (pokemon_t *)_p2;

	return strcmp(p1->nombre, p2->nombre);
}

/**
 * Recibe el pokemon y los datos a asignar al pokemon que corresponda
 * 
 * No devuelve nada ya que solo copia
 */
void asignar_datos_pokemones(pokemon_t *pokemon, char *nombre, size_t puntaje,
			     char *color, char *patron_movimiento)
{
	pokemon->nombre = nombre;
	pokemon->puntaje = puntaje;
	pokemon->color = color;
	pokemon->patron_movimiento = patron_movimiento;
}

pokedex_t *pokedex_crear()
{
	pokedex_t *pokedex = malloc(sizeof(pokedex_t));
	if (!pokedex)
		return NULL;

	pokedex->pokemones = abb_crear(comparar_nombre_pokemon);
	pokedex->colores = hash_colores();
	if (!pokedex->pokemones || !pokedex->colores) {
		free(pokedex->pokemones);
		hash_destruir(pokedex->colores);
		free(pokedex);
		return NULL;
	}

	return pokedex;
}

/**
 * Se encarga de liberar el contenido del pokemon_t
 */
void liberar_pokemon(void *contenido)
{
	pokemon_t *pokemon = (pokemon_t *)contenido;
	if (pokemon->nombre)
		free(pokemon->nombre);
	if (pokemon->color)
		free(pokemon->color);
	if (pokemon->patron_movimiento)
		free(pokemon->patron_movimiento);
	free(pokemon);
}

void pokedex_destruir(pokedex_t *pokedex)
{
	if (!pokedex)
		return;
	abb_destruir_todo(pokedex->pokemones, liberar_pokemon);
	hash_destruir(pokedex->colores);
	free(pokedex);
}

bool pokedex_agregar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon)
{
	if (!pokedex || !pokemon)
		return false;

	return abb_insertar(pokedex->pokemones, pokemon);
}

bool pokedex_cargar_csv(pokedex_t *pokedex, const char *nombre_archivo,
			char separador)
{
	struct archivo_csv *archivo =
		abrir_archivo_csv(nombre_archivo, separador);
	if (!archivo || !pokedex)
		return false;

	bool (*funciones[4])(const char *, void *) = { crear_string_nuevo,
						       leer_size_t,
						       crear_string_nuevo,
						       crear_string_nuevo };
	char *nombre = NULL;
	size_t puntaje;
	char *color = NULL;
	char *patron_movimiento = NULL;

	void *ctx[4] = { &nombre, &puntaje, &color, &patron_movimiento };

	while (leer_linea_csv(archivo, 4, funciones, ctx) == 4) {
		pokemon_t *pokemon = malloc(sizeof(pokemon_t));
		if (!pokemon) {
			free(nombre);
			free(color);
			free(patron_movimiento);
			cerrar_archivo_csv(archivo);
			return false;
		}

		asignar_datos_pokemones(pokemon, nombre, puntaje, color,
					patron_movimiento);

		if (!abb_insertar(pokedex->pokemones, pokemon)) {
			liberar_pokemon(pokemon);
			cerrar_archivo_csv(archivo);
			return false;
		}

		nombre = NULL;
		color = NULL;
		patron_movimiento = NULL;
	}

	cerrar_archivo_csv(archivo);
	return true;
}

pokemon_t *pokedex_buscar_pokemon(pokedex_t *pokedex, char *nombre)
{
	if (!pokedex || !nombre)
		return NULL;

	pokemon_t aux;
	aux.nombre = nombre;

	return (pokemon_t *)abb_obtener(pokedex->pokemones, &aux);
}

/**
 * Es la funcion para iterar sobre el ABB y obtener el pokemon en la
 * posicion requerida
 */
bool iterar_hasta_posicion(void *pokemon, void *ctx)
{
	posicion_t *datos = (posicion_t *)ctx;

	if (datos->posicion_actual == datos->posicion_buscada) {
		datos->pokemon = (pokemon_t *)pokemon;
		return false;
	}

	datos->posicion_actual++;
	return true;
}

pokemon_t *pokedex_obtener_aleatorio(pokedex_t *pokedex)
{
	if (!pokedex || !pokedex->pokemones ||
	    abb_cantidad(pokedex->pokemones) == 0)
		return NULL;

	size_t cantidad_pokemones = abb_cantidad(pokedex->pokemones);
	size_t posicion_aleatoria = (size_t)(rand() % (int)cantidad_pokemones);

	posicion_t datos = { .posicion_actual = 0,
			     .posicion_buscada = posicion_aleatoria,
			     .pokemon = NULL };

	abb_iterar_inorden(pokedex->pokemones, iterar_hasta_posicion, &datos);

	return datos.pokemon;
}

/**
 * Recibe el pokemon y la tabla de colores, con estos valores 
 * imprime el pokemon con formato adecuado
 */
bool pokemon_imprimir(void *pokemon, void *colores)
{
	if (!pokemon || !colores)
		return false;
	pokemon_t *actual = (pokemon_t *)pokemon;
	hash_t *tabla_colores = (hash_t *)colores;

	char *color_ANSI = hash_buscar(tabla_colores, actual->color);

	if (!color_ANSI) {
		char *string = "    - %s (%s) ->" ANSI_COLOR_BOLD
			       " %zu puntos\n" ANSI_COLOR_RESET;
		printf(string, actual->nombre, actual->patron_movimiento,
		       actual->puntaje);
	} else {
		char *string = "    - %s%s" ANSI_COLOR_RESET
			       " (%s) ->" ANSI_COLOR_BOLD
			       " %zu puntos\n" ANSI_COLOR_RESET;
		printf(string, color_ANSI, actual->nombre,
		       actual->patron_movimiento, actual->puntaje);
	}

	return true;
}

void pokedex_imprimir(pokedex_t *pokedex)
{
	if (!pokedex)
		return;

	abb_iterar_inorden(pokedex->pokemones, pokemon_imprimir,
			   pokedex->colores);
}