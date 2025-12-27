#include <stdio.h>

int n_factorial(int n) {
    int factorial = 1;
    for (int i = 2; i <= n; i++) { // puede arrancar en 2 para ahorrar una iteracion
        factorial *= i;
    }
    return factorial;
}

int main() {
    int n = 4;
    int factorial = n_factorial(n);
    printf("El factorial de %d vale %d\n", n, factorial);
    return 0;
}
