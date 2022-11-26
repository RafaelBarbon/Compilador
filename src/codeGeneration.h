#ifndef _CODEGENERATION_H_
#define _CODEGENERATION_H_

#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

void *toString(int paran, char result[4]);

int toInt(char *n);

void generateAssembly(char *instruction, int param1, int param2,Ui::MainWindow *ui);

void generateExpressionCode(ExpressionAnalyzer *posFix, Symbol *symbol,Ui::MainWindow *ui);

#endif
