#ifndef _VERIFYCHAR_H_
#define _VERIFYCHAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern bool debug;

extern bool error;

extern bool flagUpdate;

extern bool insertArray;

extern int lineCount;

extern FILE *sourceFile;

extern void updateCursor(char *c);

bool isSpaceCode(char c);

bool isNotEndOfFile(char c);

bool isDigit(char c);

bool isLetter(char c);

bool isAritmeticOperator(char c);

bool isRelationalOperator(char c);

bool isPonctuation(char c);

bool isEqualString(char *str1, char *str2);

bool isIdentifier(char c);

#endif