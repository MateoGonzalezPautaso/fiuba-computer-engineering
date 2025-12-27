#ifndef _LIB_HH_
#define _LIB_HH_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>

typedef enum e_type {
	TypeNone = 0,
	TypeInt = 1,
	TypeString = 2,
	TypeCard = 3
} type_t;

typedef int32_t (funcCmp_t)(void*, void*);
typedef void* (funcClone_t)(void*);
typedef void (funcDelete_t)(void*);
typedef void (funcPrint_t)(void*, FILE* pFile);
typedef void* (funcGet_t)(void*, uint8_t);
typedef void* (funcRemove_t)(void*, uint8_t);
typedef void (funcAddLast_t)(void*, void*);
typedef uint8_t (funcSize_t)(void*);
typedef void (funcSwap_t)(void*, uint8_t, uint8_t);

/** Int **/

int32_t intCmp(int32_t* a, int32_t* b);
int32_t* intClone(int32_t* a);
void intDelete(int32_t* a);
void intPrint(int32_t* a, FILE* pFile);

/* String */

int32_t strCmp(char* a, char* b);
char* strClone(char* a);
void strDelete(char* a);
void strPrint(char* a, FILE* pFile);
uint32_t strLen(char* a);

/** Array **/

typedef struct s_array {
	type_t  type;
	uint8_t size;
	uint8_t capacity;
	void** data;
} array_t;

array_t* arrayNew(type_t t, uint8_t capacity);
uint8_t  arrayGetSize(array_t* a);
void  arrayAddLast(array_t* a, void* data);
void* arrayGet(array_t* a, uint8_t i);
void* arrayRemove(array_t* a, uint8_t i);
void  arraySwap(array_t* a, uint8_t i, uint8_t j);
void  arrayDelete(array_t* a);
void  arrayPrint(array_t* a, FILE* pFile);

/* List */

typedef struct s_list {
	type_t   type;
	uint8_t  size;
	struct s_listElem* first;
	struct s_listElem* last;
} list_t;

typedef struct s_listElem {
	void* data;
	struct s_listElem* next;
	struct s_listElem* prev;
} listElem_t;

list_t* listNew(type_t t);
uint8_t  listGetSize(list_t* l);
void  listAddFirst(list_t* l, void* data);
void  listAddLast(list_t* l, void* data);
void* listGet(list_t* l, uint8_t i);
void* listRemove(list_t* l, uint8_t i);
void  listSwap(list_t* l, uint8_t i, uint8_t j);
void  listDelete(list_t* l);
list_t* listClone(list_t* l);
void  listPrint(list_t* l, FILE* pFile);

/** Card **/

typedef struct s_card {
	char*     suit;
	int32_t* number;
	list_t* stacked;
} card_t;

card_t*  cardNew(char* suit, int32_t* number);
char*    cardGetSuit(card_t* c);
int32_t* cardGetNumber(card_t* c);
list_t*  cardGetStacked(card_t* c);
int32_t cardCmp(card_t* a, card_t* b);
card_t* cardClone(card_t* c);
void cardAddStacked(card_t* c, card_t* card);
void cardDelete(card_t* c);
void cardPrint(card_t* c, FILE* pFile);

/** Game **/

typedef struct s_game {
	void*         cardDeck;
	funcGet_t*    funcGet;
	funcRemove_t* funcRemove;
	funcSize_t*   funcSize;
	funcPrint_t*  funcPrint;
	funcDelete_t* funcDelete;
} game_t;

game_t* gameNew(void* cardDeck, funcGet_t* funcGet,
	funcRemove_t* funcRemove,
	funcSize_t* funcSize,
	funcPrint_t* funcPrint,
	funcDelete_t* funcDelete);
int gamePlayStep(game_t* g);
uint8_t gameGetCardDeckSize(game_t* g);
void gameDelete(game_t* g);
void gamePrint(game_t* g, FILE* pFile);

#endif

