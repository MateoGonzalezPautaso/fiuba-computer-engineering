#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"

void test_strClone()
{
    char *string = "Hola mundo!";
    char *string_copiado = strClone(string);

    if(strcmp(string,string_copiado) == 0){
        printf("strClone copia bien el string\n");
    }
    else{
        printf("strClone no esta copiando bien el string\n");
    }
    free(string_copiado);
}

void test_strPrint()
{
    char *string = "Hola mundo!\n";
    printf("La funcion strPrint deberia mostrar 'Hola Mundo!' por consola y muestra ");
    strPrint(string, stdout);
}

void test_strLen()
{
    char *string = "Hola mundo!";
    uint32_t len = strLen(string);
    printf("La longitud del string es 11 y strLen devuelve %d\n", len);
}

void test_strDelete()
{
    char *str = malloc(5);
    strDelete(str);
}

void test_strCmp(){
    char *string_a = "Hola mundo!";
    char *string_b = malloc(12);
    strcpy(string_b,string_a);
    char *string_c = "Cabeza";
    
    int32_t res_eq1 = strCmp(string_a, string_a);
    int32_t res_eq2 = strCmp(string_a, string_b);
    int32_t res_eq3 = strCmp(string_b, string_a);
    int32_t res_g = strCmp(string_c, string_a);
    int32_t res_l = strCmp(string_a, string_c);
    printf("Pruebas strCmp\n");
    printf("Iguales: %d, %d, %d\n", res_eq1, res_eq2, res_eq3);
    printf("Menor: %d\n", res_g);
    printf("Mayor: %d\n", res_l);
    free(string_b);
}

void test_arrayGetSize()
{
    type_t _type = TypeInt;
    uint8_t _size = 4;
    uint8_t _capacity = 8;
    void* data;
    array_t array = {.type = _type,.size = _size,.capacity = _capacity, .data = &data};
    uint8_t tamaño = arrayGetSize(&array);
    printf("El tamaño del array es 4 y arrayGetSize() devuelve %d\n", tamaño);
}

void test_arrayNew_arrayDelete()
{
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type,_capacity);
    if (array) {
        printf("Se asigno memoria exitosamente para array_t\n");
    } else {
        printf("No se asigno memoria para array_t\n");
    }
    arrayDelete(array);
}

void test_arrayAddLast(){
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type, _capacity);
    int dato = 2;
    arrayAddLast(array, &dato);
    if(*((int *)(array->data[0])) == dato) {
        printf("arraAddLast funciona bien\n");
    } else {
        printf("arraAddLast funciona MAL\n");
    }
    printf("%d\n", arrayGetSize(array));
    arrayDelete(array);
}


void test_arrayGet(){
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type, _capacity);
    int dato1 = 2;
    int dato2 = 6;
    arrayAddLast(array, &dato1);
    arrayAddLast(array, &dato2);
    
    void *encontrado1 = arrayGet(array, 0);
    void *encontrado2 = arrayGet(array, 1);
    void *encontrado3 = arrayGet(array, 2);

    if(*(int*)encontrado1 == dato1 && *(int*)encontrado2 == dato2 && !*(int*)encontrado1 == 0){
        printf("arrayGet funciona bien!\n");
    }else{
        printf("arrayGet funciona MAL\n");
    }
    arrayDelete(array);
}

void test_arraySwap(){
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type, _capacity);
    int dato1 = 2;
    int dato2 = 6;
    int dato3 = 13;

    arrayAddLast(array, &dato1);
    arrayAddLast(array, &dato2);
    arrayAddLast(array, &dato3);

    arraySwap(array, 10, 0); // Hay uno fuera de rango, no hace swap
    arraySwap(array, 0, 10); // Hay uno fuera de rango, no hace swap
    arraySwap(array, 1, 1); // Son las mismas posiciones, no hace swap

    arraySwap(array, 0, 1); // Hace un swap
    
    void *encontrado1 = arrayGet(array, 0);
    void *encontrado2 = arrayGet(array, 1);
    void *encontrado3 = arrayGet(array, 2);

    if(*(int*)encontrado1 == dato2 && *(int*)encontrado2 == dato1 && *(int*)encontrado3 == dato3){
        printf("arraySwap cambia bien los elementos\n");
    }else{
        printf("arraySwap no cambia los elementos\n");
    }
    arrayDelete(array);
}

void test_arrayRemove(){
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type, _capacity);
    int dato1 = 2;
    int dato2 = 6;
    int dato3 = 13;

    arrayAddLast(array, &dato1);
    arrayAddLast(array, &dato2);
    arrayAddLast(array, &dato3);

    int *borrado = arrayRemove(array, 0);
    int *encontrado1 = arrayGet(array,0);
    int *encontrado2 = arrayGet(array,1);
    uint8_t nuevo_tamaño = arrayGetSize(array);

    int *borrado_fuera_de_rango = arrayRemove(array,2); // Elimina un elemento fuera de rango, el array queda igual
    
    if(*borrado == dato1 && nuevo_tamaño == 2 && *encontrado1 == dato2 && *encontrado2 == dato3){
        printf("arrayRemove remueve bien el elemento | ");
        free(borrado);
        if(!borrado_fuera_de_rango) printf("arrayRemove fuera de rango funciona bien\n");
    } else{
        printf("arrayRemove :(\n");
    }

    arrayDelete(array);
}

void test_arrayPrint(){
    type_t _type = TypeInt;
    uint8_t _capacity = 8;
    array_t *array = arrayNew(_type, _capacity);
    int dato1 = 2;
    int dato2 = 6;
    int dato3 = 13;

    arrayAddLast(array, &dato1);
    arrayAddLast(array, &dato2);
    arrayAddLast(array, &dato3);

    FILE *pfile = stdout;
    printf("arrayPrint imprime : ");
    arrayPrint(array,pfile);
    printf(" | Debe imprimir : [2,6,13]\n");
    arrayDelete(array);
}

void test_cardNew_cardDelete()
{
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);
    if (card) {
        printf("Se asigno memoria exitosamente para card_t\n");
    } else {
        printf("No se asigno memoria para card_t\n");
    }
    
    char *suit_guardado = card->suit;
    int32_t *number_guardado = card->number;
    list_t *lista_guardada = card->stacked;

    int32_t res = strCmp(suit_guardado, suit);
    
    if(res == 0) printf("Se asignó correctamente el suit\n");
    if(*number_guardado == number) printf("Se asignó correctamente el number\n");
    if(lista_guardada && lista_guardada->type == TypeCard) printf("Se asigno una lista valida a la carta\n");
    cardDelete(card);
}

void test_cardGetSuit(){
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);
    char *card_suit = cardGetSuit(card);
    printf("Prueba de cardGetSuit %s == %s\n", card_suit, suit);
    cardDelete(card);
}

void test_cardGetNumber(){
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);
    int32_t *card_number = cardGetNumber(card);
    printf("Prueba de cardGetSuit %d == %d\n", *card_number, number);
    cardDelete(card);
}

void test_cardGetStacked(){
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);
    list_t *card_stacked = cardGetStacked(card);
    listPrint(card_stacked, stdout);
    printf(" == ");
    listPrint(card->stacked, stdout);
    printf("\n");
    cardDelete(card);
}

void test_cardPrint(){
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);
    cardPrint(card,stdout);
    cardDelete(card);
    printf("\n");
}


void test_cardCmp()
{
    char *suit_1 = "Espada";
    char *suit_2 = "Oro";
    int32_t number_1 = 7;
    int32_t number_2 = 2;
    card_t *card_1 = cardNew(suit_1, &number_1);    // Espada 7
    card_t *card_2 = cardNew(suit_1, &number_2);    // Espada 2
    card_t *card_3 = cardNew(suit_2, &number_1);    // Oro 7
    card_t *card_4 = cardNew(suit_2, &number_2);    // Oro 2 
    card_t *card_5 = cardNew(suit_1, &number_1);    // Espada 7

    int32_t res1 = cardCmp(card_1,card_5); // a = b -> 0
    int32_t res2 = cardCmp(card_1,card_2); //a > b -> -1
    int32_t res3 = cardCmp(card_1,card_3); // a < b -> 1
    int32_t res4 = cardCmp(card_1,card_4); // a < b -> 1
    int32_t res5 = cardCmp(card_2,card_1); // a < b -> 1
    int32_t res6 = cardCmp(card_3,card_2); // a > b -> -1

    printf("0 == %d | -1 == %d | 1 == %d | 1 == %d | 1 == %d | -1 == %d \n", res1, res2, res3, res4, res5, res6);
    cardDelete(card_1);
    cardDelete(card_2);
    cardDelete(card_3);
    cardDelete(card_4);
    cardDelete(card_5);
}

void test_cardClone()
{
    char *suit = "Espada";
    int32_t number = 7;
    card_t *card = cardNew(suit, &number);

    card_t *copia = cardClone(card);

    if(cardCmp(card, copia) == 0) printf("cardClone funciona correctamente :)\n"); 

    cardDelete(card);
    cardDelete(copia);
}

void test_cardAddStacked()
{
    char *suit_1 = "Espada";
    char *suit_2 = "Oro";
    int32_t number_1 = 7;
    int32_t number_2 = 2;
    card_t *card_1 = cardNew(suit_1, &number_1);    // Espada 7
    card_t *card_2 = cardNew(suit_1, &number_2);    // Espada 2
    card_t *card_3 = cardNew(suit_2, &number_1);    // Oro 7

    cardAddStacked(card_1,card_2);
    cardAddStacked(card_1,card_3);

    cardPrint(card_1, stdout);
    printf("\n");
    
    cardDelete(card_1);
    cardDelete(card_2);
    cardDelete(card_3);
}

void caso_array()
{
    array_t *mazo = arrayNew(TypeCard,5);  // Crea un mazo para 5 cartas

    // Crea 5 cartas diferentes
    char *suit_1 = "Espada";
    char *suit_2 = "Oro";
    char *suit_3 = "Copa";
    int32_t number_1 = 7;
    int32_t number_2 = 2;
    int32_t number_3 = 5;
    card_t *card_1 = cardNew(suit_1, &number_1);    // Espada 7
    card_t *card_2 = cardNew(suit_1, &number_2);    // Espada 2
    card_t *card_3 = cardNew(suit_2, &number_1);    // Oro 7
    card_t *card_4 = cardNew(suit_2, &number_2);    // Oro 2 
    card_t *card_5 = cardNew(suit_3, &number_3);    // Copa 5

    card_t *cartas[] = {card_1,card_2,card_3,card_4,card_5};
    for(int i=0; i<5; i++){
        arrayAddLast(mazo,cartas[i]);   // Agrega las 5 cartas al mazo
    }

    arrayPrint(mazo,stdout);    // Imprimo el mazo
    printf("\n");
    cardAddStacked(arrayGet(mazo,2),arrayGet(mazo,4));  // Apila dos cartas cualquiera del mazo
    arrayPrint(mazo,stdout);    // Imprime nuevamente el mazo
    printf("\n");

    arrayDelete(mazo);  // Borra el mazo
    for(int i=0; i<5; i++){
        cardDelete(cartas[i]);   // Borra las cartas
    }
}

void caso_lista()
{
    list_t *mazo = listNew(TypeCard);  // Crea un mazo para 5 cartas

    // Crea 5 cartas diferentes
    char *suit_1 = "Espada";
    char *suit_2 = "Oro";
    char *suit_3 = "Copa";
    int32_t number_1 = 7;
    int32_t number_2 = 2;
    int32_t number_3 = 5;
    card_t *card_1 = cardNew(suit_1, &number_1);    // Espada 7
    card_t *card_2 = cardNew(suit_1, &number_2);    // Espada 2
    card_t *card_3 = cardNew(suit_2, &number_1);    // Oro 7
    card_t *card_4 = cardNew(suit_2, &number_2);    // Oro 2 
    card_t *card_5 = cardNew(suit_3, &number_3);    // Copa 5

    card_t *cartas[] = {card_1,card_2,card_3,card_4,card_5};
    for(int i=0; i<5; i++){
        listAddLast(mazo,cartas[i]);   // Agrega las 5 cartas al mazo
    }

    listPrint(mazo,stdout);    // Imprimo el mazo
    printf("\n");
    cardAddStacked(listGet(mazo,2),listGet(mazo,4));  // Apila dos cartas cualquiera del mazo
    listPrint(mazo,stdout);    // Imprime nuevamente el mazo
    printf("\n");

    listDelete(mazo);  // Borra el mazo
    for(int i=0; i<5; i++){
        cardDelete(cartas[i]);   // Borra las cartas
    }
}

int main (void){
    test_strClone();
    test_strPrint();
    test_strLen();
    test_strCmp();
    test_strDelete();
    test_arrayGetSize();
    test_arrayNew_arrayDelete();
    test_arrayAddLast();
    test_arrayGet();
    test_arraySwap();
    test_arrayRemove();
    test_arrayPrint();
    test_cardNew_cardDelete();
    test_cardGetSuit();
    test_cardGetNumber();
    test_cardGetStacked();
    test_cardPrint();
    test_cardCmp();
    test_cardClone();
    test_cardAddStacked();

    printf("\n=== CASO ARRAY ===\n");
    caso_array();

    printf("\n=== CASO LISTA ===\n");
    caso_lista();
    return 0;
}


