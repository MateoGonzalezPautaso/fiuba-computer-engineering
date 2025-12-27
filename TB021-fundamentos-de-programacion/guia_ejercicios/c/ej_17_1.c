#include <stdio.h>

/*
int areatriangulo(int base, int altura) {
    int area;
    area = (base * altura);
    return area;
}


int main() {
    int base = 3;
    int altura = 3;
    int area = areatriangulo(base, altura);
    printf("El area del triangulo es %d\n", area);
    return 0;
}
*/

float area_rect(float base, float altura) {
    float area;
    area = (base * altura);
    return area;
}

int main() {
    float base = 4.5;
    float altura = 5.7;
    float area = area_rect(base, altura);
    printf("El area del triangulo es %f\n", area);
    return 0;
}
