#include <stdio.h>

size_t longitud_cadena(const char *s) {
    if (*s == '\0') {
        return 0;
    }
    return 1 + longitud_cadena(s + 1);
}

int main() {
    char *texto = "Mateo";
    size_t longitud = longitud_cadena(texto);
    printf("La palabra %s tiene %ld caracteres\n", texto, longitud);
    return 0;
}