#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXITO 0
#define ERROR 1
#define FIN 0

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
 * La funcion se encarga de procesar los numeros
 * mediante el algoritmo de la criba de Eratóstenes
 * con el siguiente pseudo-código
 *
 * p := <leer valor de pipe izquierdo>
 *
 * imprimir p // asumiendo que es primo
 *
 * mientras <pipe izquierdo no cerrado>:
 *      n = <leer siguiente valor de pipe izquierdo>
 *      si n % p != 0:
 *          escribir <n> en el pipe derecho
 *
 * La funcion recibe unicamente el pipe de lectura
 */
void
procesar_criba_eratostenes(int pipe_izq)
{
	int primo;
	ssize_t bytes_leidos = read(pipe_izq, &primo, sizeof(primo));

	if (bytes_leidos == FIN) {
		exit(EXITO);
	} else if (bytes_leidos != sizeof(primo)) {
		imprimir_error("read() falló\n");
	}

	printf("primo %d\n", primo);

	int pipe_der[2];
	if (pipe(pipe_der) == ERROR)
		imprimir_error("pipe() falló\n");

	pid_t pid = fork();
	if (pid == ERROR)
		imprimir_error("fork() falló\n");

	if (pid == 0) {  // Proceso hijo
		close(pipe_izq);
		close(pipe_der[1]);
		procesar_criba_eratostenes(pipe_der[0]);
	} else {  // Proceso padre
		close(pipe_der[0]);

		int numero;
		while (read(pipe_izq, &numero, sizeof(numero)) == sizeof(numero)) {
			if (numero % primo != 0) {
				if (write(pipe_der[1], &numero, sizeof(numero)) !=
				    sizeof(numero))
					imprimir_error("write() falló\n");
			}
		}

		close(pipe_izq);
		close(pipe_der[1]);
		wait(NULL);
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2)  // argv[0] =./primes , argv[1] = n
		imprimir_error("Numero de argumentos invalido\n");

	int numero = atoi(argv[1]);  // Transformo en entero al numero
	if (numero < 2)
		imprimir_error("El número no es mayor o igual a 2\n");

	int pipe_inicial[2];
	if (pipe(pipe_inicial) == ERROR)
		imprimir_error("pipe() falló\n");

	pid_t pid = fork();
	if (pid == ERROR)
		imprimir_error("fork() falló\n");

	if (pid == 0) {                  // Proceso hijo
		close(pipe_inicial[1]);  // Cerrar escritura
		procesar_criba_eratostenes(pipe_inicial[0]);
	} else {                         // Proceso padre
		close(pipe_inicial[0]);  // Cerrar lectura

		for (int i = 2; i <= numero; i++) {
			// Escribir numeros de 2 a n en el pipe
			if (write(pipe_inicial[1], &i, sizeof(i)) != sizeof(i))
				imprimir_error("write() falló\n");
		}

		close(pipe_inicial[1]);  // Cerrar escritura
		wait(NULL);
	}

	return EXITO;
}