#include "abb.h"
#include "abb_estructura_privada.h"

typedef struct vector {
	void **vector;
	size_t *posicion;
	size_t tamaño;
} vector_t;

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));
	if (!abb)
		return NULL;

	abb->comparador = comparador;

	return abb;
}

void destruir_todo_recursivo(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	destruir_todo_recursivo(nodo->izq, destructor);
	destruir_todo_recursivo(nodo->der, destructor);

	if (destructor)
		destructor(nodo->elemento);

	free(nodo);
}

void abb_destruir(abb_t *abb)
{
	if (!abb)
		return;

	destruir_todo_recursivo(abb->raiz, NULL);
	free(abb);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb)
		return;

	destruir_todo_recursivo(abb->raiz, destructor);
	free(abb);
}

nodo_t *buscar_predecesor_inmediato(nodo_t *nodo)
{
	while (nodo->der)
		nodo = nodo->der;

	return nodo;
}

nodo_t *borrar_nodo_recursivo(nodo_t *nodo, void *buscado,
			      int (*comparador)(void *, void *),
			      void **encontrado, bool *centinela)
{
	if (!nodo)
		return NULL;

	if (comparador(buscado, nodo->elemento) > 0) {
		nodo->der = borrar_nodo_recursivo(
			nodo->der, buscado, comparador, encontrado, centinela);
	} else if (comparador(buscado, nodo->elemento) < 0) {
		nodo->izq = borrar_nodo_recursivo(
			nodo->izq, buscado, comparador, encontrado, centinela);
	} else {
		if (encontrado)
			*encontrado = nodo->elemento;

		if (!nodo->der) {
			nodo_t *aux = nodo->izq;
			free(nodo);
			*centinela = true;
			return aux;
		}

		if (!nodo->izq) {
			nodo_t *aux = nodo->der;
			free(nodo);
			*centinela = true;
			return aux;
		}

		nodo_t *predecesor_inmediato =
			buscar_predecesor_inmediato(nodo->izq);

		nodo->elemento = predecesor_inmediato->elemento;

		nodo->izq = borrar_nodo_recursivo(
			nodo->izq, predecesor_inmediato->elemento, comparador,
			NULL, centinela);
	}

	return nodo;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (!abb || !abb->raiz)
		return false;

	bool centinela = false;

	nodo_t *raiz_aux = borrar_nodo_recursivo(
		abb->raiz, buscado, abb->comparador, encontrado, &centinela);

	if (centinela == false) {
		return false;
	}

	abb->raiz = raiz_aux;
	abb->nodos--;
	return true;
}

nodo_t *insertar_recursivo(nodo_t *raiz, void *elemento,
			   int (*comparador)(void *, void *), bool *centinela)
{
	if (!raiz) {
		nodo_t *nueva_raiz = calloc(1, sizeof(nodo_t));
		if (!nueva_raiz) {
			*centinela = false;
			return NULL;
		}

		nueva_raiz->elemento = elemento;
		*centinela = true;
		return nueva_raiz;
	}

	if (comparador(elemento, raiz->elemento) > 0) {
		raiz->der = insertar_recursivo(raiz->der, elemento, comparador,
					       centinela);
	} else {
		raiz->izq = insertar_recursivo(raiz->izq, elemento, comparador,
					       centinela);
	}

	return raiz;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb)
		return false;

	bool centinela = false;

	nodo_t *nuevo_nodo = insertar_recursivo(abb->raiz, elemento,
						abb->comparador, &centinela);

	if (centinela == false) {
		return false;
	}

	abb->raiz = nuevo_nodo;
	abb->nodos++;
	return true;
}

void *obtener_recursivo(nodo_t *nodo, void *elemento,
			int (*comparador)(void *, void *))
{
	if (!nodo)
		return NULL;

	if (comparador(nodo->elemento, elemento) == 0) {
		return nodo->elemento;
	} else if (comparador(nodo->elemento, elemento) > 0) {
		return obtener_recursivo(nodo->izq, elemento, comparador);
	} else {
		return obtener_recursivo(nodo->der, elemento, comparador);
	}
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb || !abb->comparador)
		return NULL;

	return obtener_recursivo(abb->raiz, elemento, abb->comparador);
}

size_t abb_cantidad(abb_t *abb)
{
	if (!abb)
		return 0;

	return abb->nodos;
}

size_t iterar_inorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *),
				void *ctx, bool *centinela)
{
	if (!nodo || !*centinela)
		return 0;

	size_t cantidad = 0;

	cantidad += iterar_inorden_recursivo(nodo->izq, f, ctx, centinela);

	if (!*centinela)
		return cantidad;

	cantidad++;

	if (!f(nodo->elemento, ctx)) {
		*centinela = false;
		return cantidad;
	}

	cantidad += iterar_inorden_recursivo(nodo->der, f, ctx, centinela);

	return cantidad;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	bool centinela = true;

	return iterar_inorden_recursivo(abb->raiz, f, ctx, &centinela);
}

size_t iterar_preorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *),
				 void *ctx, bool *centinela)
{
	if (!nodo || !*centinela)
		return 0;

	size_t cantidad = 0;

	if (!*centinela)
		return cantidad;

	cantidad++;

	if (!f(nodo->elemento, ctx)) {
		*centinela = false;
		return cantidad;
	}

	cantidad += iterar_preorden_recursivo(nodo->izq, f, ctx, centinela);

	cantidad += iterar_preorden_recursivo(nodo->der, f, ctx, centinela);

	return cantidad;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	bool centinela = true;

	return iterar_preorden_recursivo(abb->raiz, f, ctx, &centinela);
}

size_t iterar_postorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *),
				  void *ctx, bool *centinela)
{
	if (!nodo || !*centinela)
		return 0;

	size_t cantidad = 0;

	cantidad += iterar_postorden_recursivo(nodo->izq, f, ctx, centinela);

	cantidad += iterar_postorden_recursivo(nodo->der, f, ctx, centinela);

	if (!*centinela)
		return cantidad;

	cantidad++;

	if (!f(nodo->elemento, ctx)) {
		*centinela = false;
		return cantidad;
	}

	return cantidad;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz || !f)
		return 0;

	bool centinela = true;

	return iterar_postorden_recursivo(abb->raiz, f, ctx, &centinela);
}

bool llenar_vector(void *elemento, void *_ctx)
{
	vector_t *ctx = (vector_t *)_ctx;

	if ((*(ctx->posicion)) >= (ctx->tamaño))
		return false;

	ctx->vector[(*(ctx->posicion))] = elemento;
	(*(ctx->posicion))++;
	return true;
}

size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector || tamaño == 0)
		return 0;

	size_t pos = 0;
	vector_t ctx = { .vector = vector, .posicion = &pos, .tamaño = tamaño };

	abb_iterar_inorden(abb, llenar_vector, &ctx);
	return (*(ctx.posicion));
}

size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector || tamaño == 0)
		return 0;

	size_t pos = 0;
	vector_t ctx = { .vector = vector, .posicion = &pos, .tamaño = tamaño };

	abb_iterar_preorden(abb, llenar_vector, &ctx);
	return (*(ctx.posicion));
}

size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector || tamaño == 0)
		return 0;

	size_t pos = 0;
	vector_t ctx = { .vector = vector, .posicion = &pos, .tamaño = tamaño };

	abb_iterar_postorden(abb, llenar_vector, &ctx);
	return (*(ctx.posicion));
}