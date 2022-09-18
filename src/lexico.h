#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include "token.h"

// Biblioteca QT para interface grafica

void symbolError(char c, Token **tokenList, int lineCount);

void treatDigit(char *c, Token **tokenList, int lineCount);

void treatAttribution(char *c, Token **tokenList, int lineCount);

void treatArithmeticOperator(char *c, Token **tokenList, int lineCount);

void treatRelationalOperator(char *c, Token **tokenList, int lineCount);

void treatPunctuation(char *c, Token **tokenList, int lineCount);

void identifyReservedWord(char *c, Token **tokenList, int lineCount);

void colectToken(char *c, Token **tokenList, int lineCount);

#endif