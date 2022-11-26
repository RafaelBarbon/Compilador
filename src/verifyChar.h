#ifndef _VERIFYCHAR_H_
#define _VERIFYCHAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define maxIdentifierLength 30


// **************************************************

// Global variables and functions

extern bool debug;

extern bool error;

extern bool flagUpdate;

extern bool insertArray;

extern int lineCount;

extern int label;

extern int address;

extern FILE *sourceFile, *outputCode;

extern void updateCursor(char *c);

// **************************************************

// Check for space characters
bool isSpaceCode(char c);

// Check if the cursor have been reached the end of file
bool isNotEndOfFile(char c);

// Check if the character is a digit
bool isDigit(char c);

// Check if the character is a letter
bool isLetter(char c);

// Check if the character is an arithmetic operator
bool isArithmeticOperator(char c);

// Check if the character is a relational operator
bool isRelationalOperator(char c);

// Check if the character is puntuation
bool isPonctuation(char c);

// Check if the strings are the same
bool isEqualString(char *str1, char *str2);

// Check if the character is a valid identifier
bool isIdentifier(char c);

#endif