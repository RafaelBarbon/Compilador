#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <stdio.h>
#include <stdlib.h>
#include "token.h"


// Redirects to print error and treat Token structure
void symbolError(char c, Token **tokenList);

// Verify and treat numbers in expressions
void treatDigit(char *c, Token **tokenList);

// Verify and treat attribution sintax
void treatAttribution(char *c, Token **tokenList);

// Verify and treat arithmetic operators in expressions
void treatArithmeticOperator(char *c, Token **tokenList);

// Verify and treat relational operators in expressions
void treatRelationalOperator(char *c, Token **tokenList);

// Verify and treat any punctuation or symbol
void treatPunctuation(char *c, Token **tokenList);

// Identify if the token is an reserved word from the programming language
void identifyReservedWord(char *c, Token **tokenList);

// Redirect the token got in source file to be treated specifically by other functions
void colectToken(char *c, Token **tokenList);

// Collect the next valid token in source file
void getToken(char *c, Token **tokenList);

// Verify and ignore any comment structure
bool checkComment(char *c);

// verify and ignore any spaces in source file
bool checkSpaces(char *c);

#endif