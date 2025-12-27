#include <stdio.h>
#include <string.h>

void invertir(char *s) {
    char *inicio = s; // puntero que apunta al primer valor
    char *fin = s + strlen(s) - 1; // s = 0 , strlen = 5, -1, posicion 5
    while (inicio < fin) {
        char aux = *inicio;
        *inicio = *fin;
        *fin = aux;
        inicio++;
        fin--;
    }
}

int main() {
    char texto[] = "Mateo";
    printf("La cadena sin invertir es %s\n", texto);
    invertir(texto);
    printf("La cadena invertida ahora es %s\n", texto);
    return 0;
}