#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Biblioteca QT para interface grafica

void symbolError(char c, Token **tokenList, int lineCount, Ui::MainWindow *ui);

void treatDigit(char *c, Token **tokenList, int lineCount, Ui::MainWindow *ui);

void treatAttribution(char *c, Token **tokenList, int lineCount);

void treatArithmeticOperator(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

void treatRelationalOperator(char *c, Token **tokenList, int lineCount);

void treatPunctuation(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

void identifyReservedWord(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

void colectToken(char *c, Token **tokenList, int lineCount,Ui::MainWindow *ui);

void getToken(char *c, Token **tokenList,Ui::MainWindow *ui);

bool checkComment(char *c,Ui::MainWindow *ui);

bool checkSpaces(char *c);

#endif
