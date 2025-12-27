#ifndef __MENU_H__
#define __MENU_H__

#include <stdbool.h>

typedef struct menu menu_t;

/**
 * Crea el menu para el juego cargando todas sus opciones
 * 
 * Devuelve el menu creado o NULL en caso de error
 */
menu_t *menu_crear();

/**
 * Destruye el menu liberando la memoria
 */
void menu_destruir(menu_t *menu);

/**
 * Inserta la opcion solicitada por el usuario al menu junto a su
 * funcion de accion del tipo funcion_t y el identificador de la misma
 * 
 * Devuelve true o false en caso de error
 */
bool menu_agregar_opcion(menu_t *menu, char *opcion, char *identificador,
			 void (*f)(void *));

/**
 * Ejecuta la funcion asociada a la opcion pasada por parametro y le
 * pasa el ctx como parametro a esta misma
 * 
 * Devuelve true o false en caso de error
 */
bool menu_ejecutar_opcion(menu_t *menu, char *opcion, void *ctx);

/**
 * Imprime el menu por pantalla para que el usuario pueda verlo
 */
void menu_imprimir(menu_t *menu, char *titulo);

#endif /* __MENU_H__ */