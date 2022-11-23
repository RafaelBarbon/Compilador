#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "verifyChar.h"

// Enum for identify the symbol type declared
typedef enum SymbolType{
    Var, // 0
    Func, // 1
    FuncInteira, // 2
    FuncBooleana, // 3
    VarInteira, // 4
    VarBooleana, // 5
    Procedimento, // 6
    Programa // 7
}SymbolType;

// Struct for identify a symbol
typedef struct symbol {
    char lexeme[maxIdentifierLength];
    bool scope;
    SymbolType type;
    int memory;
    struct symbol *next;
}Symbol;

//#################################################################

typedef enum LexemeType{
    VarInt, // 0
    VarBool, // 1
    FuncInt, // 2
    FuncBool, // 3
    AbreP, // 4
    FechaP, // 5
    UnarioN, // 6
    UnarioP, // 7
    OpMultDiv, // 8
    OpMaisMenos, // 9
    Rel, // 10
    Nao, // 11
    E, // 12
    OU, // 13
    Inteiro, // 14 
    Booleano // 15
}LexemeType;

// Used on expression analyzer type
typedef struct expressionAnalyzer {
    char lexeme[maxIdentifierLength];
    LexemeType type;
    struct expressionAnalyzer *next;
}ExpressionAnalyzer;

// Simple stack functions (POS_FIX conversion)
typedef struct simpleStack {
    ExpressionAnalyzer *c;
    struct simpleStack *next;
}simpleStack;

//#################################################################

// Insert a new symbol into stack
void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory);

// Insert the type of symbol of variables
void putType(Symbol **stack, SymbolType type);

// Insert the type of symbol of function
void putTypeFunc(Symbol **stack, SymbolType type);

// Print all symbols in stack
void printStack(Symbol *stack);

// Free memory
void freeSymbol(Symbol **l);

// Convert enum to string
char* symbolTypeToString(SymbolType type);

// Verify variable duplicity (need to check if duplicity on global variables are allowed)
bool searchDuplicity(Symbol *stack, char *lexeme);

// Returns the address of the declared procedure
int searchProcAddr(Symbol *symbol, char *lexeme);

// Returns the address of the declared function or variable
int searchVarFuncAddress(Symbol *symbol, char *lexeme);

// Returns the type of the specified function or variable name
SymbolType searchVarFuncType(Symbol *l, char *lexeme);

// Verify if the procedure or function have been already declared
bool verifyProcedureFunctionDuplicity(Symbol *symbol, char *lexeme);

// Verify if the procedure was already declared (check if search duplicity can overwrite this)
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme);

// Verify if the function was already declared (check if search duplicity can overwrite this)
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme);

// verify if the var/func was declared
bool verifyVarFuncDeclaration(Symbol *stack, char *lexeme);

// Verify if the int var was declared
bool verifyVarDeclaration(Symbol *stack, char *lexeme, int *memory);

// Unstack until the next scope (local variable region)
int unStack(Symbol **symbol);

//#################################################################

// Push stack (Used on expression analyzer) 
void push(simpleStack **stack, ExpressionAnalyzer *c);

// Pop stack (Used on expression analyzer) 
ExpressionAnalyzer pop(simpleStack **stack);

// Print the simple stack used to analyze the expression
void printSimpleStack(simpleStack *s);

// Free the simple stack memory allocated used to analyze the expression
void freeSimpleStack(simpleStack **st);

// Free the expression memory allocated used on semantic to analyze expressions
void freeExpression(ExpressionAnalyzer **l);

// Print the expression (Used on DEBUG mode to POS_FIX conversion)
void printExpression(ExpressionAnalyzer *ex, char *ty, bool type);

//Make a copy of a expression (Used to make a copy from POS_FIX expression to analyze the expression type (Semantic Analayzer))
void copyExpression(ExpressionAnalyzer **dest, ExpressionAnalyzer *src);

// Get the variable type (integer or boolean)
LexemeType getVarType(Symbol *l, char *lexeme);

// Check if the lexeme informed is a function and returns it's type
LexemeType isFunction(Symbol *l, char *lexeme);

// Used on syntatic to insert the found expression part
void insertInFix(ExpressionAnalyzer **list, char lexeme[maxIdentifierLength], LexemeType type);

// Used on semantic to insert the IN_FIX convertion of the expression
void insertPosFix(ExpressionAnalyzer **PosFix, ExpressionAnalyzer *Expression);

// Find the next operator with more precedence to insert correctly in the POS_FIX expression
void searchStackMorePrecedence(simpleStack **stack, ExpressionAnalyzer *op, ExpressionAnalyzer **PosFix);

// Used to identify Unary operators in the IN_FIX expression and change their type to 'UnarioP' or 'UnarioN' (Used before POS_FIX conversion)
void verifyUnaryOperators(ExpressionAnalyzer **inFix);

// Convert the IN_FIX expression to POS_FIX expression 
void convertPosFix(ExpressionAnalyzer **inFixIn, ExpressionAnalyzer **PosFix);

#endif