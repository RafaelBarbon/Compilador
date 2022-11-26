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

// Treat errors, files and structures
void errorSintax(Token **token, int errorCode, char symbol,Ui::MainWindow *ui);

// Verify if the symbol is relational
bool verifyRelationalSymbol(Token *token);

// Calls lexic to get a new token in source file
void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix,Ui::MainWindow *ui);

// Analyze if the expression matches with the expected type
void analyzeExpressionType(ExpressionAnalyzer **expression, LexemeType expectedType);

// Responsible for convert the expression to POS_FIX, verify if the expression is correct and generate the assembly code for the expression
void semanticAnalyzer(ExpressionAnalyzer **inFix, LexemeType type, Symbol *symbol,Ui::MainWindow *ui);

// Starts the compilation of the code
void syntacticAnalyzer(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze a block of program
void analyzeBlock(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze the declarion of variables
void analyzeEtVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

// Also used to analyze the declarion of variables
void analyzeVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

// Analyze the type of the token and put it on the symbol table
void analyzeType(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

// Analyze the program commands
void analyzeCommands(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Also used to analyze the program commands
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze an attribution or a procedure call
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze attributions
void analyzeAttribution(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix, char *name,Ui::MainWindow *ui);

// Analyze a procedure call
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze a function call
void analyzeFunctionCall(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze the read command
void analyzeRead(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui);

// Analyze the write command
void analyzeWrite(char *c, Token **token, Symbol **Symbol,Ui::MainWindow *ui);

// Analyze the while command
void analyzeWhile(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) ;

// Analyze the conditional command
void analyzeConditional(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze declaration of subroutines=
void analyzeSubroutines(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Analyze procedure declarations
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Function declaration
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix);

// Expression - Verify expression and possible relational operator
void analyzeExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix);

// Simple expression - Analyze the lower precedence of expressions
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Term - Analyze the higher precedence of the operations
void analyzeTerm(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

// Factor - used to extract each token of an expression
void analyzeFactor(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui);

#endif

