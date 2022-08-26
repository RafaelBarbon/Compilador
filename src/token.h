#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct for identify a token
typedef struct Token{
    char lexema[30];
    char symbol[20];
    struct Token *next;
}Token;

// Insert a new Token in the end of the list
void insertToken(Token **l);

// Free memory list
void freeToken(Token **l);