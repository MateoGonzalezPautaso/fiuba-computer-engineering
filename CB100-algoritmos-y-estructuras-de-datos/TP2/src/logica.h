#ifndef __LOGICA_H__
#define __LOGICA_H__

typedef struct juego juego_t;

/**
 * Crea el juego y todas sus variables
 * 
 * Devuelve el juego creado o NULL en caso de error
 */
juego_t *juego_crear();

/**
 * Destruye el juego y libera toda la memoria
 */
void juego_destruir(juego_t *juego);

/**
 * Imprime el menu y lee las entradas por teclado
 * del jugador
 */
void juego_menu(juego_t *juego);

/**
 * Muestra la Pokedex por pantalla cuando el usuario
 * ingresa la opcion en el menu
 */
void mostrar_pokedex(void *ctx);

/**
 * Finaliza la ejecucion del menu y por lo tanto
 * del programa tambien
 */
void salir(void *ctx);

/**
 * Ingresa al juego con la semilla ingresada por el usuario
 */
void jugar_con_semilla(void *ctx);

/**
 * Ingresa al juego con una semilla random generada
 */
void jugar_sin_semilla(void *ctx);

#endif /* __LOGICA_H__ */