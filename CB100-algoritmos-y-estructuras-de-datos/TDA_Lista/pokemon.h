#ifndef POKEMON_H
#define POKEMON_H

#include "src/lista.h"

#define TIPO_AGUA 'A'
#define TIPO_FUEGO 'F'
#define TIPO_PLANTA 'P'
#define TIPO_ROCA 'R'
#define TIPO_ELECTRICO 'E'
#define TIPO_NORMAL 'N'
#define TIPO_LUCHA 'L'

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

/**
 * Compara los nombres de los pokemones para poder comprobar
 * si son iguales o no mediante strcmp.
 */
int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = (struct pokemon *)_p1;
	struct pokemon *p2 = (struct pokemon *)_p2;

	return strcmp(p1->nombre, p2->nombre);
}

/**
 * Recibe la pokedex, el pokemon y la posicion, así asigna los datos a
 * los pokemones que corresponde
 * No devuelve nada ya que solo copia
 */
void asignar_datos_pokemones(struct pokemon *pokemon, char *nombre, char tipo,
			     int fuerza, int destreza, int resistencia)
{
	pokemon->nombre = nombre;
	pokemon->tipo = tipo;
	pokemon->fuerza = fuerza;
	pokemon->destreza = destreza;
	pokemon->resistencia = resistencia;
}

/**
 * Recibe la pokedex e imprime el formato pedido por el enunciado
 * No devuelve nada, solo imprime
 */
void imprimir_pokedex(Lista *pokedex)
{
	int cantidad_tipo[7] = { 0, 0, 0, 0, 0, 0, 0 };

	Lista_iterador *i;
	for (i = lista_iterador_crear(pokedex); lista_iterador_hay_siguiente(i);
	     lista_iterador_avanzar(i)) {
		struct pokemon *pokemon;
		pokemon = lista_iterador_obtener_elemento_actual(i);
		printf("Nombre %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
		       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
		       pokemon->destreza, pokemon->resistencia);

		switch (pokemon->tipo) {
		case TIPO_AGUA:
			cantidad_tipo[0]++;
			break;
		case TIPO_FUEGO:
			cantidad_tipo[1]++;
			break;
		case TIPO_PLANTA:
			cantidad_tipo[2]++;
			break;
		case TIPO_ROCA:
			cantidad_tipo[3]++;
			break;
		case TIPO_ELECTRICO:
			cantidad_tipo[4]++;
			break;
		case TIPO_NORMAL:
			cantidad_tipo[5]++;
			break;
		case TIPO_LUCHA:
			cantidad_tipo[6]++;
			break;
		}
	}
	lista_iterador_destruir(i);

	printf("Cantidad de pokemones de cada tipo:\n");
	printf("Agua: %d\n", cantidad_tipo[0]);
	printf("Fuego: %d\n", cantidad_tipo[1]);
	printf("Planta: %d\n", cantidad_tipo[2]);
	printf("Roca: %d\n", cantidad_tipo[3]);
	printf("Electrico: %d\n", cantidad_tipo[4]);
	printf("Normal: %d\n", cantidad_tipo[5]);
	printf("Lucha: %d\n\n", cantidad_tipo[6]);
}

/**
 * Se encarga de liberar el contenido del nodo, que en este caso sería
 * la estructura del pokemon.
 */
void liberar_pokemon(void *contenido)
{
	struct pokemon *pokemon = (struct pokemon *)contenido;
	free(pokemon->nombre);
	free(pokemon);
}

#endif // POKEMON_H
