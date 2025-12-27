#include "pokedex.h"
#include <string.h>

struct pokedex {
	struct pokemon *pokemones;
	size_t cantidad_pokemones;
	size_t size;
};

/**
 * Recibe la pokedex, el pokemon y la posicion, así asigna los datos a 
 * los pokemones que corresponde
 * No devuelve nada ya que solo copia
 */
void asignar_datos_pokemones(struct pokedex *pokedex, struct pokemon pokemon,
			     int i)
{
	strcpy(pokedex->pokemones[i].nombre, pokemon.nombre);
	pokedex->pokemones[i].tipo = pokemon.tipo;
	pokedex->pokemones[i].fuerza = pokemon.fuerza;
	pokedex->pokemones[i].destreza = pokemon.destreza;
	pokedex->pokemones[i].resistencia = pokemon.resistencia;
}

/**
 * Recibe la pokedex y el pokemon a insertar, se implementa el algoritmo de ordenamiento
 * por insercion, así los pokemones estan ordenados alfabeticamente. Devuelve
 * Devuelve true si los pokemones fueron ordenados correctamente, si falla devuelve false
 */
bool insertion_sort(struct pokedex *pokedex, struct pokemon pokemon)
{
	int i = (int)pokedex->cantidad_pokemones - 1;

	while (i >= 0 &&
	       strcmp(pokedex->pokemones[i].nombre, pokemon.nombre) > 0) {
		pokedex->pokemones[i + 1].nombre =
			realloc(pokedex->pokemones[i + 1].nombre,
				(strlen(pokedex->pokemones[i].nombre) + 1) *
					sizeof(char));
		if (!pokedex->pokemones[i + 1].nombre)
			return false;

		asignar_datos_pokemones(pokedex, pokedex->pokemones[i], i + 1);
		i--;
	}

	pokedex->pokemones[i + 1].nombre =
		realloc(pokedex->pokemones[i + 1].nombre,
			(strlen(pokemon.nombre) + 1) * sizeof(char));
	if (!pokedex->pokemones[i + 1].nombre)
		return false;

	asignar_datos_pokemones(pokedex, pokemon, i + 1);
	pokedex->cantidad_pokemones++;
	return true;
}

struct pokedex *pokedex_crear()
{
	struct pokedex *pokedex = malloc(sizeof(struct pokedex));

	if (!pokedex)
		return NULL;

	pokedex->cantidad_pokemones = 0;
	pokedex->size = 10;
	pokedex->pokemones = calloc(pokedex->size, sizeof(struct pokemon));
	if (!pokedex->pokemones)
		return NULL;

	return pokedex;
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (!pokedex || !pokemon.nombre)
		return false;

	if (pokedex->size == pokedex->cantidad_pokemones) {
		pokedex->size *= 2;
		pokedex->pokemones =
			realloc(pokedex->pokemones,
				pokedex->size * sizeof(struct pokemon));
		if (!pokedex->pokemones)
			return false;
	}

	pokedex->pokemones[pokedex->cantidad_pokemones].nombre =
		malloc((strlen(pokemon.nombre) + 1) * sizeof(char));
	if (!pokedex->pokemones[pokedex->cantidad_pokemones].nombre)
		return false;

	if (!insertion_sort(pokedex, pokemon))
		return false;

	return true;
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	if (!pokedex)
		return 0;

	return pokedex->cantidad_pokemones;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	if (!pokedex || !nombre)
		return NULL;

	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		if (strcmp(nombre, pokedex->pokemones[i].nombre) == 0)
			return &pokedex->pokemones[i];
	}

	return NULL;
}

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	if (!pokedex)
		return 0;

	size_t pokemones_iterados = 0;

	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		pokemones_iterados++;

		if (funcion == NULL || !funcion(&pokedex->pokemones[i], ctx))
			return pokemones_iterados;
	}

	return pokemones_iterados;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	if (!pokedex)
		return;

	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		free(pokedex->pokemones[i].nombre);
	}
	free(pokedex->pokemones);
	free(pokedex);
}
