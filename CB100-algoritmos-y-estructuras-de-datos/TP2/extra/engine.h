#ifndef __ENGINE_H__
#define __ENGINE_H__

#define TECLA_ARRIBA 256
#define TECLA_ABAJO 257
#define TECLA_IZQUIERDA 258
#define TECLA_DERECHA 259

/**
 * Borra la pantalla
 */
void borrar_pantalla();

/**
 * Esconde el cursor
 */
void esconder_cursor();

/**
 * Muestra el cursor
 */
void mostrar_cursor();

/**
 * Invoca el callback 5 veces por segundo (aproximadamente porque no importa tanto para este tp :P). 
 * 
 * El primer parámetro es el código ASCII de la tecla presionada (o algún código especial para los cursores).
 * El segundo es un puntero a datos que el callback puede utilizar.
 *
 * La función invocada puede devolver 0 si el loop debe continuar o diferente a
 * 0 si debe finalizar la ejecución.
*/
void game_loop(int (*callback)(int, void *), void *data);

#endif // __ENGINE_H__
