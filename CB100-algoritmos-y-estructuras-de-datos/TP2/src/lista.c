#include "lista.h"

typedef struct nodo {
	void *contenido;
	struct nodo *siguiente;
} Nodo;

struct lista {
	Nodo *primero;
	Nodo *ultimo;
	size_t cantidad_nodos;
};

struct lista_iterador {
	Nodo *actual;
};

Lista *lista_crear()
{
	Lista *lista = calloc(1, sizeof(Lista));
	if (!lista)
		return NULL;

	return lista;
}

void lista_destruir(Lista *lista)
{
	if (!lista)
		return;

	Nodo *nodo_aux = lista->primero;

	while (lista->cantidad_nodos != 0) {
		lista->primero = lista->primero->siguiente;
		free(nodo_aux);
		nodo_aux = lista->primero;
		lista->cantidad_nodos--;
	}

	free(lista);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (!lista)
		return;

	Nodo *nodo_aux = lista->primero;

	while (lista->cantidad_nodos != 0) {
		lista->primero = lista->primero->siguiente;

		if (destructor)
			destructor(nodo_aux->contenido);

		free(nodo_aux);
		nodo_aux = lista->primero;
		lista->cantidad_nodos--;
	}

	free(lista);
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (!lista)
		return 0;

	return lista->cantidad_nodos;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (!lista || posicion > lista->cantidad_nodos)
		return false;

	Nodo *nodo = malloc(sizeof(Nodo));
	if (!nodo)
		return false;
	nodo->contenido = cosa;

	if (posicion == 0) {
		nodo->siguiente = lista->primero;
		lista->primero = nodo;
	} else {
		Nodo *nodo_previo = lista->primero;

		for (size_t i = 0; i < (posicion - 1); i++)
			nodo_previo = nodo_previo->siguiente;

		nodo->siguiente = nodo_previo->siguiente;
		nodo_previo->siguiente = nodo;
	}

	if (posicion == lista->cantidad_nodos)
		lista->ultimo = nodo;

	lista->cantidad_nodos++;
	return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (!lista)
		return false;

	Nodo *nodo = malloc(sizeof(Nodo));
	if (!nodo)
		return false;
	nodo->contenido = cosa;
	nodo->siguiente = NULL;

	if (lista->cantidad_nodos == 0) {
		lista->primero = nodo;
	} else {
		lista->ultimo->siguiente = nodo;
	}

	lista->ultimo = nodo;

	lista->cantidad_nodos++;
	return true;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (!lista || posicion >= lista->cantidad_nodos)
		return false;

	Nodo *nodo_aux = lista->primero;
	Nodo *nodo_previo = lista->primero;

	if (posicion == 0) {
		lista->primero = nodo_previo->siguiente;
	} else {
		for (size_t i = 0; i < (posicion - 1); i++)
			nodo_previo = nodo_previo->siguiente;

		nodo_aux = nodo_previo->siguiente;
		nodo_previo->siguiente = nodo_aux->siguiente;
	}

	if (posicion == lista->cantidad_nodos - 1)
		lista->ultimo = nodo_previo;

	if (elemento_quitado)
		*elemento_quitado = nodo_aux->contenido;

	free(nodo_aux);

	lista->cantidad_nodos--;
	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (!lista || !comparador)
		return NULL;

	Nodo *nodo_aux = lista->primero;

	for (size_t i = 0; i < lista->cantidad_nodos; i++) {
		if (comparador(nodo_aux->contenido, buscado) == 0)
			return nodo_aux->contenido;

		nodo_aux = nodo_aux->siguiente;
	}

	return NULL;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (!lista || posicion >= lista->cantidad_nodos)
		return false;

	Nodo *nodo_aux = lista->primero;

	for (size_t i = 0; i < posicion; i++)
		nodo_aux = nodo_aux->siguiente;

	if (elemento_encontrado)
		*elemento_encontrado = nodo_aux->contenido;

	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (!lista || !f)
		return 0;

	Nodo *nodo_aux = lista->primero;

	size_t elementos_iterados = 0;

	while (nodo_aux != NULL) {
		elementos_iterados++;

		if (!f(nodo_aux->contenido, ctx))
			return elementos_iterados;

		nodo_aux = nodo_aux->siguiente;
	}

	return elementos_iterados;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (!lista)
		return NULL;

	Lista_iterador *lista_iterador = malloc(sizeof(Lista_iterador));
	if (!lista_iterador)
		return NULL;
	lista_iterador->actual = lista->primero;

	return lista_iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *lista_iterador)
{
	if (!lista_iterador || !lista_iterador->actual)
		return false;

	return lista_iterador->actual != NULL;
}

void lista_iterador_avanzar(Lista_iterador *lista_iterador)
{
	if (!lista_iterador || !lista_iterador->actual)
		return;

	lista_iterador->actual = lista_iterador->actual->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *lista_iterador)
{
	if (!lista_iterador || !lista_iterador->actual)
		return NULL;

	return lista_iterador->actual->contenido;
}

void lista_iterador_destruir(Lista_iterador *lista_iterador)
{
	if (!lista_iterador)
		return;

	free(lista_iterador);
}
