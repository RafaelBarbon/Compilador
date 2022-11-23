#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "verifyChar.h"

// Struct for identify a token
typedef struct Token{
    char lexeme[maxIdentifierLength];
    char symbol[20];
    struct Token *next;
}Token;


// Insert a new Token in the end of the list
void insertToken(Token **l, char *lexeme, char *symbol);

// Free memory list
void freeToken(Token **l);

// Print all token list
void printToken(Token *l);

#endif