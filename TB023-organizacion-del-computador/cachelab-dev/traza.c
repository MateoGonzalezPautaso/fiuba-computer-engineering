#include "traza.h"

#define MAX_LINEA 100

archivo_t *abrir_archivo(const char *nombre_archivo)
{
    archivo_t *archivo = malloc(sizeof(archivo_t));
	archivo->archivo = fopen(nombre_archivo, "r");
    
	if (!archivo->archivo) {
        fprintf(stderr,"El archivo de traza no pudo abrirse\n");
		free(archivo);
		return NULL;
	}

	return archivo;
}

void cerrar_archivo(archivo_t *archivo)
{
    if (archivo->archivo)
        fclose(archivo->archivo);

    free(archivo);
}

// Función para leer el archivo y parsear las líneas
bool leer_linea_traza(archivo_t *archivo_traza, lectura_t *lectura)
{
    char linea[MAX_LINEA];

    if(!fgets(linea, sizeof(linea), archivo_traza->archivo))
        return false;

    // Formato de los archivos .xex
    if (sscanf(linea, "0x%x: %c 0x%x %x %x",
            &lectura->instruction_pointer, 
            &lectura->operacion,
            &lectura->direccion_memoria, 
            &lectura->cantidad_bytes, 
            &lectura->datos) == 5) {
        return true;
    }

    return false;
}