#ifndef _SINTATICO_H_
#define _SINTATICO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include <QApplication>
#include <string.h>
#include "symbol.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

void semanticAnalyzer(ExpressionAnalyzer **inFix, LexemeType type, Symbol *symbol,Ui::MainWindow *ui);

//
void errorSintax(Token **token, int errorCode, char symbol,Ui::MainWindow *ui);

// Get a new token
void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix);

// programa
void syntacticAnalyzer(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//bloco
void analyzeBlock(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//declaração de variáveis
void analyzeEtVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

//declaração de variáveis
void analyzeVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

//tipo
void analyzeType(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

//comandos
void analyzeCommands(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//comandos
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//atribuição_chprocedimento
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//comando leitura
void analyzeRead(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

// comando escrita
void analyzeWrite(char *c, Token **token, Symbol **Symbol,Ui::MainWindow *ui);

//comando repetição
void analyzeWhile(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) ;

// comando condicional
void analyzeConditional(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// etapa de declaração de sub-rotinas
void analyzeSubroutines(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//declaração de procedimento
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//declaração de função
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//expressão
void analyzeExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//expressão simples
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//termo
void analyzeTerm(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//fator
void analyzeFactor(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

//usado no Analisa_expressao
bool verifyRelationalSymbol(Token *token);

void procedureCall(char *c, Token **token, char *nameProcedure, Symbol **symbol,Ui::MainWindow *ui);

void analyzeAttribution(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix, char *name,Ui::MainWindow *ui);

void analyzeFunctionCall(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

#endif

