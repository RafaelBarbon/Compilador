#ifndef _VERIFYCHAR_H_
#define _VERIFYCHAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isSpaceCode(char c, int *lineCount);

bool isNotEndOfFile(char c);

bool isDigit(char c);

bool isLetter(char c);

bool isAritmeticOperator(char c);

bool isRelationalOperator(char c);

bool isPonctuation(char c);

bool isEqualString(char *str1, char *str2);

bool isIdentifier(char c);

#endif