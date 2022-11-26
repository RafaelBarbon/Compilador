#ifndef _CODEGENERATION_H_
#define _CODEGENERATION_H_

#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

//Transforms the integer parameter to string (Used to create the .obj file)
void *toString(int paran, char result[4]);

//Transforms the string parameter to integer (Used to get lexeme values and use it on generateAssembly)
int toInt(char *n);

//Create the instruction according to the parameters and insert it in the .obj file
void generateAssembly(char *instruction, int param1, int param2,Ui::MainWindow *ui);

//Generate the commands from the POS_FIX Expression
void generateExpressionCode(ExpressionAnalyzer *posFix, Symbol *symbol,Ui::MainWindow *ui);

#endif
