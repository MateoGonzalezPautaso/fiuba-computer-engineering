#include <stdio.h>

size_t longitud_cadena(const char *s) {
    size_t cantidad = 0;
    while (s[cantidad] != '\0') {
        cantidad++;
    }
    return cantidad;
}

int main() {
    char *texto = "Mateo";
    size_t longitud = longitud_cadena(texto);
    printf("La palabra %s tiene %ld caracteres\n", texto, longitud);
    return 0;
}