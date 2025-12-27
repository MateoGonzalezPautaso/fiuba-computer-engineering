#ifndef __POKEDEX_H__
#define __POKEDEX_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct pokedex pokedex_t;

typedef struct pokemon {
	char *nombre;
	size_t puntaje;
	char *color;
	char *patron_movimiento;
} pokemon_t;

/**
 * Crea la pokedex para guardar los pokemones
 * 
 * Devuelve la pokedex creada o NULL en caso de error
 */
pokedex_t *pokedex_crear();

/**
 * Destruye la pokedex y aplica la funcion destructora a cada 
 * pokemon para liberar la memoria
 */
void pokedex_destruir(pokedex_t *pokedex);

/**
 * Agrega el pokemon a la pokedex de forma alfabetica
 */
bool pokedex_agregar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon);

/**
 * Recibe un archivo CSV con el formato de ejemplo
 * Pikachu,15,AMARILLO,I
 * y lo carga a la Pokedex
 * 
 * Devuelve true o false en caso de error
 */
bool pokedex_cargar_csv(pokedex_t *pokedex, const char *nombre_archivo,
			char separador);

/**
 * Busca el pokemon en la pokedex
 * 
 * Devuelve el pokemon o NULL en caso de no encontrarlo
 */
pokemon_t *pokedex_buscar_pokemon(pokedex_t *pokedex, char *nombre);

/**
 * Itera sobre la Pokedex y retorna alguno de los pokemones en esta
 * de forma aleatoria
 */
pokemon_t *pokedex_obtener_aleatorio(pokedex_t *pokedex);

/**
 * Imprime la pokedex por pantalla para que el usuario pueda verlo
 */
void pokedex_imprimir(pokedex_t *pokedex);

#endif /* __POKEDEX_H__ */