#ifndef _SINTATICO_H_
#define _SINTATICO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

//
void errorSintax(Token **token, int errorCode, char symbol);

// Get a new token
void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix);

// programa
void syntacticAnalyzer(char *c, Token **token, Symbol **symbol);

//bloco
void analyzeBlock(char *c, Token **token, Symbol **symbol);

//declaração de variáveis
void analyzeEtVariables(char *c, Token **token, Symbol **symbol);

//declaração de variáveis
void analyzeVariables(char *c, Token **token, Symbol **symbol);

//tipo
void analyzeType(char *c, Token **token, Symbol **symbol);

//comandos
void analyzeCommands(char *c, Token **token, Symbol **symbol);

//comandos
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol);

//atribuição_chprocedimento
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol);

//comando leitura
void analyzeRead(char *c, Token **token, Symbol **symbol);

// comando escrita
void analyzeWrite(char *c, Token **token, Symbol **Symbol);

//comando repetição
void analyzeWhile(char *c, Token **token, Symbol **symbol);

// comando condicional
void analyzeConditional(char *c, Token **token, Symbol **symbol);

// etapa de declaração de sub-rotinas
void analyzeSubroutines(char *c, Token **token, Symbol **symbol/*, int rotulo*/);

//declaração de procedimento
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol);

//declaração de função
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol);

//expressão
void analyzeExpression(char *c, Token **token, Symbol *symbol);

//expressão simples
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol);

//termo
void analyzeTerm(char *c, Token **token, Symbol *symbol);

//fator
void analyzeFactor(char *c, Token **token, Symbol *symbol);

//usado no Analisa_expressao
bool verifyRelationalSymbol(Token *token);

void procedureCall(char *c, Token **token, char *nameProcedure, Symbol **symbol);

void analyzeAttribution(char *c, Token **token, Symbol *symbol);

void analyzeFunctionCall(char *c, Token **token);

#endif