#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Struct for identify a symbol
typedef struct symbol{
    char lexeme[30];
    bool scope;
    enum SymbolType{Var, Func, FuncInteira, FuncBooleana, VarInteira, VarBooleana, Procedimento, Programa} type;
    int memory;
    struct symbol *next;
}Symbol;

void activateDebugSymbol();

// Insert a new symbol into stack
void insertSymbol(Symbol **stack, char *lexeme, bool scope, enum SymbolType type, int memory);

// Query a lexeme based on a position
Symbol* query(Symbol *stack, char *lexeme, int position);

// Insert the type of symbol
void putType(Symbol **stack, enum SymbolType type);

// Print all symbols in stack
void printStack(Symbol *stack);

// Free memory
void freeSymbol(Symbol **l);

char* symbolTypeToString(enum SymbolType type);

#endif