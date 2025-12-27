#include "pila.h"
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

struct pila {
	Lista *lista;
};

Pila *pila_crear()
{
	Pila *pila = calloc(1, sizeof(Pila));
	if (!pila)
		return NULL;

	pila->lista = lista_crear();
	if (!pila->lista) {
		free(pila);
		return NULL;
	}

	return pila;
}

void pila_destruir(Pila *pila)
{
	if (!pila)
		return;

	lista_destruir(pila->lista);
	free(pila);
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (!pila)
		return;

	if (!pila->lista) {
		free(pila);
		return;
	}

	lista_destruir_todo(pila->lista, f);
	free(pila);
}

size_t pila_cantidad(Pila *pila)
{
	if (!pila)
		return 0;

	return lista_cantidad_elementos(pila->lista);
}

void *pila_tope(Pila *pila)
{
	if (!pila || !pila->lista || !pila->lista->primero)
		return NULL;

	return pila->lista->primero->contenido;
}

bool pila_apilar(Pila *pila, void *cosa)
{
	if (!pila)
		return false;

	return lista_agregar_elemento(pila->lista, 0, cosa);
}

void *pila_desapilar(Pila *pila)
{
	if (!pila)
		return NULL;

	void *elemento_quitado = NULL;

	if (lista_quitar_elemento(pila->lista, 0, &elemento_quitado))
		return elemento_quitado;

	return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
	if (!pila || !pila->lista || pila->lista->cantidad_nodos == 0)
		return true;

	return false;
}
