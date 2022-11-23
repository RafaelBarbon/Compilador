#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "verifyChar.h"

void insertToken(Token **l, char *lexeme, char *symbol) {

    if(debug)
        printf("\nDEBUG - Token - Inserindo lexema: { %s } - %s\n", lexeme, symbol);

    Token *novo = (Token *)malloc(sizeof(Token));

    strcpy(novo->lexeme,lexeme);
    strcpy(novo->symbol,symbol);
    novo->next = NULL;

    if(*l != NULL) {
        Token *aux = (*l);
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = novo;
    }
    else
        (*l) = novo;
}

void freeToken(Token **l) {
    Token *aux = (*l), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}

void printToken(Token *l){
    while(l != NULL){
        printf("\nLexeme: %-30s \t\t Symbol: %s\n", l->lexeme, l->symbol);
        l = l->next;
    }
}
