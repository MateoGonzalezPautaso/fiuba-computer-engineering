#include "logica.h"
#include "menu.h"
#include "pokedex.h"
#include "lista.h"
#include "utilidades.h"
#include "../extra/engine.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANCHO_TABLERO 32
#define ALTO_TABLERO 15
#define POKEMONES_TABLERO 7
#define TIEMPO 60

int jugar_logica(int entrada, void *ctx);
void iniciar_pokemones(Lista *pokemones_tablero, juego_t *juego);
void imprimir_final(juego_t *juego);

typedef struct pokemon_tablero {
	int x;
	int y;
	char *nombre;
	char *patron_movimiento;
	char *color;
	size_t puntaje;
	size_t indice_patron;
} pokemon_tablero_t;

typedef struct jugador {
	int x;
	int y;
	int iteraciones;
	bool movimiento;
	pokemon_tablero_t *capturado;
} jugador_t;

struct juego {
	menu_t *menu;
	pokedex_t *pokedex;
	jugador_t *jugador;
	Lista *pokemones;
	Lista *pokemones_atrapados;
	long int semilla;
	hash_t *colores;
	int contador;
	int tiempo;
	int puntaje;
	int multiplicador;
	int maximo_multiplicador;
	int combo;
	int maximo_combo;
};

typedef struct combo {
	size_t actual;
	size_t inicio;
	size_t fin;
	juego_t *juego;
} combo_t;

typedef struct elemento {
	char caracter;
	char *color;
	void *elemento;
} elemento_t;

void iniciar_juego(juego_t *juego, jugador_t *jugador)
{
	jugador->x = 0;
	jugador->y = 0;
	jugador->iteraciones = 0;
	jugador->movimiento = false;
	jugador->capturado = NULL;

	juego->semilla = 0;
	juego->contador = 0;
	juego->tiempo = 0;
	juego->puntaje = 0;
	juego->multiplicador = 1;
	juego->maximo_multiplicador = 0;
	juego->combo = 0;
	juego->maximo_combo = 0;
}

void juego_destruir(juego_t *juego)
{
	if (!juego)
		return;
	menu_destruir(juego->menu);
	pokedex_destruir(juego->pokedex);
	lista_destruir_todo(juego->pokemones, free);
	lista_destruir_todo(juego->pokemones_atrapados, free);
	hash_destruir(juego->colores);
	free(juego->jugador);
	free(juego);
}

juego_t *juego_crear()
{
	menu_t *menu = menu_crear();
	pokedex_t *pokedex = pokedex_crear();
	Lista *pokemones = lista_crear();
	Lista *pokemones_atrapados = lista_crear();
	hash_t *colores = hash_colores();

	jugador_t *jugador = calloc(1, sizeof(jugador_t));
	juego_t *juego = calloc(1, sizeof(juego_t));

	juego->menu = menu;
	juego->pokedex = pokedex;
	juego->jugador = jugador;
	juego->pokemones = pokemones;
	juego->pokemones_atrapados = pokemones_atrapados;
	juego->colores = colores;

	if (!menu || !pokedex || !pokemones || !pokemones_atrapados ||
	    !colores || !jugador || !juego) {
		juego_destruir(juego);
		return NULL;
	}

	if (!pokedex_cargar_csv(pokedex, "datos/pokedex.csv", ',')) {
		pokedex_destruir(pokedex);
	}

	menu_agregar_opcion(menu, "P", "Mostrar Pokedex", mostrar_pokedex);
	menu_agregar_opcion(menu, "J", "Jugar", jugar_sin_semilla);
	menu_agregar_opcion(menu, "S", "Jugar con semilla", jugar_con_semilla);
	menu_agregar_opcion(menu, "Q", "Salir", salir);

	iniciar_juego(juego, jugador);

	return juego;
}

void juego_menu(juego_t *juego)
{
	char opcion = '\0';
	while (opcion != 'Q') {
		menu_imprimir(juego->menu, "Bienvenidos a Pokemon Gon't\n");
		printf("\nIngrese alguna de las opciones: ");

		if (scanf(" %c", &opcion) != 1 || getchar() != '\n') {
			printf("Hubo un error leyendo el parametro ingresado\n");
			while (getchar() != '\n')
				;
			continue;
		}

		opcion = convertir_a_mayuscula(opcion);

		if (!menu_ejecutar_opcion(juego->menu, &opcion, juego)) {
			printf("Opcion no valida");
		}
		printf("\n");
	}
}

void mostrar_pokedex(void *ctx)
{
	juego_t *juego = (juego_t *)ctx;
	if (!juego->pokedex) {
		printf("No hay Pokedex\n");
		return;
	}
	printf("Pokemones conocidos:\n");
	pokedex_imprimir(juego->pokedex);
}

void salir(void *ctx)
{
	printf("Finalizando ejecución...\n");
}

void jugar(juego_t *juego, long int semilla)
{
	jugador_t *jugador = juego->jugador;

	if (semilla == 0) {
		semilla = time(NULL);
		srand((unsigned int)semilla);
		semilla = rand();
	}

	srand((unsigned int)semilla);
	juego->semilla = semilla;

	iniciar_pokemones(juego->pokemones, juego);
	game_loop(jugar_logica, juego);
	mostrar_cursor();

	imprimir_final(juego);

	iniciar_juego(juego, jugador);

	lista_vaciar_sin_destruir(juego->pokemones, free);
	lista_vaciar_sin_destruir(juego->pokemones_atrapados, free);
}

void jugar_sin_semilla(void *ctx)
{
	jugar((juego_t *)ctx, 0);
}

void jugar_con_semilla(void *ctx)
{
	juego_t *juego = (juego_t *)ctx;

	bool valida = false;

	while (!valida) {
		printf("Ingrese la semilla: ");

		if (scanf("%ld", &(juego->semilla)) == 1 && getchar() == '\n') {
			valida = true;
		} else {
			printf("Hubo un error leyendo el parametro ingresado\n");
			while (getchar() != '\n')
				;
		}
	}

	jugar(juego, juego->semilla);
}

void destruir_pokemones_tablero(Lista *pokemones_tablero,
				Lista *pokemones_atrapados)
{
	if (pokemones_tablero)
		lista_destruir_todo(pokemones_tablero, free);
	if (pokemones_atrapados)
		lista_destruir_todo(pokemones_atrapados, free);
}

pokemon_tablero_t *iniciar_pokemon(juego_t *juego)
{
	pokemon_tablero_t *nuevo_pokemon = calloc(1, sizeof(pokemon_tablero_t));
	if (!nuevo_pokemon)
		return NULL;

	nuevo_pokemon->x = rand() % ANCHO_TABLERO;
	nuevo_pokemon->y = rand() % ALTO_TABLERO;

	pokemon_t *pokemon = pokedex_obtener_aleatorio(juego->pokedex);
	nuevo_pokemon->nombre = pokemon->nombre;
	nuevo_pokemon->patron_movimiento = pokemon->patron_movimiento;
	nuevo_pokemon->color = pokemon->color;
	nuevo_pokemon->puntaje = pokemon->puntaje;
	nuevo_pokemon->indice_patron = 0;

	return nuevo_pokemon;
}

void iniciar_pokemones(Lista *pokemones_tablero, juego_t *juego)
{
	for (int i = 0; i < POKEMONES_TABLERO; i++) {
		pokemon_tablero_t *nuevo_pokemon = iniciar_pokemon(juego);

		if (!nuevo_pokemon) {
			destruir_pokemones_tablero(pokemones_tablero, NULL);
			return;
		}

		if (!lista_agregar_al_final(pokemones_tablero, nuevo_pokemon)) {
			free(nuevo_pokemon);
			destruir_pokemones_tablero(pokemones_tablero, NULL);
			return;
		}
	}
}

void mover_pokemon(pokemon_tablero_t *pokemon, int movimiento_jugador_x,
		   int movimiento_jugador_y)
{
	char patron_movimiento =
		pokemon->patron_movimiento[pokemon->indice_patron];
	pokemon->indice_patron = (pokemon->indice_patron + 1) %
				 strlen(pokemon->patron_movimiento);

	int p_x = 0;
	int p_y = 0;

	switch (patron_movimiento) {
	case 'N':
		p_y = -1;
		break;

	case 'S':
		p_y = 1;
		break;

	case 'E':
		p_x = 1;
		break;

	case 'O':
		p_x = -1;
		break;

	case 'J':
		p_x = movimiento_jugador_x;
		p_y = movimiento_jugador_y;
		break;

	case 'I':
		p_x = -movimiento_jugador_x;
		p_y = -movimiento_jugador_y;
		break;

	case 'R':
		p_x = (rand() % 3) - 1;
		p_y = (rand() % 3) - 1;
		;
		break;

	default:
		break;
	}

	pokemon->x = min(ANCHO_TABLERO - 1, max(0, pokemon->x + p_x));
	pokemon->y = min(ALTO_TABLERO - 1, max(0, pokemon->y + p_y));
}

void mover_pokemones(Lista *pokemones, int movimiento_jugador_x,
		     int movimiento_jugador_y)
{
	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemon_tablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);

		if (pokemon)
			mover_pokemon(pokemon, movimiento_jugador_x,
				      movimiento_jugador_y);

		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
}

bool combo(pokemon_tablero_t *p1, pokemon_tablero_t *p2)
{
	bool misma_inicial = (p1->nombre[0] == p2->nombre[0]);
	bool mismo_color = (strcmp(p1->color, p2->color) == 0);

	return p1 && p2 && (misma_inicial || mismo_color);
}

void actualizar_puntaje(juego_t *juego, pokemon_tablero_t *pokemon,
			int indice_pokemon)
{
	jugador_t *jugador = juego->jugador;

	if (!jugador->capturado) {
		juego->multiplicador = 1;
		juego->combo = 0;
	} else {
		if (combo(pokemon, jugador->capturado)) {
			juego->multiplicador++;
			juego->combo++;
			juego->maximo_combo =
				max(juego->maximo_combo, juego->combo);
		} else {
			juego->multiplicador = 1;
			juego->combo = 0;
		}
	}

	int puntos = juego->multiplicador * ((int)(pokemon->puntaje));
	juego->puntaje += puntos;

	juego->maximo_multiplicador =
		max(juego->maximo_multiplicador, juego->multiplicador);

	juego->jugador->capturado = pokemon;
}

void procesar_entrada_jugador(int entrada, juego_t *juego)
{
	jugador_t *jugador = juego->jugador;
	Lista *pokemones = juego->pokemones;
	Lista *pokemones_atrapados = juego->pokemones_atrapados;

	int j_x = 0;
	int j_y = 0;

	if (entrada == TECLA_DERECHA) {
		j_x = 1;
	} else if (entrada == TECLA_IZQUIERDA) {
		j_x = -1;
	} else if (entrada == TECLA_ARRIBA) {
		j_y = -1;
	} else if (entrada == TECLA_ABAJO) {
		j_y = 1;
	}

	if (j_x != 0 || j_y != 0) {
		juego->jugador->iteraciones++;
		juego->jugador->movimiento = true;
	}

	jugador->x = min(ANCHO_TABLERO - 1, max(0, jugador->x + j_x));
	jugador->y = min(ALTO_TABLERO - 1, max(0, jugador->y + j_y));

	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return;
	int indice_pokemon = 0;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemon_tablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);
		lista_iterador_avanzar(iterador);

		if (pokemon && pokemon->x == jugador->x &&
		    pokemon->y == jugador->y) {
			lista_eliminar(pokemones, pokemon);

			if (!lista_agregar_al_final(pokemones_atrapados,
						    pokemon))
				free(pokemon);

			pokemon_tablero_t *nuevo_pokemon =
				iniciar_pokemon(juego);
			if (!nuevo_pokemon)
				return;

			if (!lista_agregar_al_final(pokemones, nuevo_pokemon))
				free(nuevo_pokemon);

			actualizar_puntaje(juego, pokemon, indice_pokemon);
		}

		indice_pokemon++;
	}

	lista_iterador_destruir(iterador);

	if (juego->jugador->movimiento)
		mover_pokemones(pokemones, j_x, j_y);

	juego->jugador->movimiento = false;
}

void imprimir_cabecera(juego_t *juego)
{
	jugador_t *jugador = juego->jugador;
	juego->tiempo = juego->contador / 5;

	printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD
	       "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");

	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET
	       " para salir\n");

	printf("🌱 " ANSI_COLOR_GREEN "%ld\n" ANSI_COLOR_RESET, juego->semilla);
	printf("🕑 " ANSI_COLOR_WHITE "%d " ANSI_COLOR_RESET
	       "👣 " ANSI_COLOR_BLUE "%d " ANSI_COLOR_RESET,
	       TIEMPO - juego->tiempo, jugador->iteraciones);
	printf("❌ " ANSI_COLOR_RED "%d " ANSI_COLOR_RESET
	       "🔥 " ANSI_COLOR_YELLOW "%d\n" ANSI_COLOR_RESET,
	       juego->multiplicador, juego->puntaje);
}

void imprimir_tablero(juego_t *juego)
{
	Lista *pokemones = juego->pokemones;
	jugador_t *jugador = juego->jugador;
	hash_t *colores = juego->colores;

	elemento_t tablero[ALTO_TABLERO][ANCHO_TABLERO];
	memset(tablero, 0, sizeof(tablero));

	elemento_t jugador_tablero = { .caracter = '@',
				       .color = "BLANCO",
				       .elemento = jugador };
	tablero[jugador->y][jugador->x] = jugador_tablero;

	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemon_tablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);

		if (pokemon) {
			elemento_t pokemon_tablero = {
				.caracter = pokemon->nombre[0],
				.color = pokemon->color,
				.elemento = pokemon
			};
			tablero[pokemon->y][pokemon->x] = pokemon_tablero;
		}

		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);

	printf("╔");
	for (int i = 0; i < ANCHO_TABLERO; i++) {
		printf("═");
	}
	printf("╗\n");

	for (int y = 0; y < ALTO_TABLERO; y++) {
		printf("║");
		for (int x = 0; x < ANCHO_TABLERO; x++) {
			elemento_t elemento = tablero[y][x];
			if (elemento.caracter != 0) {
				char *color_ANSI =
					hash_buscar(colores, elemento.color);
				char *string = "%s%c" ANSI_COLOR_RESET;
				printf(string, color_ANSI, elemento.caracter);
			} else {
				printf(" ");
			}
		}
		printf("║\n");
	}

	printf("╚");
	for (int i = 0; i < ANCHO_TABLERO; i++) {
		printf("═");
	}
	printf("╝\n");

	if (jugador->capturado) {
		char *color_ANSI =
			hash_buscar(colores, jugador->capturado->color);
		char *string = "Ultimo capturado: " ANSI_COLOR_BOLD
			       "%s%s\n" ANSI_COLOR_RESET;
		printf(string, color_ANSI, jugador->capturado->nombre);
	}
}

void imprimir_racha(juego_t *juego, combo_t *combo)
{
	Lista_iterador *iterador =
		lista_iterador_crear(juego->pokemones_atrapados);
	if (!iterador)
		return;

	size_t multiplicador = 1;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemon_tablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);

		if (combo->actual >= combo->inicio &&
		    combo->actual <= combo->fin) {
			char *color_ANSI =
				hash_buscar(juego->colores, pokemon->color);

			if (!color_ANSI) {
				char *string = "    - %s ->" ANSI_COLOR_BOLD
					       " %zu puntos\n" ANSI_COLOR_RESET;
				printf(string, pokemon->nombre,
				       multiplicador * pokemon->puntaje);
			} else {
				char *string = "    - %s%s" ANSI_COLOR_RESET
					       " ->" ANSI_COLOR_BOLD
					       " %zu puntos\n" ANSI_COLOR_RESET;
				printf(string, color_ANSI, pokemon->nombre,
				       multiplicador * pokemon->puntaje);
			}

			multiplicador++;
		}
		combo->actual++;
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
}

void imprimir_final(juego_t *juego)
{
	printf(ANSI_COLOR_BOLD "--- FIN ---\n" ANSI_COLOR_RESET);

	if (lista_cantidad_elementos(juego->pokemones_atrapados) == 0) {
		printf("❌ No se atraparon pokemones ❌\n");
		return;
	}

	printf("El maximo multiplicador alcanzado fue de" ANSI_COLOR_BOLD
	       " x%d puntos\n" ANSI_COLOR_RESET,
	       juego->maximo_combo + 1);
	printf("Se obtuvieron un total de" ANSI_COLOR_GREEN
	       " %d puntos\n" ANSI_COLOR_RESET,
	       juego->puntaje);
	printf("Racha de Pokemones: \n");

	Lista_iterador *iterador =
		lista_iterador_crear(juego->pokemones_atrapados);
	if (!iterador)
		return;

	pokemon_tablero_t *actual = NULL;
	pokemon_tablero_t *anterior = NULL;

	size_t combo_actual = 0;
	size_t comienzo_combo_actual = 0;
	size_t mejor_combo = 0;
	size_t comienzo_mejor_combo = 0;

	size_t indice = 0;

	while (lista_iterador_hay_siguiente(iterador)) {
		actual = lista_iterador_obtener_elemento_actual(iterador);

		if (anterior == NULL || combo(actual, anterior)) {
			combo_actual++;
		} else {
			if (combo_actual > mejor_combo) {
				mejor_combo = combo_actual;
				comienzo_mejor_combo = comienzo_combo_actual;
			}

			combo_actual = 1;
			comienzo_combo_actual = indice;
		}

		anterior = actual;
		indice++;
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);

	if (combo_actual > mejor_combo) {
		mejor_combo = combo_actual;
		comienzo_mejor_combo = comienzo_combo_actual;
	}

	combo_t combo = { .actual = 0,
			  .inicio = comienzo_mejor_combo,
			  .fin = comienzo_mejor_combo + mejor_combo - 1 };

	imprimir_racha(juego, &combo);
}

int jugar_logica(int entrada, void *ctx)
{
	juego_t *juego = (juego_t *)ctx;
	borrar_pantalla();

	procesar_entrada_jugador(entrada, juego);
	juego->contador++;

	imprimir_cabecera(juego);
	imprimir_tablero(juego);

	esconder_cursor();

	if (TIEMPO - juego->tiempo == 0)
		return 1;

	return entrada == 'q' || entrada == 'Q';
}