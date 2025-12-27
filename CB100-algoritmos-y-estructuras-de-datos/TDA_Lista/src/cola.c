#include "cola.h"
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

struct cola {
	Lista *lista;
};

Cola *cola_crear()
{
	Cola *cola = calloc(1, sizeof(Cola));
	if (!cola)
		return NULL;

	cola->lista = lista_crear();
	if (!cola->lista) {
		free(cola);
		return NULL;
	}

	return cola;
}

void cola_destruir(Cola *cola)
{
	if (!cola)
		return;

	lista_destruir(cola->lista);
	free(cola);
}

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	if (!cola)
		return;

	if (!cola->lista) {
		free(cola);
		return;
	}

	lista_destruir_todo(cola->lista, f);
	free(cola);
}

size_t cola_cantidad(Cola *cola)
{
	if (!cola)
		return 0;

	return lista_cantidad_elementos(cola->lista);
}

void *cola_frente(Cola *cola)
{
	if (!cola || !cola->lista || !cola->lista->primero)
		return NULL;

	return cola->lista->primero->contenido;
}

bool cola_encolar(Cola *cola, void *cosa)
{
	if (!cola)
		return false;

	return lista_agregar_al_final(cola->lista, cosa);
}

void *cola_desencolar(Cola *cola)
{
	if (!cola)
		return NULL;

	void *elemento_quitado = NULL;

	if (lista_quitar_elemento(cola->lista, 0, &elemento_quitado))
		return elemento_quitado;

	return NULL;
}

bool cola_esta_vacía(Cola *cola)
{
	if (!cola || !cola->lista || cola->lista->cantidad_nodos == 0)
		return true;

	return false;
}
