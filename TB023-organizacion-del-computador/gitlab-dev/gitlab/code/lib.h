#ifndef LIB_H
#define LIB_H

#include<stdlib.h>


// Definir una función que remueva duplicados del array de enteros no negativos y devuelva el resultado
// El orden de la secuencia debe mantenerse igual


// Ejemplos:

// Input -> Output
// [1, 1, 2] -> [1, 2]
// [1, 2, 1, 1, 3, 2] -> [1, 2, 3]



int *distinct(const int *values, size_t count, size_t *pResultCount);
// Guardar la cantidad de valores distintos en la memoria apuntada por
// pResultCount. Si values == NULL o count == 0, entonces *pResultCount == 0.

#endif /* LIB_H */
