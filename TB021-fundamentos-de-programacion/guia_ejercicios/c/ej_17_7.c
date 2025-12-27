#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copiar_string(const char *origen, char *destino) {
    size_t longitud = strlen(origen);
    for (size_t i = 0; i <= longitud; i++) {
        destino[i] = origen[i];
    }
}

int main() {
    char *origen = "Mateo";
    char *destino = malloc(strlen(origen) + 1);
    copiar_string(origen, destino);
    printf("La cadena original es %s y la copiada es %s\n", origen, destino);
    free(destino);
    return 0;
}
