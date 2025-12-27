#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("Tamaño bool: %ld\n", sizeof(bool));
    printf("Tamaño char: %ld\n", sizeof(char));
    printf("Tamaño short: %ld\n", sizeof(short));
    printf("Tamaño int: %ld\n", sizeof(int));
    printf("Tamaño long: %ld\n", sizeof(long));
    printf("Tamaño float: %ld\n", sizeof(float));
    printf("Tamaño double: %ld\n", sizeof(double));
    printf("Tamaño bool: %ld\n", sizeof(bool*));
    printf("Tamaño char: %ld\n", sizeof(char*));
    printf("Tamaño short: %ld\n", sizeof(short*));
    printf("Tamaño int: %ld\n", sizeof(int*));
    printf("Tamaño long: %ld\n", sizeof(long*));
    printf("Tamaño float: %ld\n", sizeof(float*));
    printf("Tamaño double: %ld\n", sizeof(double*));

    return 0;
}