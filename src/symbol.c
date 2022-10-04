#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "symbol.h"
#include "verifyChar.h"


void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory) {
    Symbol *new = (Symbol *)malloc(sizeof(Symbol));

    strcpy(new->lexeme,lexeme);
    new->scope = scope;
    new->type = type;
    new->memory = memory;
    new->next = *stack;

    *stack = new;
}

bool query(Symbol *stack, char *lexeme) {
    for(; !isEqualString(stack->lexeme, lexeme) && stack != NULL; stack = stack->next);
    return stack;
}


void putType(Symbol **stack, SymbolType type) {
    
}

void freeSymbol(Symbol **l) {
    Symbol *aux = (*l), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}

void printStack(Symbol *l){
    while(l != NULL){
        printf("\nLexeme: %-30s \t\t Type: %s\nScope: %s Memory: %d\n\n", l->lexeme, symbolTypeToString(l->type), l->scope ? "Sim" : "Nao", l->memory);
        l = l->next;
    }
}

char* symbolTypeToString(SymbolType type){

    switch(type) {
        case Var: return "Var";
        case Func: return "Func";
        case FuncInteira: return "FuncInteira";
        case FuncBooleana: return "FuncBooleana";
        case VarInteira: return "VarInteira";
        case VarBooleana: return "VarBooleana";
        case Procedimento: return "Procedimento";
        case Programa: return "Programa";
    }
}

bool searchDuplicity(Symbol *l, char *lexeme){
    for(; l != NULL; l = l->next)
        if(srtcmp(l->lexeme, lexeme) == 0)
            return true; 
    return false; 
}

bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && symbol->type == Procedimento)
            return true;
    return false;
}

bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && (symbol->type == FuncBooleana || symbol->type == FuncInteira))
            return true;
    return false;
}

bool verifyVarFuncDeclaration(Symbol *symbol, char *lexeme){ //
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && (symbol->type == VarInteira || symbol->type == FuncInteira))
            return true;
    return false;
}

bool verifyVarDeclaration(Symbol *symbol, char *lexeme){
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && symbol->type == VarInteira)
            return true;
    return false;
} 

void unStack(Symbol **symbol) {
    Symbol *aux = (*symbol), *aux2;
    while(aux != NULL || aux->scope){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    *symbol = aux;
}