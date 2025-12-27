#include "lib.h"

funcCmp_t *getCompareFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcCmp_t *)&intCmp;
        break;
    case TypeString:
        return (funcCmp_t *)&strCmp;
        break;
    case TypeCard:
        return (funcCmp_t *)&cardCmp;
        break;
    default:
        break;
    }
    return 0;
}
funcClone_t *getCloneFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcClone_t *)&intClone;
        break;
    case TypeString:
        return (funcClone_t *)&strClone;
        break;
    case TypeCard:
        return (funcClone_t *)&cardClone;
        break;
    default:
        break;
    }
    return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcDelete_t *)&intDelete;
        break;
    case TypeString:
        return (funcDelete_t *)&strDelete;
        break;
    case TypeCard:
        return (funcDelete_t *)&cardDelete;
        break;
    default:
        break;
    }
    return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcPrint_t *)&intPrint;
        break;
    case TypeString:
        return (funcPrint_t *)&strPrint;
        break;
    case TypeCard:
        return (funcPrint_t *)&cardPrint;
        break;
    default:
        break;
    }
    return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
    // Desreferencio los valores de los punteros para compararlos
    if (*a == *b) {
        return 0;
    } else if (*a < *b) {
        return 1;
    } else {
        return -1;
    }
}

void intDelete(int32_t *a)
{
    free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
    // el "%d" es para formato de numero entero
    fprintf(pFile, "%d", *a);
}

int32_t *intClone(int32_t *a)
{
    int32_t *a_aux = malloc(sizeof(int32_t));
    *a_aux = *a;
    return a_aux;
}

/** Lista **/

list_t *listNew(type_t t)
{
    list_t *lista = calloc(1,sizeof(list_t));
    lista->type = t;
    return lista;
}

uint8_t listGetSize(list_t *l)
{
    return l->size;
}

void *listGet(list_t *l, uint8_t i)
{
    if(i >= l->size) return NULL;

    struct s_listElem *actual = l->first;

    for(uint8_t j=0; j<i; j++) // itero sobre los nodos hasta llegar a la posicion deseada
        actual = actual->next;
    
    return actual->data;
}

void listAddFirst(list_t *l, void *data)
{
    struct s_listElem *nuevo = calloc(1, sizeof(struct s_listElem));
    funcClone_t* clonador_data = getCloneFunction(l->type);
    nuevo->data = clonador_data(data);

    if (l->size != 0) { //Si el tamaño de la lista es distinto de 0, el siguiente nodo al nuevo elemento será el primer 
        nuevo->next = l->first; //elemento de la lista y el anterior a este último será el nuevo elemento
        l->first->prev = nuevo;
    } else { //En caso de que no haya ningún elemento, el nuevo será el primero y el último
        l->last = nuevo;
    }

    l->first = nuevo;
    l->size++;
}

void listAddLast(list_t *l, void *data)
{
    struct s_listElem *nuevo = calloc(1, sizeof(struct s_listElem));
    funcClone_t* clonador_data = getCloneFunction(l->type);
    nuevo->data = clonador_data(data);

    if(l->size == 0) { 
        l->first = nuevo;
    } else {    
        l->last->next = nuevo;
        nuevo->prev = l->last;
    }

    l->size++;
    l->last = nuevo; 
}

list_t *listClone(list_t *l)
{
    list_t *nueva_lista = listNew(l->type);
    if(l->size == 0) return nueva_lista;

    struct s_listElem *actual = l->first;

    for (uint8_t i = 0; i < l->size; i++) {
        listAddLast(nueva_lista, actual->data); // recorre los nodos originales y agrega copia de los mismos en la lista nueva
        actual = actual->next;
    }

    return nueva_lista;
}

void *listRemove(list_t *l, uint8_t i)
{
    if (l->size == 0 || i >= l->size) return 0;

    struct s_listElem *nodo_actual = l->first;

    if (i == 0) { // Si la posicion a eliminar es la primera reasigno l->first
        l->first = nodo_actual->next;
    } else { // Sino hago una iteracion hasta la posicion deseada
        for(uint8_t k = 0; k < i; k++)
            nodo_actual = nodo_actual->next;

        struct s_listElem *nodo_prev = nodo_actual->prev;
        struct s_listElem *nodo_next = nodo_actual->next;
        
        if(nodo_prev != NULL) nodo_prev->next = nodo_next;
        if(nodo_next != NULL) nodo_next->prev = nodo_prev;
    }

    if (i == l->size - 1) // Si la posicion a eliminar es la ultima reasigno l->last
        l->last = nodo_actual->prev;

    void *data = nodo_actual->data; // Uso un puntero auxiliar para no perder referencia a esta
    free(nodo_actual);

    l->size--;
    return data;
}

void listSwap(list_t *l, uint8_t i, uint8_t j)
{
    if(i >= l->size || j >= l->size || i == j) return;

    struct s_listElem *nodo_i = NULL;
    struct s_listElem *nodo_j = NULL;

    struct s_listElem *actual = l->first;   
    for (uint8_t k = 0; k < l->size; k++) {
        if(k == i) nodo_i = actual; // guardo la referencia al nodo i
        if(k == j) nodo_j = actual; // guardo la referencia al nodo j

        if(nodo_i && nodo_j) break; // si ambos son no nulos termino la ejecucion

        actual = actual->next;
    }

    // swap de contenidos
    void* data_aux = nodo_i->data;
    nodo_i->data = nodo_j->data;
    nodo_j->data = data_aux;
}

void listDelete(list_t *l)
{
    funcDelete_t *destructor_datos = getDeleteFunction(l->type);

    listElem_t *actual = l->first;
    listElem_t *nodo_a_eliminar = NULL;

    while (actual != NULL) {
        nodo_a_eliminar = actual; // uso un auxiliar para no perder referencia de los nodos
        actual = actual->next;
    
        destructor_datos(nodo_a_eliminar->data);
        free(nodo_a_eliminar);
    }

    free(l);
}

void listPrint(list_t *l, FILE *pFile)
{
    funcPrint_t* funcion_impresora = getPrintFunction(l->type);
    struct s_listElem *actual = l->first;

    // Formato de impresion
    fprintf(pFile, "[");

    for (uint8_t i = 0; i < l->size; i++) {
        funcion_impresora(actual->data, pFile);
        if(i < l->size - 1) fprintf(pFile, ",");
        actual = actual->next;
    }
    
    fprintf(pFile, "]");
}

/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->cardDeck = cardDeck;
    game->funcGet = funcGet;
    game->funcRemove = funcRemove;
    game->funcSize = funcSize;
    game->funcPrint = funcPrint;
    game->funcDelete = funcDelete;
    return game;
}
int gamePlayStep(game_t *g)
{
    int applied = 0;
    uint8_t i = 0;
    while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
    {
        card_t *a = g->funcGet(g->cardDeck, i);
        card_t *b = g->funcGet(g->cardDeck, i + 1);
        card_t *c = g->funcGet(g->cardDeck, i + 2);
        if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
        {
            card_t *removed = g->funcRemove(g->cardDeck, i);
            cardAddStacked(b, removed);
            cardDelete(removed);
            applied = 1;
        }
        i++;
    }
    return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
    return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
    g->funcDelete(g->cardDeck);
    free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
    g->funcPrint(g->cardDeck, pFile);
}
