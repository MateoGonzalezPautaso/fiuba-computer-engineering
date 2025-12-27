#include "src/logica.h"

int main()
{
	juego_t *juego = juego_crear();
	juego_menu(juego);
	juego_destruir(juego);
	return 0;
}