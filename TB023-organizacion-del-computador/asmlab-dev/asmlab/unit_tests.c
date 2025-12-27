#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lib.h"

#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"

#define TILDE "✓"
#define CRUZ "✗"

funcCmp_t *getCompareFunction(type_t t);
funcClone_t *getCloneFunction(type_t t);
funcDelete_t *getDeleteFunction(type_t t);
funcPrint_t *getPrintFunction(type_t t);

void testlogTitle(char *title)
{
    printf("\n   %s\n   ", title);
    while (*(title++))
        printf("=");
    printf("\n\n");
}

void testlogSeparator()
{
    printf("    ");
    for (int i = 0; i < 100; i++)
    {
        printf("_");
    }
    printf("\n\n");
}

void testlogAfirm(char *type, int num, char *description)
{
    printf(VERDE "   %s ", TILDE);
    if (num < 10)
    {
        printf(BLANCO " 0%i - %s - %s \n", num, type, description);
    }
    else
    {
        printf(BLANCO " %i - %s - %s \n", num, type, description);
    }
}

/*---------------------------------- AUXILIARES -------------------------------------------*/

void cardDeleteC(card_t *c)
{
    strDelete(c->suit);
    intDelete(c->number);
    listDelete(c->stacked);
    free(c);
}

void arrayDeleteC(array_t *a)
{
    funcDelete_t *delete = getDeleteFunction(a->type);
    for (int i = 0; i < a->size; i++)
    {
        delete (a->data[i]);
    }
    free(a->data);
    free(a);
}

void strDeleteC(char *str)
{
    free(str);
}

/*---------------------------------- INT TEST -------------------------------------------*/

void test01IntCmpConPrimerElementoMayorAlSegundo(char *testType, int testNum, int *number, int *number_2)
{

    assert(intCmp(number, number_2) == -1);
    testlogAfirm(testType, testNum, "Cuando el primer parametro es mayor al segundo IntCmp devuelve -1");
}

void test02IntCmpConPrimerElementoMenorAlSegundo(char *testType, int testNum, int *number, int *number_2)
{

    assert(intCmp(number, number_2) == 1);
    testlogAfirm(testType, testNum, "Cuando el primer párametro es menor al segundo IntCmpDevuelve 1");
}

void test03IntCmpConDosNumerosIguales(char *testType, int testNum, int *number)
{

    testlogAfirm(testType, testNum, "Dados nos números iguales IntCmp devuelve 0");
    assert(intCmp(number, number) == 0);
}

void test04IntPrintDeUnElemento(char *testType, int testNum, int *number)
{
    FILE *file = fopen("outInt.txt", "w");

    intPrint(number, file);
    fclose(file);

    file = fopen("outInt.txt", "r");
    int numberInStream;
    fscanf(file, "%d", &numberInStream);

    assert(intCmp(number, &numberInStream) == 0);

    testlogAfirm(testType, testNum, "Dado un entero intPrint lo imprime correctamente en el stream pasado por parámetro.");
    fclose(file);
}

void test05IntCloneDeUnElemento(char *testType, int testNum, int *number)
{
    int *copia = intClone(number);
    assert(intCmp(number, copia) == 0);
    assert(copia != number);
    testlogAfirm(testType, testNum, "Dado un entero IntClone devuelve el mismo numero en una direccion de memoria distinta");
    intDelete(copia);
}

/*---------------------------------- LIST TEST -------------------------------------------*/

void test01ListNewSinElementos(char *testType, int testNum)
{
    list_t *lista = listNew(0);

    assert(lista->size == 0);
    assert(lista->first == NULL);
    assert(lista->last == NULL);

    testlogAfirm(testType, testNum, "Se crea una lista vacia y se inicializa correctamente");

    listDelete(lista);
}

void test02ListAddFirstEnListaSinElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int nuevo_elemento = 5;

    listAddFirst(lista, &nuevo_elemento);
    assert(lista->size == 1);
    assert(intCmp(lista->first->data, &nuevo_elemento) == 0);
    assert(intCmp(lista->last->data, &nuevo_elemento) == 0);
    assert(&nuevo_elemento != (lista->first->data));
    testlogAfirm(testType, testNum, "Se agrega un elemento en la primera posicion de la lista correctamente");
    listDelete(lista);
}

void test03ListAddFirstConsecutivosEnListaSinElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;

    listAddFirst(lista, &elemento);
    listAddFirst(lista, &elemento2);
    listAddFirst(lista, &elemento3);
    assert(lista->size == 3);
    assert(intCmp(lista->first->data, &elemento3) == 0);
    assert(intCmp(lista->first->next->data, &elemento2) == 0);
    assert(intCmp(lista->last->data, &elemento) == 0);

    testlogAfirm(testType, testNum, "Se agregan varios elementos sucesivamente en la primera posicion de una lista correctamente");
    listDelete(lista);
}

void test04ListGetSizeConListaSinElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);

    assert(listGetSize(lista) == 0);
    testlogAfirm(testType, testNum, "Dada una lista vacia listGetSize devuelve 0");
    listDelete(lista);
}

void test05ListGetSizeConListaDeVariosElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;

    listAddFirst(lista, &elemento);
    listAddFirst(lista, &elemento2);
    listAddFirst(lista, &elemento3);
    assert(listGetSize(lista) == 3);
    testlogAfirm(testType, testNum, "Dada una lista con varios elementos listGetSize devuelve la cantidad correcta");
    listDelete(lista);
}

void test06ListGetConListaDeVariosElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;

    listAddFirst(lista, &elemento);
    listAddFirst(lista, &elemento2);
    listAddFirst(lista, &elemento3);
    assert(intCmp(listGet(lista, 1), &elemento2) == 0);
    testlogAfirm(testType, testNum, "Dada una lista con varios elementos se obtiene el elemento en la posicion desdeada correctamente");
    listDelete(lista);
}

void test07ListAddLastEnListaVacia(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int nuevo_elemento = 5;

    listAddLast(lista, &nuevo_elemento);
    assert(lista->size == 1);
    assert(intCmp(listGet(lista, 0), &nuevo_elemento) == 0);
    assert(&nuevo_elemento != (lista->first->data));
    testlogAfirm(testType, testNum, "Dada una lista vacia se agrega un elemento en la ultima posicion correctamente");
    listDelete(lista);
}

void test08ListRemoveEnListaSinElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);

    assert(listRemove(lista, 10) == 0);
    testlogAfirm(testType, testNum, "Dada una lista vacia eliminar el elemento en la posicion 10 devuelve 0");
    listDelete(lista);
}

void test09ListRemoveEnListaConVariosElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;

    listAddLast(lista, &elemento);
    listAddLast(lista, &elemento2);
    listAddLast(lista, &elemento3);

    void *elemento_obtenido = listRemove(lista, 1);
    assert(lista->size == 2);
    assert(intCmp(listGet(lista, 1), &elemento3) == 0);
    assert(intCmp(elemento_obtenido, &elemento2) == 0);
    intDelete(elemento_obtenido);
    testlogAfirm(testType, testNum, "Dada una lista con varios elementos se elimina correctamente el elemento en la posicion pedida");
    listDelete(lista);
}

void test10ListSwapDeListaVacia(char *testType, int testNum)
{
    list_t *lista = listNew(1);

    listSwap(lista, 10, 100);
    testlogAfirm(testType, testNum, "Dada una lista vacia swapear dos elementos no realiza ninguna accion");
    listDelete(lista);
}

void test11ListSwapEnListaConUnSoloElemento(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    listAddFirst(lista, &elemento);

    listSwap(lista, 0, 100);
    testlogAfirm(testType, testNum, "Dada una lista con un elemento swapear dos elementos no realiza ninguna accion");
    listDelete(lista);
}

void test12ListSwapEnListaDeVariosElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;
    int elemento4 = 50;

    listAddLast(lista, &elemento);
    listAddLast(lista, &elemento2);
    listAddLast(lista, &elemento3);
    listAddLast(lista, &elemento4);

    listSwap(lista, 0, 3);
    assert(intCmp(listGet(lista, 0), &elemento4) == 0);
    assert(intCmp(listGet(lista, 3), &elemento) == 0);
    testlogAfirm(testType, testNum, "Dada una lista con varios elementos swapear dos en posiciones validas elegidas arbitrariamente funciona correctamente");
    listDelete(lista);
}

void test13ListCloneDeListaVacia(char *testType, int testNum)
{
    list_t *lista = listNew(1);

    list_t *nuevaLista = listClone(lista);

    assert(nuevaLista->first == NULL);
    assert(nuevaLista->type == lista->type);
    assert(nuevaLista->last == NULL);
    testlogAfirm(testType, testNum, "Clonar una lista vacia devuelve otra lista vacia");
    listDelete(lista);
    listDelete(nuevaLista);
}

void test14ListCloneDeListaConUnElemento(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;

    listAddLast(lista, &elemento);

    list_t *nuevaLista = listClone(lista);

    assert(intCmp(lista->first->data, nuevaLista->first->data) == 0);
    assert(intCmp(lista->last->data, nuevaLista->last->data) == 0);
    assert(nuevaLista->type == lista->type);
    assert(nuevaLista->size == lista->size);
    testlogAfirm(testType, testNum, "Una lista con un elemento se clona correctamente");
    listDelete(lista);
    listDelete(nuevaLista);
}

void test15ListCloneDeListaConVariosElementos(char *testType, int testNum)
{
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;
    int elemento4 = 50;

    listAddLast(lista, &elemento);
    listAddLast(lista, &elemento2);
    listAddLast(lista, &elemento3);
    listAddLast(lista, &elemento4);

    list_t *nuevaLista = listClone(lista);

    assert(intCmp(lista->first->data, nuevaLista->first->data) == 0);
    assert(intCmp(listGet(lista, 1), listGet(nuevaLista, 1)) == 0);
    assert(intCmp(listGet(lista, 2), listGet(nuevaLista, 2)) == 0);
    assert(intCmp(lista->last->data, nuevaLista->last->data) == 0);
    assert(nuevaLista->type == lista->type);
    assert(nuevaLista->size == lista->size);

    testlogAfirm(testType, testNum, "Una lista varios elementos se clona correctamente");

    listDelete(lista);
    listDelete(nuevaLista);
}

void test16ListPrintDeListaVacia(char *testType, int testNum)
{
    FILE *file = fopen("outListaVacia.txt", "w");
    list_t *lista = listNew(1);
    int contador = 0;
    char ch;

    listPrint(lista, file);
    fclose(file);

    file = fopen("outListaVacia.txt", "r");

    ch = fgetc(file);
    assert(ch == '[');
    ch = fgetc(file);
    assert(ch == ']');

    testlogAfirm(testType, testNum, "Dada una lista vacia, listPrint genera el archivo correspondiente imprimiendo lo esperado '[]'");
    fclose(file);
    listDelete(lista);
}

void test17ListPrintDeListaConUnElemento(char *testType, int testNum)
{
    FILE *file = fopen("outlistaConUnElemento.txt", "w");
    list_t *lista = listNew(1);
    int elemento = 10;
    listAddLast(lista, &elemento);

    listPrint(lista, file);
    fclose(file);

    file = fopen("outlistaConUnElemento.txt", "r");
    int elemntoEnStream;
    fscanf(file, "[%d]", &elemntoEnStream);

    assert(intCmp(listGet(lista, 0), &elemntoEnStream) == 0);

    testlogAfirm(testType, testNum, "Dada una lista con un elemento, listPrint imprime el elemento en el stream pasado por parámetro");
    fclose(file);
    listDelete(lista);
}

void test18ListPrintDeListaConVariosElementos(char *testType, int testNum)
{
    FILE *file = fopen("outlista.txt", "w");
    list_t *lista = listNew(1);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;
    int elemento4 = 50;

    listAddLast(lista, &elemento);
    listAddLast(lista, &elemento2);
    listAddLast(lista, &elemento3);
    listAddLast(lista, &elemento4);

    listPrint(lista, file);
    fclose(file);

    file = fopen("outlista.txt", "r");

    fscanf(file, "[%d, %d, %d, %d]", &elemento, &elemento2, &elemento3, &elemento4);

    assert(intCmp(listGet(lista, 0), &elemento) == 0);
    assert(intCmp(listGet(lista, 1), &elemento2) == 0);
    assert(intCmp(listGet(lista, 2), &elemento3) == 0);
    assert(intCmp(listGet(lista, 3), &elemento4) == 0);

    testlogAfirm(testType, testNum, "Dada una lista con elementos, listPrint imprime los mismos en el stream pasado por parámetro");
    fclose(file);
    listDelete(lista);
}

/*---------------------------------- STR TEST -------------------------------------------*/

void test01StrDeleteVacio(char *testType, int testNum)
{
    char *str = malloc(10 * sizeof(char));
    testlogAfirm(testType, testNum, "Dado un str vacío, strDelete lo elimina");
    strDelete(str);
}

void test02StrDeleteNoVacio(char *testType, int testNum)
{
    char *str = malloc(20 * sizeof(char));
    strcpy(str, "hola mundo");
    testlogAfirm(testType, testNum, "Dado un str no vacío, strDelete lo elimina");
    strDelete(str);
}

void test03StrLenVacio(char *testType, int testNum)
{
    char string[] = "";
    int len = strLen(string);
    assert(len == 0);
    testlogAfirm(testType, testNum, "strLen = 0 con un string vacio");
}

void test04StrLen(char *testType, int testNum)
{
    char string[] = "holaaa";
    int len = strLen(string);
    assert(len == 6);
    testlogAfirm(testType, testNum, "strLen con un string no vacio");
}

void test05StrPrint(char *testType, int testNum)
{
    char str[] = "hola mundo";
    FILE *file = fopen("outStr.txt", "w");
    strPrint(str, file);
    fclose(file);

    int bufferLength = 11;
    char buffer[bufferLength];
    file = fopen("outStr.txt", "r");
    fgets(buffer, bufferLength, file);
    assert(strcmp(buffer, "hola mundo") == 0);
    fclose(file);
    testlogAfirm(testType, testNum, "Dado un str, strPrint lo imprime en un archivo pasado por parametro");
}

void test06StrPrintVacio(char *testType, int testNum)
{
    char str[10] = "";
    FILE *file = fopen("outStrVacio.txt", "w");
    strPrint(str, file);
    fclose(file);

    int bufferLength = 5;
    char buffer[bufferLength];
    file = fopen("outStrVacio.txt", "r");
    fgets(buffer, bufferLength, file);
    assert(strcmp(buffer, "NULL") == 0);
    fclose(file);
    testlogAfirm(testType, testNum, "Dado un str vacio, strPrint imprime NULL archivo pasado por parametro");
}

void test07StrCloneEnStringConVariosElementos(char *testType, int testNum)
{
    char *string = "VAMOSSS RIVERRR";
    char *copy = strClone(string);
    assert(strcmp(string, copy) == 0);
    assert(string != copy);
    testlogAfirm(testType, testNum, "strClone de String con Varios Elementos");
    free(copy);
}

void test08StrCloneDeStringVacio(char *testType, int testNum)
{
    char *string = "";
    char *copy = strClone(string);
    assert(strcmp(string, copy) == 0);
    assert(string != copy);
    testlogAfirm(testType, testNum, "strClone de String Vacio");
    free(copy);
}

void test09StrCmpDeDosStringsConVariosElementos(char *testType, int testNum)
{
    char string[] = "aaaaa";
    char otro[] = "holaaa";
    int resultado = 0;
    resultado = strCmp(string, otro);
    assert(resultado == 1);

    testlogAfirm(testType, testNum, "strCmp de dos strings con elementos");
}

void test10StrCmpDeDosStringsVacios(char *testType, int testNum)
{
    char string[] = "";
    char otro[] = "";
    int resultado = 0;
    resultado = strCmp(string, otro);
    assert(resultado == 0);

    testlogAfirm(testType, testNum, "strCmp de dos strings vacios");
}

void test11StrCmpConUnStrinVacio(char *testType, int testNum)
{
    char string[] = "holaaa";
    char otro[] = "";
    int resultado = 0;
    resultado = strCmp(string, otro);
    assert(resultado == -1);

    testlogAfirm(testType, testNum, "strCmp con un string vacio");
}

/*---------------------------------- ARRAY TEST -------------------------------------------*/

void test01ArrayNew(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    assert(a->type == 1);
    assert(a->capacity == 3);
    testlogAfirm(testType, testNum, "arrayNew");
    arrayDeleteC(a);
}

void test02ArrayAddLastConUnElemento(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    int num = 3;
    arrayAddLast(a, &num);
    assert(*(int *)(a->data[0]) == 3);
    assert(a->size == 1);
    testlogAfirm(testType, testNum, "Se agrega un elemento al final de un array vacio");
    arrayDelete(a);
}

void test03ArrayAddLastConVariosElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);
    arrayAddLast(a, &elemento3);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    assert(*(int *)(a->data[2]) == 30);
    assert(a->size == 3);
    testlogAfirm(testType, testNum, "Se agrega un elemento al final de un array con elementos");
    arrayDelete(a);
}

void test04ArrayAddLastSuperandoLimite(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 2);
    int elemento = 10;
    int elemento2 = 20;
    int elemento3 = 30;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);
    arrayAddLast(a, &elemento3);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    assert(a->size == 2);
    testlogAfirm(testType, testNum, "No se puede agregar un elemento a un array completo");
    arrayDelete(a);
}

void test05ArrayRemoveElementoUnico(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int32_t num = 3;
    arrayAddLast(a, &num);
    int32_t *elementRemoved = arrayRemove(a, 0);
    assert(*elementRemoved == num);
    assert(a->size == 0);
    testlogAfirm(testType, testNum, "Se remueve el unico elemento de un array");
    arrayDeleteC(a);
    intDelete(elementRemoved);
}

void test06ArrayRemoveElementoMedio(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int32_t num = 3;
    int32_t num2 = 5;
    int32_t num3 = 6;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num2);
    arrayAddLast(a, &num3);
    int32_t *elementRemoved = arrayRemove(a, 1);
    assert(*elementRemoved == num2);
    assert(a->size == 2);
    testlogAfirm(testType, testNum, "Se remueve un elemento intermedio de un array");
    arrayDeleteC(a);
    intDelete(elementRemoved);
}

void test07ArrayRemoveElementoUltimo(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int32_t num = 3;
    int32_t num2 = 5;
    int32_t num3 = 6;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num2);
    arrayAddLast(a, &num3);
    int32_t *elementRemoved = arrayRemove(a, 2);
    assert(*elementRemoved == num3);
    assert(a->size == 2);
    testlogAfirm(testType, testNum, "Se remueve el ultimo elemento de un array");
    arrayDeleteC(a);
    intDelete(elementRemoved);
}

void test08ArrayRemoveFueraDeRango(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int num = 3;
    int num2 = 5;
    int num3 = 6;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num2);
    arrayAddLast(a, &num3);
    int *elementRemoved = arrayRemove(a, 3);
    assert(elementRemoved == NULL);
    assert(a->size == 3);
    testlogAfirm(testType, testNum, "No se puede remover un elemento fuera de rango");
    arrayDeleteC(a);
}

void test09ArrayRemoveDeUnArrayConDosElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int num = 3;
    int num1 = 2;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num1);
    uint8_t i = 0;
    int *resultado = arrayRemove(a, i);
    assert(*resultado == num);
    assert(a->size == 1);
    testlogAfirm(testType, testNum, "arrayRemove primer elemento de un array de dos elementos");
    intDelete(resultado);
    arrayDelete(a);
}

void test10ArrayRemoveDeUnArrayConUnElemento(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int num = 3;
    arrayAddLast(a, &num);
    uint8_t i = 0;
    int *resultado = arrayRemove(a, i);
    assert(*resultado == num);
    assert(a->size == 0);
    testlogAfirm(testType, testNum, "arrayRemove unico elemento de un array");
    intDelete(resultado);
    arrayDelete(a);
}

void test11ArrayDeleteArrayVacio(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    arrayDelete(a);
    testlogAfirm(testType, testNum, "Se borra un array vacio");
}

void test12ArrayDeleteArrayConElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    int elemento = 10;
    int elemento2 = 20;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);
    assert(a->size == 2);
    arrayDelete(a);
    testlogAfirm(testType, testNum, "Se borra un array con elementos");
}

void test13ArrayGetSizeVacio(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    uint8_t size = arrayGetSize(a);
    assert(size == 0);
    testlogAfirm(testType, testNum, "Se obtiene el size de un array vacio");
    arrayDelete(a);
}

void test14ArrayGetSizeConUnElemento(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    int num = 3;
    arrayAddLast(a, &num);
    uint8_t size = arrayGetSize(a);
    assert(size == 1);
    testlogAfirm(testType, testNum, "Se obtiene el size de un array con un elemento");
    arrayDelete(a);
}

void test15ArrayGetSizeConVariosElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 10);
    int num = 3;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num);
    arrayAddLast(a, &num);
    uint8_t size = arrayGetSize(a);
    assert(size == 3);
    testlogAfirm(testType, testNum, "Se obtiene el size de un array con varios elementos");
    arrayDelete(a);
}

void test16ArraySwap(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 2);
    int elemento = 10;
    int elemento2 = 20;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    arraySwap(a, 0, 1);
    assert(*(int *)(a->data[0]) == 20);
    assert(*(int *)(a->data[1]) == 10);
    testlogAfirm(testType, testNum, "Se swapean dos elementos de un array");
    arrayDelete(a);
}

void test17ArraySwapExcedido(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 2);
    int elemento = 10;
    int elemento2 = 20;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    arraySwap(a, 3, 1);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    arraySwap(a, 0, 3);
    assert(*(int *)(a->data[0]) == 10);
    assert(*(int *)(a->data[1]) == 20);
    testlogAfirm(testType, testNum, "No se puede swapear a direcciones fuera del array");
    arrayDelete(a);
}

void test18ArrayPrintDeArrayVacio(char *testType, int testNum)
{
    FILE *file = fopen("outArrayVacio.txt", "w");
    array_t *a = arrayNew(1, 5);
    char ch;

    arrayPrint(a, file);
    fclose(file);

    file = fopen("outArrayVacio.txt", "r");

    ch = fgetc(file);
    assert(ch == '[');
    ch = fgetc(file);
    assert(ch == ']');

    testlogAfirm(testType, testNum, "Dada un array vacio, arrayPrint genera el archivo correspondiente imprimiendo lo esperado '[]'");
    fclose(file);
    arrayDelete(a);
}

void test19ArrayPrintDeArrayConUnSoloElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 5);
    int elemento = 10;
    arrayAddLast(a, &elemento);

    FILE *file = fopen("outArray.txt", "w");
    arrayPrint(a, file);
    fclose(file);

    file = fopen("outArray.txt", "r");

    char ch;
    ch = fgetc(file);
    assert(ch == '[');
    ch = fgetc(file);
    assert(ch == '1');
    ch = fgetc(file);
    assert(ch == '0');
    ch = fgetc(file);
    assert(ch == ']');

    testlogAfirm(testType, testNum, "Dada un array con un elemento, arrayPrint genera el archivo correspondiente imprimiendo lo esperado");
    fclose(file);

    arrayDelete(a);
}

void test20ArrayPrintDeArrayConVariosElementos(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 5);
    int elemento = 10;
    int elemento2 = 20;
    arrayAddLast(a, &elemento);
    arrayAddLast(a, &elemento2);

    FILE *file = fopen("outArrayVarios.txt", "w");
    arrayPrint(a, file);
    fclose(file);

    file = fopen("outArrayVarios.txt", "r");

    char ch;
    ch = fgetc(file);
    assert(ch == '[');
    ch = fgetc(file);
    assert(ch == '1');
    ch = fgetc(file);
    assert(ch == '0');
    ch = fgetc(file);
    assert(ch == ',');
    ch = fgetc(file);
    assert(ch == '2');
    ch = fgetc(file);
    assert(ch == '0');
    ch = fgetc(file);
    assert(ch == ']');

    testlogAfirm(testType, testNum, "Dada un array con elementos, arrayPrint genera el archivo correspondiente imprimiendo lo esperado");
    fclose(file);

    arrayDelete(a);
}

void test21ArrayGetDeUnaPosicionValida(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int num = 3;
    int num1 = 2;
    int num2 = 5;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num1);
    arrayAddLast(a, &num2);
    uint8_t i = 1;
    int *resultado = arrayGet(a, i);
    assert(*resultado == num1);
    testlogAfirm(testType, testNum, "arrayGet de posicion Valida");

    arrayDelete(a);
}

void test22ArrayGetDeUnaPosicionInvalida(char *testType, int testNum)
{
    array_t *a = arrayNew(1, 3);
    int num = 3;
    int num1 = 2;
    int num2 = 5;
    arrayAddLast(a, &num);
    arrayAddLast(a, &num1);
    arrayAddLast(a, &num2);
    uint8_t i = -1;
    int *resultado = arrayGet(a, i);
    assert(resultado == NULL);
    testlogAfirm(testType, testNum, "arrayGet de posicion Invalida");

    arrayDelete(a);
}

/*---------------------------------- CARD TEST -------------------------------------------*/

void test01CardNew(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);
    assert(strcmp(card->suit, str) == 0);
    assert(*(card->number) == 12);
    assert((card->stacked->type) == 3);
    assert((card->stacked->size) == 0);
    testlogAfirm(testType, testNum, "cardNew crea correctamente una carta");
    cardDeleteC(card);
}

void test02CardAddStacked(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);

    int32_t number2 = 4;
    char str2[] = "oro";
    card_t *card2 = cardNew(str2, &number2);

    cardAddStacked(card, card2);

    card_t *cardStacked = listGet(card->stacked, 0);

    assert((card->stacked->size) == 1);
    assert(*(cardStacked->number) == number2);
    assert(strcmp(cardStacked->suit, str2) == 0);

    testlogAfirm(testType, testNum, "cardAddStacked agrega una carta al staked de otra");
    cardDeleteC(card);
    cardDeleteC(card2);
}

void test03CardDelete(char *testType, int testNum)
{
    int32_t *number = malloc(sizeof(int32_t));
    *number = 10;
    card_t *card = cardNew("espada", number);

    cardDelete(card);
    free(number);
    testlogAfirm(testType, testNum, "cardDelete de una carta, stacked vacio");
}

void test04CardDeleteConStacked(char *testType, int testNum)
{
    int32_t *number = malloc(sizeof(int32_t));
    *number = 10;
    card_t *card = cardNew("espada", number);
    int32_t number2 = 4;
    char str2[] = "oro";
    card_t *card2 = cardNew(str2, &number2);

    cardAddStacked(card, card2);

    cardDelete(card);
    cardDelete(card2);
    free(number);
    testlogAfirm(testType, testNum, "cardDelete de una carta, stacked no vacio");
}

void test05CardGetNumber(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);

    int32_t *cardNumber = cardGetNumber(card);
    assert(*cardNumber == number);
    testlogAfirm(testType, testNum, "cardGetNumber obtiene correctamente el numero de una carta");

    cardDelete(card);
}

void test06CardGetStackedVacio(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);

    list_t *stacked = cardGetStacked(card);

    assert(stacked->size == 0);
    testlogAfirm(testType, testNum, "cardGetStacked obtiene el stacked vacio");

    cardDelete(card);
}

void test07CardGetStacked(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);

    int32_t number2 = 4;
    char str2[] = "oro";
    card_t *card2 = cardNew(str, &number2);

    cardAddStacked(card, card2);

    card_t *cardStacked = listGet(cardGetStacked(card), 0);
    assert(*(cardStacked->number) == number2);
    assert(strcmp(cardStacked->suit, str2));
    testlogAfirm(testType, testNum, "cardGetStacked obtiene el stacked con una carta");

    cardDelete(card);
    cardDelete(card2);
}

void test08CardGetSuitCartaConSuitNoVacio(char *testType, int testNum)
{
    int32_t number = 10;
    card_t *card = cardNew("espada", &number);
    char *suit = cardGetSuit(card);
    assert(strcmp("espada", suit) == 0);
    cardDelete(card);
    testlogAfirm(testType, testNum, "cardGetSuit de carta con suit de varios elementos");
}

void test09CardGetSuitCartaConSuitVacio(char *testType, int testNum)
{
    int32_t number = 10;
    card_t *card = cardNew("", &number);
    char *suit = cardGetSuit(card);
    assert(strcmp("", suit) == 0);
    cardDelete(card);
    testlogAfirm(testType, testNum, "cardGetSuit de carta con suit vacio");
}

void test10CardCmpDeCartasIguales(char *testType, int testNum)
{
    int32_t number = 15;
    int32_t number2 = 15;
    card_t *card = cardNew("espada", &number);
    card_t *card2 = cardNew("espada", &number2);

    assert(cardCmp(card, card2) == 0);
    testlogAfirm(testType, testNum, "cardCmp de dos cartas con mismo suit y numero");
    cardDelete(card);
    cardDelete(card2);
}

void test11CardCmpDeCartasConSuitDistinto(char *testType, int testNum)
{
    int32_t number = 15;
    int32_t number2 = 15;
    card_t *card = cardNew("copa", &number);
    card_t *card2 = cardNew("espada", &number2);

    assert(cardCmp(card, card2) == 1);
    testlogAfirm(testType, testNum, "cardCmp de dos cartas con suit distinto");
    cardDelete(card);
    cardDelete(card2);
}

void test12CardCmpDeCartasConMismoSuitYNumeroDistitno(char *testType, int testNum)
{
    int32_t number = 24;
    int32_t number2 = 15;
    card_t *card = cardNew("copa", &number);
    card_t *card2 = cardNew("copa", &number2);

    assert(cardCmp(card, card2) == -1);
    testlogAfirm(testType, testNum, "cardCmp de dos cartas con mismo suit y numero distinto");
    cardDelete(card);
    cardDelete(card2);
}

void test13CardClone(char *testType, int testNum)
{
    int32_t number = 10;
    card_t *card = cardNew("espada", &number);
    card_t *cloned = cardClone(card);

    assert(cardCmp(card, cloned) == 0);
    testlogAfirm(testType, testNum, "cardClone");
    cardDelete(cloned);
    cardDelete(card);
}

void test14CardPrint(char *testType, int testNum)
{
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);
    FILE *frame = fopen("outCard.txt", "w");

    cardPrint(card, frame);
    testlogAfirm(testType, testNum, "cardPrint");
    fclose(frame);
    cardDelete(card);
}

/*---------------------------------- CATEDRA TEST -------------------------------------------*/

void testCatedraArray(card_t **cards, uint8_t size)
{
    array_t *array = arrayNew(3, 5);

    for (uint8_t i = 0; i < size; i++)
    {
        arrayAddLast(array, cards[i]);
    }

    FILE *file = fopen("outCatedraArray.txt", "w");

    arrayPrint(array, file);

    card_t *cardDest = arrayGet(array, 1);
    card_t *cardSource = arrayGet(array, 3);

    cardAddStacked(cardDest, cardSource);
    card_t *c = arrayRemove(array, 3);

    arrayPrint(array, file);

    arrayDelete(array);
    cardDelete(c);
    fclose(file);
    testlogAfirm("Catedra", 1, "Se completan los test de la catedra para Array");
}

void testCatedraList(card_t **cards, uint8_t size)
{
    list_t *list = listNew(3);

    for (uint8_t i = 0; i < size; i++)
    {
        listAddLast(list, cards[i]);
    }

    FILE *file = fopen("outCatedraList.txt", "w");
    listPrint(list, file);

    card_t *cardDest = listGet(list, 1);
    card_t *cardSource = listGet(list, 3);

    cardAddStacked(cardDest, cardSource);
    card_t *c = listRemove(list, 3);

    listPrint(list, file);

    listDelete(list);
    cardDelete(c);
    fclose(file);
    testlogAfirm("Catedra", 2, "Se completan los test de la catedra para List");
}

/*-------------------------  TESTS  -------------------------*/

void testInt()
{
    char *type = "Int";

    int32_t *number = malloc(sizeof(int32_t));
    *number = 10;
    int32_t *number_2 = malloc(sizeof(int32_t));
    *number_2 = 8;

    test01IntCmpConPrimerElementoMayorAlSegundo(type, 1, number, number_2);

    test02IntCmpConPrimerElementoMenorAlSegundo(type, 2, number_2, number);
    test03IntCmpConDosNumerosIguales(type, 3, number);

    test04IntPrintDeUnElemento(type, 4, number);

    test05IntCloneDeUnElemento(type, 5, number);

    intDelete(number);
    intDelete(number_2);
}

void testList()
{

    char *type = "List";

    test01ListNewSinElementos(type, 1);

    test02ListAddFirstEnListaSinElementos(type, 2);
    test03ListAddFirstConsecutivosEnListaSinElementos(type, 3);

    test04ListGetSizeConListaSinElementos(type, 4);
    test05ListGetSizeConListaDeVariosElementos(type, 5);

    test06ListGetConListaDeVariosElementos(type, 6);

    test07ListAddLastEnListaVacia(type, 7);

    test08ListRemoveEnListaSinElementos(type, 8);
    test09ListRemoveEnListaConVariosElementos(type, 9);

    test10ListSwapDeListaVacia(type, 10);
    test11ListSwapEnListaConUnSoloElemento(type, 11);
    test12ListSwapEnListaDeVariosElementos(type, 12);

    test13ListCloneDeListaVacia(type, 13);
    test14ListCloneDeListaConUnElemento(type, 14);
    test15ListCloneDeListaConVariosElementos(type, 15);

    test16ListPrintDeListaVacia(type, 16);
    test17ListPrintDeListaConUnElemento(type, 17);
    test18ListPrintDeListaConVariosElementos(type, 18);
}

void testString()
{
    char type[] = "String";

    test01StrDeleteVacio(type, 1);
    test02StrDeleteNoVacio(type, 2);

    test03StrLenVacio(type, 3);
    test04StrLen(type, 4);

    test05StrPrint(type, 5);
    test06StrPrintVacio(type, 6);

    test07StrCloneEnStringConVariosElementos(type, 7);
    test08StrCloneDeStringVacio(type, 8);

    test09StrCmpDeDosStringsConVariosElementos(type, 9);
    test10StrCmpDeDosStringsVacios(type, 10);
    test11StrCmpConUnStrinVacio(type, 11);
}

void testArray()
{
    char type[] = "Array";

    test01ArrayNew(type, 1);

    test02ArrayAddLastConUnElemento(type, 2);
    test03ArrayAddLastConVariosElementos(type, 3);
    test04ArrayAddLastSuperandoLimite(type, 4);

    test05ArrayRemoveElementoUnico(type, 5);
    test06ArrayRemoveElementoMedio(type, 6);
    test07ArrayRemoveElementoUltimo(type, 7);
    test08ArrayRemoveFueraDeRango(type, 8);
    test09ArrayRemoveDeUnArrayConDosElementos(type, 9);
    test10ArrayRemoveDeUnArrayConUnElemento(type, 10);

    test11ArrayDeleteArrayVacio(type, 11);
    test12ArrayDeleteArrayConElementos(type, 12);

    test13ArrayGetSizeVacio(type, 13);
    test14ArrayGetSizeConUnElemento(type, 14);
    test15ArrayGetSizeConVariosElementos(type, 15);

    test16ArraySwap(type, 16);
    test17ArraySwapExcedido(type, 17);

    test18ArrayPrintDeArrayVacio(type, 18);
    test19ArrayPrintDeArrayConUnSoloElementos(type, 19);
    test20ArrayPrintDeArrayConVariosElementos(type, 20);

    test21ArrayGetDeUnaPosicionValida(type, 21);
    test22ArrayGetDeUnaPosicionInvalida(type, 22);
}

void testCard()
{

    char *type = "Card";

    test01CardNew(type, 1);

    test02CardAddStacked(type, 2);

    test03CardDelete(type, 3);
    test04CardDeleteConStacked(type, 4);

    test05CardGetNumber(type, 5);
    test06CardGetStackedVacio(type, 6);
    test07CardGetStacked(type, 7);
    test08CardGetSuitCartaConSuitNoVacio(type, 8);
    test09CardGetSuitCartaConSuitVacio(type, 9);

    test10CardCmpDeCartasIguales(type, 10);
    test11CardCmpDeCartasConSuitDistinto(type, 11);
    test12CardCmpDeCartasConMismoSuitYNumeroDistitno(type, 12);

    test13CardClone(type, 13);

    test14CardPrint(type, 14);
}

void testCatedra()
{
    int32_t num1 = 12;
    int32_t num2 = 1;
    int32_t num3 = 4;
    int32_t num4 = 6;
    int32_t num5 = 7;

    card_t *card1 = cardNew("espada", &num1);
    card_t *card2 = cardNew("basto", &num2);
    card_t *card3 = cardNew("oro", &num3);
    card_t *card4 = cardNew("oro", &num4);
    card_t *card5 = cardNew("copa", &num5);

    card_t *cards[5] = {card1, card2, card3, card4, card5};

    testCatedraArray(cards, 5);
    testCatedraList(cards, 5);

    for (int i = 0; i < 5; i++)
    {
        cardDelete(cards[i]);
    }
}

/*-----------------------------------------------------------------*/

int main(void)
{
    testlogTitle("Pruebas realizadas para implementaciones en C");
    testInt();
    testlogSeparator();
    testList();

    testlogTitle("Pruebas realizadas para implementaciones en asm");
    testString();
    testlogSeparator();
    testArray();
    testlogSeparator();
    testCard();

    testlogTitle("Pruebas realizadas para la catedra");
    testCatedra();
    testlogSeparator();
}
