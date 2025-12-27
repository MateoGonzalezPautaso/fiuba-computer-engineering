#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define FACTOR_MAXIMO 0.7
#define CAPACIDAD_MINIMA 3

typedef struct par {
	char *clave;
	void *valor;
	struct par *siguiente;
} par_t;

struct hash {
	par_t **tabla_hash;
	size_t capacidad;
	size_t cantidad;
};

unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	unsigned char c;

	while ((c = (unsigned char)*str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

size_t hash_modulo(char *str, size_t capacidad)
{
	if (!str || capacidad == 0)
		return 0;
	return hash(str) % capacidad;
}

hash_t *hash_crear(size_t capacidad_inicial)
{
	if (capacidad_inicial == 0)
		return NULL;

	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;

	if (capacidad_inicial < CAPACIDAD_MINIMA)
		capacidad_inicial = CAPACIDAD_MINIMA;

	hash->tabla_hash = calloc(capacidad_inicial, sizeof(par_t *));
	if (!hash->tabla_hash) {
		hash_destruir(hash);
		return NULL;
	}

	hash->capacidad = capacidad_inicial;
	hash->cantidad = 0;

	return hash;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *nodo = hash->tabla_hash[i];

		while (nodo) {
			par_t *nodo_aux = nodo->siguiente;

			free(nodo->clave);
			if (destructor)
				destructor(nodo->valor);

			free(nodo);
			nodo = nodo_aux;
		}
	}

	free(hash->tabla_hash);
	free(hash);
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;

	return hash->cantidad;
}

bool hash_entrada_valida(hash_t *hash, char *clave)
{
	return hash && clave && *clave != '\0';
}

hash_t *rehash(hash_t *hash)
{
	if (!hash)
		return NULL;

	size_t nueva_capacidad = hash->capacidad * 2;
	par_t **tabla_hash_nueva = calloc(nueva_capacidad, sizeof(par_t *));
	if (!tabla_hash_nueva)
		return NULL;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *nodo = hash->tabla_hash[i];

		while (nodo) {
			par_t *nodo_siguiente = nodo->siguiente;
			size_t posicion_nueva =
				hash_modulo(nodo->clave, nueva_capacidad);

			nodo->siguiente = tabla_hash_nueva[posicion_nueva];
			tabla_hash_nueva[posicion_nueva] = nodo;

			nodo = nodo_siguiente;
		}
	}

	free(hash->tabla_hash);

	hash->tabla_hash = tabla_hash_nueva;
	hash->capacidad = nueva_capacidad;

	return hash;
}

bool crear_nodo_e_insertar(par_t **tabla_hash, size_t posicion, char *clave,
			   void *valor)
{
	size_t longitud = strlen(clave) + 1;
	char *nueva_clave = calloc(longitud, sizeof(char));
	if (!nueva_clave)
		return false;

	strcpy(nueva_clave, clave);

	par_t *nodo_aux = calloc(1, sizeof(par_t));
	if (!nodo_aux) {
		free(nueva_clave);
		return false;
	}

	nodo_aux->clave = nueva_clave;
	nodo_aux->valor = valor;

	nodo_aux->siguiente = tabla_hash[posicion];
	tabla_hash[posicion] = nodo_aux;

	return true;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (!hash_entrada_valida(hash, clave))
		return false;

	float factor_carga =
		(float)(hash->cantidad + 1) / (float)hash->capacidad;

	if (factor_carga > FACTOR_MAXIMO) {
		if (!rehash(hash))
			return false;
	}

	size_t posicion = hash_modulo(clave, hash->capacidad);
	par_t *nodo = hash->tabla_hash[posicion];

	while (nodo) {
		if (strcmp(clave, nodo->clave) == 0) {
			if (encontrado)
				*encontrado = nodo->valor;

			nodo->valor = valor;
			return true;
		}

		nodo = nodo->siguiente;
	}

	if (encontrado)
		*encontrado = NULL;

	if (!crear_nodo_e_insertar(hash->tabla_hash, posicion, clave, valor))
		return false;

	hash->cantidad++;
	return true;
}

void *hash_buscar_aux(hash_t *hash, char *clave, bool *centinela)
{
	if (!hash_entrada_valida(hash, clave))
		return NULL;

	size_t posicion = hash_modulo(clave, hash->capacidad);
	par_t *nodo = hash->tabla_hash[posicion];

	while (nodo) {
		if (strcmp(clave, nodo->clave) == 0) {
			*centinela = true;
			return nodo->valor;
		}

		nodo = nodo->siguiente;
	}

	return NULL;
}

void *hash_buscar(hash_t *hash, char *clave)
{
	bool centinela = false;
	return hash_buscar_aux(hash, clave, &centinela);
}

bool hash_contiene(hash_t *hash, char *clave)
{
	bool centinela = false;
	hash_buscar_aux(hash, clave, &centinela);

	return centinela;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	if (!hash_entrada_valida(hash, clave))
		return NULL;

	size_t posicion = hash_modulo(clave, hash->capacidad);
	par_t *nodo = hash->tabla_hash[posicion];
	par_t *nodo_previo = NULL;

	while (nodo) {
		if (strcmp(clave, nodo->clave) == 0) {
			if (nodo_previo) {
				nodo_previo->siguiente = nodo->siguiente;
			} else {
				hash->tabla_hash[posicion] = nodo->siguiente;
			}

			void *valor = nodo->valor;
			free(nodo->clave);
			free(nodo);
			hash->cantidad--;

			return valor;
		}

		nodo_previo = nodo;
		nodo = nodo->siguiente;
	}

	return NULL;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx)
{
	if (!hash || !f)
		return 0;

	size_t elementos_iterados = 0;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *nodo = hash->tabla_hash[i];

		while (nodo) {
			elementos_iterados++;

			if (!f(nodo->clave, nodo->valor, ctx))
				return elementos_iterados;

			nodo = nodo->siguiente;
		}
	}

	return elementos_iterados;
}