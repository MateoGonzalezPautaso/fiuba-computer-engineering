#ifndef __SIMULADOR_H__
#define __SIMULADOR_H__

#include "traza.h"

// Formato de la linea del set
typedef struct linea {
	unsigned int tag;
	unsigned int valid;
    unsigned int lru;
    unsigned int dirty;
	int ultima_operacion;
} linea_t;

// Formato de los datos de la cache
typedef struct datos_cache{
	int bits_s;		// Tamaño set index
	int S;			// Cantidad de sets
	int bits_b;		// Tamaño block offset
	int B;			// Tamaño del block en bytes
    int E;          // Cantidad de lineas por set
	int C;			// Tamaño de la cache en bytes
} datos_cache_t;

// Formato de la cache
typedef struct cache {
	datos_cache_t datos_cache;    // Bits y tamaños con informacion de la cache
	size_t loads;
	size_t stores;
	size_t r_miss;
	size_t w_miss;
	size_t r_dirty_miss;
	size_t w_dirty_miss;
	size_t bytes_leidos;
	size_t bytes_escritos;
	size_t tiempo_lecturas;
	size_t tiempo_escrituras;
	linea_t **lineas; 			// Matriz de linea, la primera coordenada representa un set, la segunda la linea
} cache_t;

typedef enum identificador{
	hit = 0,
	clean_miss = 1,
	dirty_miss = 2
} identificador_t;

// Formato del modo verboso -v
typedef struct verboso {
	int indice_operacion;
	identificador_t identificador;
	unsigned int set_index;
	unsigned int tag;
	int cache_line;
	int line_tag;
	int valid_bit;
	int dirty_bit;
	int ultimo_indice_operacion;
} verboso_t;

// Funcion para iniciar la cache
cache_t* iniciar_cache(int C, int E, int S);

/**
 * Carga los datos de la lectura a la cache.
 * Devuelve siempre los datos verbosos que pueden ser impresos cuando el modo verboso se activa.
 * 
 * Los datos verbosos se cargan en la estructura verboso_t
 */
verboso_t cache_cargar_linea(cache_t *cache, lectura_t *lectura, int numero_operacion);

// Funcion para imprimir la cache con formato
void imprimir_cache(cache_t *cache);

// Imprime los datos verbosos de la cache
void imprimir_verboso(cache_t *cache, verboso_t verboso);

// Funcion para liberar la memoria ocupada por la estructura cache
void destruir_cache(cache_t *cache);

#endif /* __SIMULADOR_H__ */