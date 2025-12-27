#ifndef MENU_H
#define MENU_H

#include "pokemon.h"
#include "src/abb.h"
#include <stdbool.h>
#include <string.h>

#define CANTIDAD 100

/**
 * Recibe un string y el ctx, asigna memoria para el nuevo string en un char*,
 * lo copia al ctx y luego lo castea a char**
 * Devuelve true si pudo crearlo o false en caso de fallo
 */
bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;

	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

/**
 * Recibe un caracter y el ctx, lo copia al ctx y luego lo castea a char*
 * Devuelve true si pudo copiarlo
 */
bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *str;
	return true;
}

/**
 * Recibe un string y el ctx. La funcion sscanf recibe un *str,
 * el formato y lo copia al ctx pero formateado a int*
 * Devuelve true si pudo leerlo o false en caso de fallo
 */
bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

/**
 * Esta funcion se encarga de recibir la pokedex y hacer el manejo de ingresos
 * del usuario, maneja posibles errores y lo mantiene en bucle hasta que el
 * usuario quiera salir.
 */
void menu_usuario(abb_t *abb)
{
	int opcion = 0;
	char nombre_ingresado[CANTIDAD];

	while (opcion != 3) {
		printf("Ingrese el numero de alguna de las opciones:\n");
		printf("1. Ingresar por teclado un nombre de Pokemon y el programa lo "
		       "busca en la lista\n");
		printf("2. Imprimir todos los Pokemones de la lista por pantalla\n");
		printf("3. Salir\n");

		if (!scanf("%d", &opcion)) {
			printf("Hubo un error leyendo el parametro ingresado\n");
			while (getchar() != '\n')
				;
			continue;
		}

		switch (opcion) {
		case 1:
			printf("Ingrese el nombre de un Pokemon: ");
			if (!scanf("%s", nombre_ingresado)) {
				printf("Hubo un error leyendo el nombre ingresado\n");
				break;
			}
			struct pokemon buscado;
			buscado.nombre = nombre_ingresado;

			struct pokemon *encontrado =
				(struct pokemon *)abb_obtener(abb, &buscado);

			if (!encontrado) {
				printf("Pokemon %s no encontrado\n\n",
				       nombre_ingresado);
			} else {
				printf("***Pokemon encontrado***\n\n");
			}
			break;

		case 2:
			imprimir_pokedex(abb);
			break;

		case 3:
			printf("Saliendo...\n");
			break;

		default:
			printf("Opcion invalida, ingresela de nuevo\n");
			break;
		}
	}
}

#endif // MENU_H
