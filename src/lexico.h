#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Biblioteca QT para interface grafica

// Redirects to print error and treat Token structure
void symbolError(char c, Token **tokenList, int lineCount, Ui::MainWindow *ui);

// Verify and treat numbers in expressions
void treatDigit(char *c, Token **tokenList, int lineCount, Ui::MainWindow *ui);

// Verify and treat attribution sintax
void treatAttribution(char *c, Token **tokenList, int lineCount);

// Verify and treat arithmetic operators in expressions
void treatArithmeticOperator(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

// Verify and treat relational operators in expressions
void treatRelationalOperator(char *c, Token **tokenList, int lineCount);

// Verify and treat any punctuation or symbol
void treatPunctuation(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

// Identify if the token is an reserved word from the programming language
void identifyReservedWord(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

// Redirect the token got in source file to be treated specifically by other functions
void colectToken(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

// Collect the next valid token in source file
void getToken(char *c, Token **tokenList,Ui::MainWindow *ui);

// Verify and ignore any comment structure
bool checkComment(char *c,Ui::MainWindow *ui);

// verify and ignore any spaces in source file
bool checkSpaces(char *c);

#endif
