#ifndef _SINTATICO_H_
#define _SINTATICO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

//
void errorSintax(Token **token, int errorCode, char symbol);

// programa
void syntacticAnalyzer(char *c, Token **token);

//bloco
void analyzeBlock(char *c, Token **token);

//declaração de variáveis
void analyzeEtVariables(char *c, Token **token);

//declaração de variáveis
void analyzeVariables(char *c, Token **token);

//tipo
void analyzeType(char *c, Token **token);

//comandos
void analyzeCommands(char *c, Token **token);

//comandos
void analyzeSimpleCommand(char *c, Token **token);

//atribuição_chprocedimento
void analyzeAttributionProcedureCall(char *c, Token **token);

// Usado na Analisa_leia
//void pesquisar_em_toda_a_tabela();

//comando leitura
void analyzeRead(char *c, Token **token);

// comando escrita
void analyzeWrite(char *c, Token **token);

//comando repetição
void analyzeWhile(char *c, Token **token);

// comando condicional
void analyzeConditional(char *c, Token **token);

// etapa de declaração de sub-rotinas
void analyzeSubroutines(char *c, Token **token/*, int rotulo*/);

//declaração de procedimento
void analyzeProcedureDeclaration(char *c, Token **token);

//declaração de função
void analyzeFunctionDeclaration(char *c, Token **token);

//expressão
void analyzeExpression(char *c, Token **token);

//expressão simples
void analyzeSimpleExpression(char *c, Token **token);

//termo
void analyzeTerm(char *c, Token **token);

//fator
void analyzeFactor(char *c, Token **token);

//usado no Analisa_expressao
bool verifyRelationalSymbol(Token *token);

void procedureCall(char *c, Token **token, char *nameProcedure);

void analyzeAttribution(char *c, Token **token);

void analyzeFunctionCall(char *c, Token **token);

#endif