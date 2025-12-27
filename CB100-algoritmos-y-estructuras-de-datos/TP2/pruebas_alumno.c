#include "pa2m.h"
#include "src/menu.h"
#include "src/pokedex.h"
#include "src/utilidades.h"
#include "extra/ansi.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct bicho {
	char *nombre;
	char tipo;
	int fuerza;
} bicho_t;

void imprimir_numero(void *parametro)
{
	if (!parametro)
		return;
	int numero = *(int *)parametro;
	printf("El numero es: %d\n", numero);
}

void imprimir_letra(void *parametro)
{
	if (!parametro)
		return;
	char letra = *(char *)parametro;
	printf("La letra es: %c\n", letra);
}

void funcion_dummy(void *ctx)
{
	return;
}

void crearMenuDebeRetornarMenu()
{
	menu_t *menu = menu_crear();
	pa2m_afirmar(menu != NULL, "El Menu fue creado exitosamente");
	menu_destruir(menu);
}

void agregarMenuDebeRetornarTrue()
{
	menu_t *menu = menu_crear();
	bool resultado = menu_agregar_opcion(
		menu, "A", "Imprime el numero por consola", imprimir_numero);
	pa2m_afirmar(resultado == true, "La opcion fue agregada exitosamente");
	menu_destruir(menu);
}

void agregarOpcionNulaMenuDebeRetornarFalse()
{
	menu_t *menu = menu_crear();
	bool resultado = menu_agregar_opcion(menu, NULL, NULL, imprimir_numero);
	pa2m_afirmar(resultado == false,
		     "La opcion no fue agregada exitosamente");
	menu_destruir(menu);
}

void ejecutarOpcionDebeRetornarTrue()
{
	menu_t *menu = menu_crear();
	char *opcion = "A";
	char *identificador = "Imprime el numero por consola";
	int numero = 10;

	menu_agregar_opcion(menu, opcion, identificador, funcion_dummy);
	bool resultado = menu_ejecutar_opcion(menu, opcion, (void *)&numero);

	pa2m_afirmar(resultado == true, "La opcion fue ejecutada exitosamente");
	menu_destruir(menu);
}

void imprimirMenuDebeMostrarMenu()
{
	menu_t *menu = menu_crear();
	bool resultado = false;

	resultado = menu_agregar_opcion(
		menu, "A", "Imprime el numero por consola", imprimir_numero);
	pa2m_afirmar(resultado == true,
		     "La opcion A fue agregada exitosamente");

	resultado = menu_agregar_opcion(
		menu, "B", "Imprime la letra por consola", imprimir_letra);
	pa2m_afirmar(resultado == true,
		     "La opcion B fue agregada exitosamente");

	menu_imprimir(menu, "TEST de Menu por pantalla");

	pa2m_afirmar(resultado == true, "El menu fue impreso por consola");
	menu_destruir(menu);
}

void crearPokedexDebeRetornarPokedex()
{
	pokedex_t *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex != NULL, "La Pokedex fue creada exitosamente");
	pokedex_destruir(pokedex);
}

void agregarPokedexDebeRetornarTrue()
{
	pokedex_t *pokedex = pokedex_crear();
	pokemon_t *pokemon = malloc(sizeof(pokemon_t));
	pokemon->nombre = malloc(strlen("Mateo") + 1);
	pokemon->color = malloc(strlen("Rojo") + 1);
	pokemon->patron_movimiento = malloc(strlen("AABBCCDD") + 1);
	strcpy(pokemon->nombre, "Mateo");
	strcpy(pokemon->color, "Rojo");
	strcpy(pokemon->patron_movimiento, "AABBCCDD");
	pokemon->puntaje = 10;

	bool resultado = pokedex_agregar_pokemon(pokedex, pokemon);
	pa2m_afirmar(resultado == true, "El Pokemon fue agregado exitosamente");
	pokedex_destruir(pokedex);
}

void buscarPokedexDebeBuscarPokemon()
{
	pokedex_t *pokedex = pokedex_crear();
	pokemon_t *pokemon = malloc(sizeof(pokemon_t));
	pokemon->nombre = malloc(strlen("Mateo") + 1);
	pokemon->color = malloc(strlen("Rojo") + 1);
	pokemon->patron_movimiento = malloc(strlen("AABBCCDD") + 1);
	strcpy(pokemon->nombre, "Mateo");
	strcpy(pokemon->color, "Rojo");
	strcpy(pokemon->patron_movimiento, "AABBCCDD");
	pokemon->puntaje = 10;
	pokedex_agregar_pokemon(pokedex, pokemon);

	pokemon_t *encontrado = pokedex_buscar_pokemon(pokedex, "Mateo");
	pa2m_afirmar(encontrado == pokemon,
		     "El Pokemon buscado coincide con el agregado");
	pokedex_destruir(pokedex);
}

void obtenerAleatorioPokedexDebeRetornarPokemonAleatorio()
{
	pokedex_t *pokedex = pokedex_crear();
	pokedex_cargar_csv(pokedex, "datos/pokedex.csv", ',');

	pokemon_t *aleatorio = pokedex_obtener_aleatorio(pokedex);
	pa2m_afirmar(aleatorio != NULL, "Se obtuvo un pokemon aleatorio");
	pokedex_destruir(pokedex);
}

void cargarCSVDebeRetornarTrue()
{
	pokedex_t *pokedex = pokedex_crear();
	bool resultado = pokedex_cargar_csv(pokedex, "datos/pokedex.csv", ',');
	pa2m_afirmar(resultado == true,
		     "El archivo CSV fue cargado correctamente a la Pokedex");

	pokedex_imprimir(pokedex);
	pokedex_destruir(pokedex);
}

void imprimirPokedexDebeMostrarPokedex()
{
	pokedex_t *pokedex = pokedex_crear();

	pokemon_t *pokemon1 = malloc(sizeof(pokemon_t));
	pokemon1->nombre = malloc(strlen("Mateo") + 1);
	pokemon1->color = malloc(strlen("ROJO") + 1);
	pokemon1->patron_movimiento = malloc(strlen("AABBCCDD") + 1);
	strcpy(pokemon1->nombre, "Mateo");
	strcpy(pokemon1->color, "ROJO");
	strcpy(pokemon1->patron_movimiento, "AABBCCDD");
	pokemon1->puntaje = 10;
	bool resultado = pokedex_agregar_pokemon(pokedex, pokemon1);

	pokemon_t *pokemon2 = malloc(sizeof(pokemon_t));
	pokemon2->nombre = malloc(strlen("Juan") + 1);
	pokemon2->color = malloc(strlen("VERDE") + 1);
	pokemon2->patron_movimiento = malloc(strlen("ABCD") + 1);
	strcpy(pokemon2->nombre, "Juan");
	strcpy(pokemon2->color, "VERDE");
	strcpy(pokemon2->patron_movimiento, "ABCD");
	pokemon2->puntaje = 5;
	resultado = pokedex_agregar_pokemon(pokedex, pokemon2);

	pokedex_imprimir(pokedex);

	pa2m_afirmar(resultado == true, "La Pokedex fue impresa por consola");
	pokedex_destruir(pokedex);
}

void maxDebeRetornarMaximo()
{
	int a = 10;
	int b = 11;

	int maximo = max(a, b);
	pa2m_afirmar(maximo == b, "El numero maximo devuelto coincide");
}

void minDebeRetornarMinimo()
{
	int a = 10;
	int b = 11;

	int minimo = min(a, b);
	pa2m_afirmar(minimo == a, "El numero minimo devuelto coincide");
}

void listaVaciarDebeEstarVacia()
{
	Lista *lista = lista_crear();
	bicho_t pokemon1 = { "Mateo", 'A', 10 };
	bicho_t pokemon2 = { "Juan", 'B', 11 };
	bicho_t pokemon3 = { "Pedro", 'C', 12 };

	lista_agregar_elemento(lista, 0, &pokemon1);
	lista_agregar_elemento(lista, 1, &pokemon2);
	lista_agregar_elemento(lista, 2, &pokemon3);

	pa2m_afirmar(lista_cantidad_elementos(lista) == 3,
		     "La lista tiene 3 elementos");
	lista_vaciar_sin_destruir(lista, NULL);
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0,
		     "La lista post vaciado tiene 0 elementos");
	pa2m_afirmar(lista != NULL, "La lista es no nula");
	lista_destruir(lista);
}

void listaEliminarDebeRetornarTrue()
{
	Lista *lista = lista_crear();
	bicho_t pokemon1 = { "Mateo", 'A', 10 };
	bicho_t pokemon2 = { "Juan", 'B', 11 };
	bicho_t pokemon3 = { "Pedro", 'C', 12 };

	lista_agregar_elemento(lista, 0, &pokemon1);
	lista_agregar_elemento(lista, 1, &pokemon2);
	lista_agregar_elemento(lista, 2, &pokemon3);

	pa2m_afirmar(lista_cantidad_elementos(lista) == 3,
		     "La lista tiene 3 elementos");
	bool resultado = lista_eliminar(lista, (void *)&pokemon1);
	pa2m_afirmar(resultado == true,
		     "La lista elimino correctamente el elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2,
		     "La lista tiene 2 elementos despues de eliminar uno");
	lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas MENU ===============");
	crearMenuDebeRetornarMenu();
	agregarMenuDebeRetornarTrue();
	agregarOpcionNulaMenuDebeRetornarFalse();
	ejecutarOpcionDebeRetornarTrue();
	imprimirMenuDebeMostrarMenu();

	pa2m_nuevo_grupo("============== Pruebas Pokedex ===============");
	crearPokedexDebeRetornarPokedex();
	agregarPokedexDebeRetornarTrue();
	buscarPokedexDebeBuscarPokemon();
	imprimirPokedexDebeMostrarPokedex();
	obtenerAleatorioPokedexDebeRetornarPokemonAleatorio();
	cargarCSVDebeRetornarTrue();

	pa2m_nuevo_grupo("============== Pruebas Utilidades ===============");
	maxDebeRetornarMaximo();
	minDebeRetornarMinimo();
	listaVaciarDebeEstarVacia();
	listaEliminarDebeRetornarTrue();

	return pa2m_mostrar_reporte();
}