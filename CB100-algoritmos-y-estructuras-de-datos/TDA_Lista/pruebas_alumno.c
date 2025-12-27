#include "pa2m.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
};

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
	Lista *lista;
};

struct pila {
	Lista *lista;
};

struct cola {
	Lista *lista;
};

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = (struct pokemon *)_p1;
	struct pokemon *p2 = (struct pokemon *)_p2;

	return strcmp(p1->nombre, p2->nombre);
}

bool funcion_dummy(void *elemento, void *ctx)
{
	return true;
}

void crearListaDebeRetornarLista()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista fue creada exitosamente");
	lista_destruir(lista);
}

void listaNuevaDebeTenerCeroNodos()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista->cantidad_nodos == 0,
		     "La lista nueva tiene 0 nodos");
	lista_destruir(lista);
}

void listaNuevaDebeTenerNodosNull()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista->primero == NULL,
		     "El primer nodo de una lista nueva es NULL");
	pa2m_afirmar(lista->ultimo == NULL,
		     "El ultimo nodo de una lista nueva es NULL");
	lista_destruir(lista);
}

void agregarElementoListaDebeRetornarBool()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	bool resultado = lista_agregar_elemento(lista, 0, &pokemon);
	pa2m_afirmar(resultado == true,
		     "El elemento fue agregado correctamente");
	lista_destruir(lista);
}

void agregarElementoAlFinalDebeRetornarBool()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	bool resultado = lista_agregar_al_final(lista, &pokemon);
	pa2m_afirmar(resultado == true,
		     "El elemento fue agregado correctamente al final");
	lista_destruir(lista);
}

void listaDebeTenerUnElemento()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	lista_agregar_elemento(lista, 0, &pokemon);
	pa2m_afirmar(lista->cantidad_nodos == 1, "La lista tiene 1 elemento");
	lista_destruir(lista);
}

void listaDebeTenerDosElementos()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon1 = { "Mateo", 'A', 10 };
	struct pokemon pokemon2 = { "Juan", 'B', 11 };
	lista_agregar_elemento(lista, 0, &pokemon1);
	lista_agregar_elemento(lista, 1, &pokemon2);
	pa2m_afirmar(lista->cantidad_nodos == 2, "La lista tiene 2 elementos");
	lista_destruir(lista);
}

void obtenerElementoDebeRetornarBool()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	lista_agregar_elemento(lista, 0, &pokemon);
	void *elemento_encontrado;
	bool resultado = lista_obtener_elemento(lista, 0, &elemento_encontrado);
	pa2m_afirmar(resultado = true,
		     "El elemento obtenido es igual al agregado");
	lista_destruir(lista);
}

void buscarElementoDebeRetornarElemento()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	lista_agregar_elemento(lista, 0, &pokemon);
	struct pokemon *encontrado = (struct pokemon *)lista_buscar_elemento(
		lista, &pokemon, comparar_nombre_pokemon);
	pa2m_afirmar(encontrado != NULL,
		     "El elemento buscado es igual al agregado");
	lista_destruir(lista);
}

void quitarElementoDebeRetornarBool()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	lista_agregar_elemento(lista, 0, &pokemon);
	void *elemento_quitado;
	bool resultado = lista_quitar_elemento(lista, 0, &elemento_quitado);
	pa2m_afirmar(resultado == true, "Quitar un elemento retorna true");
	lista_destruir(lista);
}

void quitarElementoDeListaVaciaRetornaFalse()
{
	Lista *lista = lista_crear();
	void *elemento_quitado;
	bool resultado = lista_quitar_elemento(lista, 0, &elemento_quitado);
	pa2m_afirmar(resultado == false,
		     "Quitar un elemento de una lista vacia retorna false");
	lista_destruir(lista);
}

void crearIteradorDebeRetornarIterador()
{
	Lista *lista = lista_crear();
	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "El iterador fue creado exitosamente");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void iteradorSiguienteDebeRetornarFalse()
{
	Lista *lista = lista_crear();
	Lista_iterador *iterador = lista_iterador_crear(lista);
	bool resultado = lista_iterador_hay_siguiente(iterador);
	pa2m_afirmar(resultado == false,
		     "El iterador retorna false si no hay siguiente");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void iteradorSiguienteDebeRetornarTrue()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon1 = { "Mateo", 'A', 10 };
	struct pokemon pokemon2 = { "Juan", 'B', 11 };
	lista_agregar_elemento(lista, 0, &pokemon1);
	lista_agregar_al_final(lista, &pokemon2);
	Lista_iterador *iterador = lista_iterador_crear(lista);
	bool resultado = lista_iterador_hay_siguiente(iterador);
	pa2m_afirmar(resultado == true,
		     "El iterador retorna true si hay siguiente");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void iteradorInternoDebeRetornarElementosIterados()
{
	Lista *lista = lista_crear();
	struct pokemon pokemon1 = { "Mateo", 'A', 10 };
	struct pokemon pokemon2 = { "Juan", 'B', 11 };
	lista_agregar_elemento(lista, 0, &pokemon1);
	lista_agregar_al_final(lista, &pokemon2);
	int ctx = 1;
	size_t iterados =
		lista_iterar_elementos(lista, funcion_dummy, (void *)&ctx);
	pa2m_afirmar(
		iterados == 2,
		"El iterador interno retorna la cantidad de elementos iterados");
	lista_destruir(lista);
}

void crearPilaDebeRetornarPila()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "La pila fue creada exitosamente");
	pila_destruir(pila);
}

void pilaNuevaDebeTenerCeroNodos()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila_esta_vacía(pila) == true,
		     "La pila nueva tiene 0 nodos");
	pila_destruir(pila);
}

void apilarElementoPilaDebeRetornarBool()
{
	Pila *pila = pila_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	bool resultado = pila_apilar(pila, &pokemon);
	pa2m_afirmar(resultado == true,
		     "El elemento fue apilado correctamente");
	pila_destruir(pila);
}

void pilaDebeTenerUnElemento()
{
	Pila *pila = pila_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	pila_apilar(pila, &pokemon);
	size_t cantidad = pila_cantidad(pila);
	pa2m_afirmar(cantidad == 1, "La pila tiene 1 elemento");
	pila_destruir(pila);
}

void pilaTopeDebeRetornarElemento()
{
	Pila *pila = pila_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	pila_apilar(pila, &pokemon);
	void *elemento = pila_tope(pila);
	pa2m_afirmar(elemento != NULL, "El tope de la pila no es nulo");
	pila_destruir(pila);
}

void pilaDesapilarDebeRetornarElemento()
{
	Pila *pila = pila_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	pila_apilar(pila, &pokemon);
	void *elemento = pila_desapilar(pila);
	pa2m_afirmar(elemento != NULL, "Desapilar la pila retorna elemento");
	pila_destruir(pila);
}

void crearColaDebeRetornarCola()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "La cola fue creada exitosamente");
	cola_destruir(cola);
}

void colaNuevaDebeTenerCeroNodos()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_esta_vacía(cola) == true,
		     "La cola nueva tiene 0 nodos");
	cola_destruir(cola);
}

void encolarElementoColaDebeRetornarBool()
{
	Cola *cola = cola_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	bool resultado = cola_encolar(cola, &pokemon);
	pa2m_afirmar(resultado == true,
		     "El elemento fue encolado correctamente");
	cola_destruir(cola);
}

void colaDebeTenerUnElemento()
{
	Cola *cola = cola_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	cola_encolar(cola, &pokemon);
	size_t cantidad = cola_cantidad(cola);
	pa2m_afirmar(cantidad == 1, "La cola tiene 1 elemento");
	cola_destruir(cola);
}

void colaFrenteDebeRetornarElemento()
{
	Cola *cola = cola_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	cola_encolar(cola, &pokemon);
	void *elemento = cola_frente(cola);
	pa2m_afirmar(elemento != NULL, "El frente de la cola no es nulo");
	cola_destruir(cola);
}

void colaDesencolarDebeRetornarElemento()
{
	Cola *cola = cola_crear();
	struct pokemon pokemon = { "Mateo", 'A', 10 };
	cola_encolar(cola, &pokemon);
	void *elemento = cola_desencolar(cola);
	pa2m_afirmar(elemento != NULL, "Desencolar la cola retorna elemento");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Lista");
	crearListaDebeRetornarLista();
	listaNuevaDebeTenerCeroNodos();
	listaNuevaDebeTenerNodosNull();
	agregarElementoListaDebeRetornarBool();
	agregarElementoAlFinalDebeRetornarBool();
	listaDebeTenerUnElemento();
	listaDebeTenerDosElementos();
	obtenerElementoDebeRetornarBool();
	buscarElementoDebeRetornarElemento();
	quitarElementoDebeRetornarBool();
	quitarElementoDeListaVaciaRetornaFalse();
	crearIteradorDebeRetornarIterador();
	iteradorSiguienteDebeRetornarFalse();
	iteradorSiguienteDebeRetornarTrue();
	iteradorInternoDebeRetornarElementosIterados();

	pa2m_nuevo_grupo("Pruebas de Pila");
	crearPilaDebeRetornarPila();
	pilaNuevaDebeTenerCeroNodos();
	apilarElementoPilaDebeRetornarBool();
	pilaDebeTenerUnElemento();
	pilaTopeDebeRetornarElemento();
	pilaDesapilarDebeRetornarElemento();

	pa2m_nuevo_grupo("Pruebas de Cola");
	crearColaDebeRetornarCola();
	colaNuevaDebeTenerCeroNodos();
	encolarElementoColaDebeRetornarBool();
	colaDebeTenerUnElemento();
	colaFrenteDebeRetornarElemento();
	colaDesencolarDebeRetornarElemento();

	return pa2m_mostrar_reporte();
}
