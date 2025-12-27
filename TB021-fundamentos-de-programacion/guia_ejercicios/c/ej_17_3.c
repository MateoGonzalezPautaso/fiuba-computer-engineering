#include <stdio.h>

float calcular_promedio(int arreglos[], int cantidad) {
    int total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += arreglos[i];
    }
    float promedio = (float)total / cantidad;
    return promedio;
}

int main() {
    int cantidad = 5;
    int arreglos[] = {1, 2, 3, 8, 9};

    float promedio = calcular_promedio(arreglos, cantidad);
    printf("El promedio es %f\n", promedio);
}


/*
float promedio(int* arreglos, int cantidad) {
    int total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += arreglos[i];
    }
    float promedio = (float)total / cantidad;
    return promedio;

}

int main() {
    int numeros[500] = {8}; // guarda 500 ochos
    numeros[0] = 1;
    numeros[1] = 7;
    numeros[2] = 9;
    float prom = promedio(numeros, 3);
    printf("El promedio es %f\n", prom);
}
*/