#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#ifndef NARGS
#define NARGS 4
#endif

#define EXITO 0
#define ERROR 1

/**
 * La funcion se encarga de recibir el mensaje de error,
 * imprimirlo por pantalla y luego finalizar la ejecución
 * del programa. Es utilizada para evitar la repeticion de
 * codigo en el manejo de excepciones
 */
void
imprimir_error(const char *mensaje)
{
	perror(mensaje);
	exit(ERROR);
}

/**
 * La funcion se encarga de liberar los argumentos utilizados
 * para pasar por parametro a execvp(), itera el arreglo y
 * aplica free() a cada elemento.
 *
 * La funcion recibe los argumentos y la cantidad de estos
 */
void
liberar_argumentos(char *args[], int cantidad_args)
{
	for (int i = 1; i <= cantidad_args; i++)
		free(args[i]);
}

/**
 * La funcion se encarga de procesar la ejecucion del comando
 * junto a los argumentos del mismo, manejando a la vez los posibles
 * errores.
 *
 * La funcion recibe los argumentos y la cantidad de estos
 */
void
ejecutar_comando(char *args[], int cantidad_args)
{
	pid_t pid = fork();
	if (pid == ERROR)
		imprimir_error("fork() falló\n");

	if (pid == 0) {  // Proceso hijo
		args[cantidad_args + 1] = NULL;
		execvp(args[0], args);

		// Solo se ejecuta en caso de error
		liberar_argumentos(args, cantidad_args);
		imprimir_error("execvp() falló\n");
	} else {  // Proceso padre
		wait(NULL);
		liberar_argumentos(args, cantidad_args);
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2)  // argv[0] =./xargs , argv[1] = comando
		imprimir_error("Numero de argumentos invalido\n");

	char *args[NARGS + 2];  // comando + 4 argumentos + NULL
	args[0] = argv[1];

	char *buffer = NULL;
	size_t buffer_size = 0;  // size = 0 asi getline() asigna memoria
	ssize_t caracteres_leidos;
	int cantidad_args = 0;

	while ((caracteres_leidos = getline(&buffer, &buffer_size, stdin)) != -1) {
		buffer[caracteres_leidos - 1] = '\0';

		args[cantidad_args + 1] = strdup(buffer);
		if (!args[cantidad_args + 1]) {
			liberar_argumentos(args, cantidad_args);
			free(buffer);
			imprimir_error("strdup() falló");
		}

		cantidad_args++;

		if (cantidad_args == NARGS) {
			ejecutar_comando(args, cantidad_args);
			cantidad_args = 0;
		}
	}

	if (cantidad_args > 0)
		ejecutar_comando(args, cantidad_args);

	free(buffer);

	return EXITO;
}
