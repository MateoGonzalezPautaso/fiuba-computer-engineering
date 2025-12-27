#include "utilidades.h"

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

char convertir_a_mayuscula(char c)
{
	if (c >= 'a' && c <= 'z') {
		return c - ('a' - 'A');
	}
	return c;
}

void lista_vaciar_sin_destruir(Lista *lista, void (*destructor)(void *))
{
	if (!lista)
		return;

	void *elemento_quitado = NULL;
	while (lista_cantidad_elementos(lista) > 0) {
		if (lista_quitar_elemento(lista, 0, &elemento_quitado)) {
			if (destructor) {
				destructor(elemento_quitado);
			}
		}
	}
}

bool lista_eliminar(Lista *lista, void *elemento)
{
	if (!lista || !elemento)
		return false;

	size_t posicion = 0;
	void *elemento_encontrado = NULL;

	while (posicion < lista_cantidad_elementos(lista)) {
		if (lista_obtener_elemento(lista, posicion,
					   &elemento_encontrado) &&
		    elemento_encontrado == elemento) {
			void *elemento_quitado = NULL;
			return lista_quitar_elemento(lista, posicion,
						     &elemento_quitado);
		}
		posicion++;
	}

	return false;
}

hash_t *hash_colores()
{
	hash_t *colores = hash_crear(10);
	if (!colores)
		return NULL;

	hash_insertar(colores, "NEGRO", ANSI_COLOR_BLACK, NULL);
	hash_insertar(colores, "ROJO", ANSI_COLOR_RED, NULL);
	hash_insertar(colores, "VERDE", ANSI_COLOR_GREEN, NULL);
	hash_insertar(colores, "AMARILLO", ANSI_COLOR_YELLOW, NULL);
	hash_insertar(colores, "AZUL", ANSI_COLOR_BLUE, NULL);
	hash_insertar(colores, "MAGENTA", ANSI_COLOR_MAGENTA, NULL);
	hash_insertar(colores, "CYAN", ANSI_COLOR_CYAN, NULL);
	hash_insertar(colores, "BLANCO", ANSI_COLOR_WHITE, NULL);

	return colores;
}