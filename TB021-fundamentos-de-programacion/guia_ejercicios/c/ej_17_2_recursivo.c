#include <stdio.h>

int n_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * n_factorial(n -1);
}

int main() {
    int n = 4;
    int factorial = n_factorial(n);
    printf("El factorial de %d vale %d\n", n, factorial);
    return 0;
}
