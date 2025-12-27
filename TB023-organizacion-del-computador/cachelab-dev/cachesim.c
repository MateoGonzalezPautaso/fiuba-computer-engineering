#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "traza.h"
#include "simulador.h"

#define EXITO 0
#define ERROR 1
#define TAMAÑO_MINIMO_PALABRA 4

// Funcion para verificar si el numero es potencia de dos
bool es_potencia_de_2(int x)
{
    return (x > 0) && (x & (x - 1)) == 0;
}

// Revisa si todos los parametros pasados como argumentos  son validos
bool validar_parametros(int C, int E, int S, int n, int m, bool verboso){
    if(!es_potencia_de_2(C) || !es_potencia_de_2(E) || !es_potencia_de_2(S)){
        fprintf(stderr, "Error C, E y S deben ser potencias de 2\n");
        return false;
    }

    if(C <= S * E && C / (S * E) < TAMAÑO_MINIMO_PALABRA){
        fprintf(stderr,"Error Combinacion invalida C, E y S\n");
        return false;
    }

    if(verboso){
        if(n < 0 || m <= n){
            fprintf(stderr,"Error: debe respetarse 0 <= n <= m cuando se invoca el modo verboso\n");
            return false;
        }
    }
    
    return true;
}

int main (int argc, char *argv[]){    
    if(argc != 5 && argc != 8){
        fprintf(stderr,"Numero de argumentos invalido\n");
        return ERROR;
    }

    // Recoleccion de los 4 argumentos obligatorios
    const char *dirreccion_archivo_traza = argv[1];
    // Transformamos en enteros a C, E y S
    int C = atoi(argv[2]);    
    int E = atoi(argv[3]);
    int S = atoi(argv[4]);
    
    // Empieza con valores invalidos para n y 
    int n = -1;
    int m = -1;
    bool verboso = false;
    
    if(argc == 8){
        verboso = true;
        if(strcmp(argv[5], "-v") == 0){
            //Transformamos a int a n y a m.
            n = atoi(argv[6]);
            m = atoi(argv[7]);
        }
    }

    if(!validar_parametros(C,E,S,n,m,verboso))
        return ERROR;
    
    archivo_t *archivo = abrir_archivo(dirreccion_archivo_traza);
    if(!archivo)
        return ERROR;

    lectura_t *lectura = calloc(1, sizeof(lectura_t));
    cache_t *cache = iniciar_cache(C,E,S);

    int operacion_actual = 0;
    //Se repiten las operaciones dentro del while hasta que no haya más lineas que leer dentro del archivo
    while (leer_linea_traza(archivo, lectura)) {        
        verboso_t verboso = cache_cargar_linea(cache, lectura,operacion_actual);

        if(operacion_actual >= n && operacion_actual <= m) 
            imprimir_verboso(cache,verboso);
    
        operacion_actual++;
    }

    imprimir_cache(cache);
    
    cerrar_archivo(archivo);
    free(lectura);
    destruir_cache(cache);

    return EXITO;
}