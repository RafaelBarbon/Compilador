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
    char c;
    struct simpleStack *next;
}simpleStack; 

void push(simpleStack **stack, char c);

char pop(simpleStack **stack);

//Numero     -> N
//Relação    -> R
//div        -> /
//variavel   -> V
//Boleano    -> B
//E          -> &
//NAO        -> !             
//OU         -> |
//UniárioNeg -> 
//UnárioPos  ->  

char* convertPosFix(char *inFix, int size);

char unstackOperator(simpleStack **stack, char op);

void searchStackMorePrecedence(simpleStack **stack, char op, int *j, char *stringRet);

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

// Verify if the function was already declared (check if search duplicity can overwrite this)
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme);

// Verify if the procedure was already declared (check if search duplicity can overwrite this)
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme);

// verify if the var/func was declared
bool verifyVarFuncDeclaration(Symbol *stack, char *lexeme);

// Verify if the int var/func was declared
bool verifyIntVarFuncDeclaration(Symbol *stack, char *lexeme);

// Verify if the int var was declared
bool verifyVarDeclaration(Symbol *stack, char *lexeme);

// Unstack until the next scope (local variable region)
void unStack(Symbol **symbol);


bool verifyProcedureFunctionDuplicity(Symbol *symbol, char *lexeme);

#endif