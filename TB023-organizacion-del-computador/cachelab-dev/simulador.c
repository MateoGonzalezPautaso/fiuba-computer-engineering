#include "simulador.h"
#include <math.h>

#define ERROR -1
#define PENALTY 100
#define DATOS_INVALIDOS -1

cache_t* iniciar_cache(int C, int E, int S){
    cache_t *cache = calloc(1, sizeof(cache_t));
    // Calcula el tamaño del bloque en bytes
    int B = C/(S*E);
    // Calcula cuantos con cuantos bits se representa S y B usando logaritmo
    datos_cache_t datos = {.bits_s = (int)log2(S), .S = S, .bits_b = (int)log2(B), .B = B, .E = E, .C = C};
    cache->datos_cache = datos;

    cache->lineas = calloc(S, sizeof(linea_t*));
    for (int i = 0; i < S; i++) {
        cache->lineas[i] = calloc(E, sizeof(linea_t));

        for (int j = 0; j < E; j++) {
            // Inicializa los valores de cada linea.  

            cache->lineas[i][j].tag = 0;
            cache->lineas[i][j].valid = 0;
            cache->lineas[i][j].lru = j;        // lru = j para ir llenando la cache en orden cuando hay misses en frío.
            cache->lineas[i][j].dirty = 0;
        }
    }
    return cache;
}

void destruir_cache(cache_t *cache)
{
    for (int i = 0; i < cache->datos_cache.S; i++)
        free(cache->lineas[i]);

    free(cache->lineas);
    free(cache);
}

typedef struct direccion{
    unsigned int tag_leido;
    unsigned int set_index_leido;
    unsigned int block_offset_leido;
} direccion_t;

void parsear_direccion(cache_t *cache, direccion_t *direccion_leida_parseada, unsigned int direccion_leida){
    int bits_set = cache->datos_cache.bits_s;
    int bits_block = cache->datos_cache.bits_b;

    // Para obtener el tag, desplaza la cantidad de bits que ocupa el set y el block offset para sacarlos.
    direccion_leida_parseada->tag_leido = direccion_leida >> (bits_set + bits_block);
    // Para obtener el set_index, desplaza los bits que ocupa el block offset y le aplica una mascara para limpiar el tag
    direccion_leida_parseada->set_index_leido = (direccion_leida >> bits_block) & ((1 << bits_set) - 1);
    // Para obtener el block offset le aplica una mascara que limpia el tag y el set index.
    direccion_leida_parseada->block_offset_leido = direccion_leida & ((1 << bits_block) - 1);
}

/**
 * Acomoda el apartado LRU de las lineas. Cuanto mayor sea el numero representa que 
 * fue accedida mas recientemente
 * La linea que fue accedida hace mas tiempo, es decir, la que podria ser desalojada,
 * tiene como valor 0.
 */
void actualizar_LRU(cache_t *cache, linea_t *set, int indice_linea_buscada)
{
    int E = cache->datos_cache.E;

    for (int i = 0; i < E; i++) {
        if (i != indice_linea_buscada) {
            if (set[i].lru > set[indice_linea_buscada].lru) {
                set[i].lru--;
            }
        }
    }
    // La ultima linea accedida se guarda con el valor mas alto posible
    set[indice_linea_buscada].lru = E - 1;
}

void actualizar_estadisticas_hit(cache_t *cache, char operacion, linea_t *linea_actual) {
    if ( operacion == 'W' ) {
        // hit de escritura
        cache->tiempo_escrituras++;
        cache->stores++;
        linea_actual->dirty = 1;
    } else {
        // hit de lectura
        cache->tiempo_lecturas++;
        cache->loads++;
    }
}

void actualizar_estadisticas_clean_miss(cache_t *cache, char operacion) {
    if(operacion == 'W'){
        // w_miss
        cache->w_miss++;
        cache->tiempo_escrituras += PENALTY + 1;
        cache->stores++;
    } else{
        // r_miss
        cache->r_miss++;
        cache->tiempo_lecturas += PENALTY + 1;
        cache->loads++;
    }
    cache->bytes_leidos += cache->datos_cache.B;
}

void actualizar_estadisticas_dirty_miss(cache_t *cache, char operacion){
    if(operacion == 'W'){
        // w_dirty_miss
        cache->w_dirty_miss++;
        cache->w_miss++;
        cache->tiempo_escrituras += 2*PENALTY + 1;
        cache->stores++;
    } else{
        // r_dirty_miss
        cache->r_dirty_miss++;
        cache->r_miss++;
        cache->tiempo_lecturas += 2*PENALTY + 1;
        cache->loads ++;
    }
    cache->bytes_leidos += cache->datos_cache.B;
    cache->bytes_escritos += cache->datos_cache.B;
}

int buscar_linea_a_desalojar(cache_t *cache, linea_t *set){
    int E = cache->datos_cache.E;

    // Recorre las lineas que estan en el set
    for(int i = 0; i < E; i++){
        if(set[i].lru == 0){
            // Se encontro la linea con LRU = 0 (Tiene que ser desalojada)
            return i;
        }
    }

    return ERROR;  // NO deberia pasar nunca (solo debug)
}

verboso_t cache_cargar_linea(cache_t *cache, lectura_t *lectura, int numero_operacion){
    verboso_t verboso = {0};

    direccion_t direccion_parseada = {0};
    parsear_direccion(cache, &direccion_parseada, lectura->direccion_memoria);

    unsigned int set = direccion_parseada.set_index_leido;
    unsigned int tag = direccion_parseada.tag_leido;
    char operacion = lectura->operacion;

    verboso.indice_operacion = numero_operacion;
    verboso.set_index = set;
    verboso.tag = tag;

    linea_t **lineas = cache->lineas;
    for (int i = 0; i < cache->datos_cache.E; i++) {
        // Recorre las lineas del set buscando si la buscada estaba guardada en la cache   
        linea_t *linea_actual = &(lineas[set][i]);
        if (linea_actual->valid != 0 && linea_actual->tag == tag) {
            // HIT
            verboso.cache_line = i;
            verboso.line_tag = linea_actual->tag;
            verboso.valid_bit = linea_actual->valid;
            verboso.dirty_bit = linea_actual->dirty;
            verboso.ultimo_indice_operacion = linea_actual->ultima_operacion;
            verboso.identificador = hit;
        
            actualizar_estadisticas_hit(cache, operacion, linea_actual);

            linea_actual->ultima_operacion = numero_operacion;
            actualizar_LRU(cache, lineas[set], i);
            return verboso;
        }
    }

    // MISS
    int indice_linea_desalojada = buscar_linea_a_desalojar(cache, lineas[set]);
    linea_t linea_desalojada = lineas[set][indice_linea_desalojada];

    //Inicialimos la nueva línea
    linea_t nueva_linea = {.tag = tag, .valid = 1, .lru = linea_desalojada.lru, .dirty = (operacion == 'W') ? 1 : 0, .ultima_operacion = numero_operacion};
    
    lineas[set][indice_linea_desalojada] = nueva_linea;
    actualizar_LRU(cache,lineas[set],indice_linea_desalojada);

    if(linea_desalojada.valid == 0){
        // Clean miss frio
        actualizar_estadisticas_clean_miss(cache, operacion);
        verboso.line_tag = DATOS_INVALIDOS;
        verboso.identificador = clean_miss;
        verboso.ultimo_indice_operacion = 0;
    }
    else{
        if(linea_desalojada.dirty == 0){
            // Clean miss conflicto
            actualizar_estadisticas_clean_miss(cache,operacion);
            verboso.identificador = clean_miss;
        }
        else{
            // Dirty miss
            actualizar_estadisticas_dirty_miss(cache,operacion);
            verboso.identificador = dirty_miss;
        }
        verboso.line_tag = linea_desalojada.tag;
        verboso.ultimo_indice_operacion = linea_desalojada.ultima_operacion;
    }

    verboso.cache_line = indice_linea_desalojada;
    verboso.valid_bit = linea_desalojada.valid;
    verboso.dirty_bit = linea_desalojada.dirty;

    return verboso;
}

void imprimir_verboso(cache_t *cache, verboso_t verboso)
{
    fprintf(stdout ,"%d ", verboso.indice_operacion);

    // Dependiendo del valor del enum imprime el formato que corresponde
    switch (verboso.identificador)
    {
    case hit:
        fprintf(stdout, "1 ");
        break;
    case clean_miss:
        fprintf(stdout, "2a ");
        break;
    case dirty_miss:
        fprintf(stdout, "2b ");
    }

    fprintf(stdout,"%x %x %d ", verboso.set_index, verboso.tag, verboso.cache_line);

    // Si los datos son invalidos imprime -1, sino imprime un numero en hexadecimal.
    if (verboso.line_tag == DATOS_INVALIDOS) 
        fprintf(stdout, "%d ", DATOS_INVALIDOS);
    else 
        fprintf(stdout, "%x ", verboso.line_tag);

    fprintf(stdout,"%d %d", verboso.valid_bit, verboso.dirty_bit);

    // Si no hay mapeo directo imprime ultimo indice de la operacion del bloque accedido
    if(cache->datos_cache.E > 1)
        fprintf(stdout," %d",verboso.ultimo_indice_operacion);

    fprintf(stdout,"\n");
}

void imprimir_cache(cache_t *cache)
{
    if (!cache)
        return;
    
    // Si solo hay una linea por set imprime que es de mapeo directo, sino imprime el formato con E-ways.
    if (cache->datos_cache.E == 1) fprintf(stdout, "direct-mapped, ");
    else fprintf(stdout,"%d-way, ", cache->datos_cache.E);

    fprintf(stdout,"%d sets, size = %dKB\n", cache->datos_cache.S, cache->datos_cache.C/1024);
    fprintf(stdout,"loads %lu stores %lu total %lu\n", cache->loads, cache->stores, cache->loads + cache->stores);
    fprintf(stdout,"rmiss %lu wmiss %lu total %lu\n", cache->r_miss, cache->w_miss, cache->r_miss + cache->w_miss);
    fprintf(stdout,"dirty rmiss %lu dirty wmiss %lu\n", cache->r_dirty_miss, cache->w_dirty_miss);
    fprintf(stdout,"bytes read %lu bytes written %lu\n", cache->bytes_leidos, cache->bytes_escritos);
    fprintf(stdout,"read time %lu write time %lu\n", cache->tiempo_lecturas, cache->tiempo_escrituras);
    
    size_t accesos_totales = (cache->loads) + (cache->stores);
    size_t misses_totales = (cache->r_miss) + (cache->w_miss);
    double miss_rate = (double)(misses_totales) / (double)(accesos_totales);
    fprintf(stdout,"miss rate %f\n", miss_rate);
}
