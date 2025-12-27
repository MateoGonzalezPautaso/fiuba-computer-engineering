#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct archivo_csv {
	FILE *archivo;
	char separador;
};

struct pokedex {
	struct pokemon *pokemones;
	size_t cantidad_pokemones;
};

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}

void abrirUnArchivoInexistenteDebeRetornarNull()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
}

void abrirUnArchivoExistenteDebeRetornarArchivo()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/ejemplo.csv", ';');
	pa2m_afirmar(archivo != NULL, "El archivo existe y pudo abrirse");
	cerrar_archivo_csv(archivo);
}

void comprobarSeparadorDeUnArchivo()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/ejemplo.csv", ';');
	pa2m_afirmar(archivo->separador == ';',
		     "El archivo existe y tiene el separador correcto");
	cerrar_archivo_csv(archivo);
}

void comprobarCantidadDeColumnasLeidas()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/ejemplo.csv", ';');
	bool (*funciones[3])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter,
						       leer_int };
	int entero;
	char caracter;
	char *string = NULL;
	void *punteros[3] = { &string, &caracter, &entero };
	size_t columnas_leidas =
		leer_linea_csv(archivo, 3, funciones, punteros);
	pa2m_afirmar(columnas_leidas == 3,
		     "Las columnas del archivo fueron leidas correctamente");
	free(string);
	cerrar_archivo_csv(archivo);
}

void leerColumnasDeArchivoNullDebeDevolverCero()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	bool (*funciones[3])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter,
						       leer_int };
	int entero;
	char caracter;
	char *string = NULL;
	void *punteros[3] = { &string, &caracter, &entero };
	size_t columnas_leidas =
		leer_linea_csv(archivo, 3, funciones, punteros);
	pa2m_afirmar(columnas_leidas == 0,
		     "Leer la linea del archivo nulo devuelve 0");
	free(string);
	cerrar_archivo_csv(archivo);
}

void comprobarDatosLeidos()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/ejemplo.csv", ';');
	bool (*funciones[3])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter,
						       leer_int };
	int entero;
	char caracter;
	char *string = NULL;
	void *punteros[3] = { &string, &caracter, &entero };
	if (leer_linea_csv(archivo, 3, funciones, punteros)) {
		pa2m_afirmar(strcmp(string, "Pikachu") == 0,
			     "El nombre del pokemon fue leido correctamente");
		pa2m_afirmar(caracter == 'E',
			     "El tipo del pokemon fue leido correctamente");
		pa2m_afirmar(entero == 1,
			     "La fuerza del pokemon fue leida correctamente");
	}
	free(string);
	cerrar_archivo_csv(archivo);
}

void generarErrorEnFuncionDeParseo()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/ejemplo.csv", ';');
	bool (*funciones[2])(const char *, void *) = { crear_string_nuevo,
						       leer_int };
	int invalido = -1;
	char *string = NULL;
	void *punteros[2] = { &string, &invalido };
	size_t columnas_leidas =
		leer_linea_csv(archivo, 3, funciones, punteros);
	pa2m_afirmar(columnas_leidas == 1,
		     "Hubo un error en la funcion de parseo");
	free(string);
	cerrar_archivo_csv(archivo);
}

void crearPokedexDebeRetornarPokdedex()
{
	struct pokedex *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex != NULL, "La Pokedex pudo crearse correctamente");
	pokedex_destruir(pokedex);
}

void pokedexDebeEstarVacia()
{
	struct pokedex *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex->cantidad_pokemones == 0,
		     "La Pokedex tiene 0 Pokemones");
	pokedex_destruir(pokedex);
}

void agregarPokemonDebeRetornarBool()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Pikachu", TIPO_ELECTRICO, 10, 11, 12 };
	bool resultado = pokedex_agregar_pokemon(pokedex, pokemon);
	pa2m_afirmar(resultado == true,
		     "El pokemon fue agregado correctamente");
	pa2m_afirmar(pokedex->cantidad_pokemones == 1,
		     "La pokedex sumo 1 pokemon");
	pokedex_destruir(pokedex);
}

void pokedexNoVaciaDebeRetornarCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon1 = { "Pikachu", TIPO_ELECTRICO, 10, 11, 12 };
	bool resultado1 = pokedex_agregar_pokemon(pokedex, pokemon1);
	struct pokemon pokemon2 = { "Charizard", TIPO_FUEGO, 13, 14, 15 };
	bool resultado2 = pokedex_agregar_pokemon(pokedex, pokemon2);
	if (!resultado1 || !resultado2) {
		printf("Error\n");
	}
	size_t cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 2, "La pokedex tiene 2 pokemones");
	pokedex_destruir(pokedex);
}

void buscarPokemonDebeRetornarPunteroSiSeEncuentra()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Pikachu", TIPO_ELECTRICO, 10, 11, 12 };
	const char *nombre = "Pikachu";
	bool resultado = pokedex_agregar_pokemon(pokedex, pokemon);
	if (!resultado) {
		printf("Error\n");
	}
	const struct pokemon *pokemon_encontrado =
		pokedex_buscar_pokemon(pokedex, nombre);
	pa2m_afirmar(pokemon_encontrado != NULL,
		     "El pokemon fue encontrado exitosamente");
	pokedex_destruir(pokedex);
}

void buscarPokemonDebeRetornarNullSiNoSeEncuentra()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Pikachu", TIPO_ELECTRICO, 10, 11, 12 };
	const char *nombre = "Charizard";
	bool resultado = pokedex_agregar_pokemon(pokedex, pokemon);
	if (!resultado) {
		printf("Error\n");
	}
	const struct pokemon *pokemon_encontrado =
		pokedex_buscar_pokemon(pokedex, nombre);
	pa2m_afirmar(pokemon_encontrado == NULL,
		     "El pokemon no fue encontrado exitosamente");
	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
	abrirUnArchivoExistenteDebeRetornarArchivo();
	comprobarSeparadorDeUnArchivo();
	comprobarCantidadDeColumnasLeidas();
	leerColumnasDeArchivoNullDebeDevolverCero();
	comprobarDatosLeidos();
	generarErrorEnFuncionDeParseo();
	pa2m_nuevo_grupo("Pruebas de Pokedex");
	crearPokedexDebeRetornarPokdedex();
	pokedexDebeEstarVacia();
	agregarPokemonDebeRetornarBool();
	pokedexNoVaciaDebeRetornarCantidad();
	buscarPokemonDebeRetornarPunteroSiSeEncuentra();
	buscarPokemonDebeRetornarNullSiNoSeEncuentra();

	return pa2m_mostrar_reporte();
}
