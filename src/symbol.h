#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Enum for identify the symbol type declared
typedef enum SymbolType{
    Var,
    Func,
    FuncInteira,
    FuncBooleana,
    VarInteira,
    VarBooleana,
    Procedimento,
    Programa
}SymbolType;

// Struct for identify a symbol
typedef struct symbol {
    char lexeme[30];
    bool scope;
    SymbolType type;
    int memory;
    struct symbol *next;
}Symbol;


//#################################################################
//Simple stack functions (Posfix conversion)
typedef struct simpleStack {
    char *c;
    struct simpleStack *next;
}simpleStack; 

void push(simpleStack **stack, char c);

char pop(simpleStack **stack, char c);

char* convertPosFix(char inFix[], int size);

char unstackOperator();

char searchStackMorePrecedence();

//#################################################################


// Insert a new symbol into stack
void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory);

// Insert the type of symbol
void putType(Symbol **stack, SymbolType type);

// Print all symbols in stack
void printStack(Symbol *stack);

// Free memory
void freeSymbol(Symbol **l);

// Convert enum to string
char* symbolTypeToString(SymbolType type);

// finds variable duplication
bool searchDuplicity(Symbol *stack, char *lexeme);

// Verify if the lexeme have been declared as function
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme);

// Verify if the lexeme have been declared as procedure
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme);

// finds variable para for function already used
bool verifyVarFuncDeclaration(Symbol *stack, char *lexeme);

// finds variable para for function already used
bool verifyIntVarFuncDeclaration(Symbol *stack, char *lexeme);

// encontra variavel declarada já utilizada
bool verifyVarDeclaration(Symbol *stack, char *lexeme);

// Unstack until the next scope (local variable region)
void unStack(Symbol **symbol);

#endif