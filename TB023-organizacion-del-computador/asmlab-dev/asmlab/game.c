#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"

void fillCardDeck(void* cardDeck, funcAddLast_t* funcAddLast) {
    card_t* card;
    char* B = "basto";
    char* E = "espada";
    char* C = "copa";
    char* O = "oro";
    for(int32_t i=1; i<=7; i++) {
        card = cardNew(B, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(E, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(C, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(O, &i); funcAddLast(cardDeck, card); cardDelete(card);
    }
    for(int32_t i=10; i<=12; i++) {
        card = cardNew(B, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(E, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(C, &i); funcAddLast(cardDeck, card); cardDelete(card);
        card = cardNew(O, &i); funcAddLast(cardDeck, card); cardDelete(card);
    }
}

void shuffleCardDeck(void* cardDeck, funcSwap_t* funcSwap, int seed) {
    srand(seed);
    for(int k=0; k<100; k++) {
            uint8_t i = (uint8_t)(rand()%40);
            uint8_t j = (uint8_t)(rand()%40);
            funcSwap(cardDeck, i, j);
    }
}

game_t* buildGameWithArray(int seed) {
    void* cardDeck = arrayNew(TypeCard, 40);
    fillCardDeck(cardDeck, (funcAddLast_t*)&arrayAddLast);
    shuffleCardDeck(cardDeck, (funcSwap_t*)&arraySwap, seed);
	game_t* game = gameNew(cardDeck, (funcGet_t*)&arrayGet,
                                     (funcRemove_t*)&arrayRemove,
                                     (funcSize_t*)&arrayGetSize,
                                     (funcPrint_t*)&arrayPrint,
                                     (funcDelete_t*)&arrayDelete);
    return game;
}

game_t* buildGameWithList(int seed) {
    void* cardDeck = listNew(TypeCard);
    fillCardDeck(cardDeck, (funcAddLast_t*)&listAddLast);
    shuffleCardDeck(cardDeck, (funcSwap_t*)&listSwap, seed);
	game_t* game = gameNew(cardDeck, (funcGet_t*)&listGet,
                                     (funcRemove_t*)&listRemove,
                                     (funcSize_t*)&listGetSize,
                                     (funcPrint_t*)&listPrint,
                                     (funcDelete_t*)&listDelete);
    return game;
}

void playGame(game_t* game, FILE* pFile) {
    gamePrint(game, pFile); fprintf(pFile, "\n");
    fprintf(pFile, "-- %i -- START\n",gameGetCardDeckSize(game));
    int go = 1;
    int count = 0;
    while (go == 1) {
        fprintf(pFile, "%i -> ", count);
        gamePrint(game, pFile); fprintf(pFile, "\n");
        go = gamePlayStep(game);
        count = count + 1;
    }
    gamePrint(game, pFile); fprintf(pFile, "\n");
    fprintf(pFile, "-- %i -- END \n",gameGetCardDeckSize(game));
}

#ifndef TESTING
int main (int argc, char **argv){

    if (argc < 2) {
        printf("Usage: ./game <seed>\n");
        printf("              <seed> = integer number\n");
        return 0;
    }

    int seed = atoi(argv[1]);

    FILE *pfile;
    game_t* game;

    pfile = fopen("gameResultArray.txt","w");
    game = buildGameWithArray(seed);
    playGame(game, pfile);
    gameDelete(game);
    fclose(pfile);

    pfile = fopen("gameResultList.txt","w");
    game = buildGameWithList(seed);
    playGame(game, pfile);
    gameDelete(game);
    fclose(pfile);

    return 0;
}
#endif

