#include "lib.h"

int contains(const int *array, size_t size, int value) {
    for (size_t i = 0; i < size; i++) {
        if (array[i] == value) {
            return 1; // Valor encontrado en el array
        }
    }
    return 0; // Valor no encontrado en el array
}

int *distinct(const int *values, size_t count, size_t *pResultCount) {
    if (values == NULL || count == 0) {
        *pResultCount = 0;
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));

    size_t resultCount = 0;

    for (size_t i = 0; i < count; i++) {
        if (!contains(result, resultCount, values[i])) {
            result[resultCount] = values[i];
            resultCount++;
        }
    }

    *pResultCount = resultCount;
    return result;
}