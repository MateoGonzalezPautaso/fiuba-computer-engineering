#include "menu.h"
#include "hash.h"
#include "../extra/ansi.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Tipo de dato funcion_t para evitar problemas del compilador
typedef struct funcion {
	void (*f)(void *);
	char *identificador;
} funcion_t;

struct menu {
	hash_t *hash;
};

menu_t *menu_crear()
{
	menu_t *menu = malloc(sizeof(menu_t));
	if (!menu)
		return NULL;

	menu->hash = hash_crear(10);
	if (!menu->hash) {
		free(menu);
		return NULL;
	}

	return menu;
}

/**
 * Libera la memoria ocupada por la funcion y su
 * identificador
 */
void funcion_destruir(void *funcion)
{
	if (!funcion)
		return;

	funcion_t *f = (funcion_t *)funcion;

	free(f->identificador);
	free(f);
}

void menu_destruir(menu_t *menu)
{
	if (!menu)
		return;
	hash_destruir_todo(menu->hash, funcion_destruir);
	free(menu);
}

bool menu_agregar_opcion(menu_t *menu, char *opcion, char *identificador,
			 void (*f)(void *))
{
	if (!menu || !identificador)
		return false;

	funcion_t *funcion = malloc(sizeof(funcion_t));
	if (!funcion)
		return false;
	funcion->f = f;

	size_t longitud = strlen(identificador) + 1;
	char *nuevo_identificador = calloc(longitud, sizeof(char));
	if (!nuevo_identificador) {
		free(funcion);
		return false;
	}

	strcpy(nuevo_identificador, identificador);
	funcion->identificador = nuevo_identificador;

	bool resultado = hash_insertar(menu->hash, opcion, funcion, NULL);
	if (!resultado)
		funcion_destruir(funcion);

	return resultado;
}

bool menu_ejecutar_opcion(menu_t *menu, char *opcion, void *ctx)
{
	if (!menu)
		return false;

	funcion_t *funcion = (funcion_t *)hash_buscar(menu->hash, opcion);
	if (!funcion)
		return false;

	funcion->f(ctx);

	return true;
}

/**
 * Funcion que recibe hash_iterar para imprimir la opcion y su
 * identificador
 */
bool opcion_imprimir(char *opcion, void *valor, void *ctx)
{
	funcion_t *funcion = (funcion_t *)valor;
	char *string = ANSI_COLOR_BOLD "     (%s)" ANSI_COLOR_RESET " %s\n";
	printf(string, opcion, funcion->identificador);
	return true;
}

void menu_imprimir(menu_t *menu, char *titulo)
{
	if (!menu)
		return;

	printf("%s\n", titulo);
	hash_iterar(menu->hash, opcion_imprimir, NULL);
}