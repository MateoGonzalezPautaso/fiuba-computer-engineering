#include "src/hash.h"
#include "csv.h"
#include "menu.h"
#include "pokemon.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("No ingresaste una ruta o nombre de archivo\n");
		return 1;
	}

	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], ';');
	hash_t *hash = hash_crear(10);
	if (!archivo || !hash) {
		return 1;
	}

	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };
	int fuerza, destreza, resistencia;
	char tipo;
	char *nombre = NULL;

	void *ctx[5] = { &nombre, &tipo, &fuerza, &destreza, &resistencia };

	while (leer_linea_csv(archivo, 5, funciones, ctx) == 5) {
		struct pokemon *pokemon = malloc(sizeof(struct pokemon));
		if (!pokemon) {
			free(nombre);
			break;
		}

		asignar_datos_pokemones(pokemon, nombre, tipo, fuerza, destreza,
					resistencia);

		if (!hash_insertar(hash, pokemon->nombre, pokemon, NULL)) {
			liberar_pokemon(pokemon);
			break;
		}

		nombre = NULL;
	}

	cerrar_archivo_csv(archivo);

	menu_usuario(hash);

	hash_destruir_todo(hash, liberar_pokemon);
	return 0;
}
