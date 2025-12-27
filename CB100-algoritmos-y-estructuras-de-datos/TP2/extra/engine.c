#include "engine.h"
#include "ansi.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//Este archivo está por separado del resto del proyecto porque no es C99 puro.
//Entonces lo compilamos por separado con otros flags.
//Esperemos que funcione para todos 👀

static struct termios inicializar_consola()
{
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	return oldt;
}

static void restaurar_consola(struct termios oldt)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, 0);
}

static int proxima_tecla()
{
	unsigned char c[20];

	if (read(STDIN_FILENO, &c, 20) == -1) {
		return 0;
	}

	if (c[0] == 27) {
		if (c[1] == 91) {
			switch (c[2]) {
			case 65:
				return TECLA_ARRIBA;
			case 66:
				return TECLA_ABAJO;
			case 67:
				return TECLA_DERECHA;
			case 68:
				return TECLA_IZQUIERDA;
			}
		}
	}

	return c[0];
}

void borrar_pantalla()
{
	printf(ANSI_RESET_SCREEN);
}

void esconder_cursor()
{
	printf(ANSI_HIDE_CURSOR);
}

void mostrar_cursor()
{
	printf(ANSI_SHOW_CURSOR);
}

void game_loop(int (*callback)(int, void *), void *data)
{
	int input = 0;
	struct termios oldt = inicializar_consola();
	do {
		usleep(200000);
		input = proxima_tecla();
	} while (callback(input, data) == 0);
	restaurar_consola(oldt);
}
