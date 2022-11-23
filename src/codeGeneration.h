#ifndef _CODEGENERATION_H_
#define _CODEGENERATION_H_

#include <stdio.h>
#include <stdlib.h>

void *toString(int paran, char result[4]);

int toInt(char *n);

void generateAssembly(char *instruction, int param1, int param2);

void generateExpressionCode(ExpressionAnalyzer *posFix, Symbol *symbol);

#endif