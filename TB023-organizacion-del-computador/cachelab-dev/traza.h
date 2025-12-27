#ifndef __TRAZA_H__
#define __TRAZA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Formato de la linea del archivo
typedef struct lectura{
    unsigned int instruction_pointer;
    char operacion;
    unsigned int direccion_memoria;
    unsigned int cantidad_bytes;
    unsigned int datos;  
} lectura_t;

typedef struct archivo {
    FILE *archivo;
} archivo_t;

// Funcion para abrir el archivo
archivo_t *abrir_archivo(const char *nombre_archivo);

// Funcion para cerrar el archivo y liberar memoria
void cerrar_archivo(archivo_t *archivo);

// Función para leer y parsear las líneas
bool leer_linea_traza(archivo_t *archivo, lectura_t *lectura);

#endif /* __TRAZA_H__ */