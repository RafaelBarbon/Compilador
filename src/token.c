#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

void insertToken(Token **l, char *lexeme, char *symbol) {
    Token *new = malloc(sizeof(Token));

    strcpy(new->lexeme,lexeme);
    strcpy(new->symbol,symbol);
    new->next = NULL;

    if(*l != NULL) {
        while((*l)->next != NULL)
            (*l) = (*l)->next;
        (*l)->next = new;
    }
    else
        (*l) = new;
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