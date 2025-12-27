#ifndef POKEMON_H
#define POKEMON_H

#include "src/hash.h"
#include <stdio.h>
#include <string.h>

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
 * Iterar el ABB para contar los pokemones por tipo e ir imprimiendo el contenido
 * del nodo del ABB
 */
bool contar_imprimir_pokemon(char *clave, void *_p1, void *_cantidad_tipo)
{
	struct pokemon *p1 = (struct pokemon *)_p1;
	printf("Nombre %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       p1->nombre, p1->tipo, p1->fuerza, p1->destreza, p1->resistencia);

	int *cantidad_tipo = (int *)_cantidad_tipo;

	switch (p1->tipo) {
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

	return true;
}

/**
 * Recibe la pokedex e imprime el formato pedido por el enunciado
 * No devuelve nada, solo imprime
 */
void imprimir_pokedex(hash_t *hash)
{
	int cantidad_tipo[7] = { 0, 0, 0, 0, 0, 0, 0 };

	hash_iterar(hash, contar_imprimir_pokemon, &cantidad_tipo);

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
