#ifndef _SINTATICO_H_
#define _SINTATICO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

void semanticAnalyzer(ExpressionAnalyzer **inFix, LexemeType type);

//
void errorSintax(Token **token, int errorCode, char symbol);

// Get a new token
void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix);

// programa
void syntacticAnalyzer(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//bloco
void analyzeBlock(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//declaração de variáveis
void analyzeEtVariables(char *c, Token **token, Symbol **symbol);

//declaração de variáveis
void analyzeVariables(char *c, Token **token, Symbol **symbol);

//tipo
void analyzeType(char *c, Token **token, Symbol **symbol);

//comandos
void analyzeCommands(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//comandos
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//atribuição_chprocedimento
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//comando leitura
void analyzeRead(char *c, Token **token, Symbol **symbol);

// comando escrita
void analyzeWrite(char *c, Token **token, Symbol **Symbol);

//comando repetição
void analyzeWhile(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix/*, int rotulo*/) ;

// comando condicional
void analyzeConditional(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

// etapa de declaração de sub-rotinas
void analyzeSubroutines(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix/*, int rotulo*/);

//declaração de procedimento
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//declaração de função
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

//expressão
void analyzeExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

//expressão simples
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

//termo
void analyzeTerm(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

//fator
void analyzeFactor(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

//usado no Analisa_expressao
bool verifyRelationalSymbol(Token *token);

void procedureCall(char *c, Token **token, char *nameProcedure, Symbol **symbol);

void analyzeAttribution(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix, char *name);

void analyzeFunctionCall(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

#endif

