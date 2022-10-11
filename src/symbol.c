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


void putType(Symbol **stack, SymbolType type) {
    (*stack)->type = type;
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
        if(isEqualString(l->lexeme, lexeme))
            return false; 
    return true;  //Se não tiver duplicidade retorna true. 
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

//################################################################# Posfix conversion
//Simple stack functions (Posfix conversion)
void push(simpleStack **stack, char c){
    simpleStack *new = (simpleStack *)malloc(sizeof(simpleStack));
    new->c = c;
    new->next = *stack;
    *stack = new;
}

char pop(simpleStack **stack, char c){
    if((*stack) == NULL)
        return '%';
    
    char ret = (*stack)->c;
    
    simpleStack *old = (*stack);
    (*stack) = (*stack)->prox;
    
    free(old);
    return ret;
}

char searchStachMorePrecedence(simpleStack *stack, char op){
    while()
}

char* convertPosFix(char inFix[], int size){
    simpleStack *stack = NULL;
    int j = 0;
    char *ret = (char *)malloc(size * sizeof(char));
    char aux;
    for(int i =0; i < tam; i++){
        
        //Verificar numero com dois digitos (Ex. 30)
        if((inFix[i] >= 65 && inFix[i] <= 90) || (inFix[i] >= 97 && inFix[i] <= 122) || (inFix[i] >= 48 && inFix[i] <= 57)){//variable or number
            ret[j++] = c;
            if(j < size && inFix[j + 1] != ' '){ //Adicionar espaço no em cada um
                ret[j++] = c;
            }
            continue;    
        }

        if(inFix[i] == '('){//Emplinha
            push(&stack, '(');
            continue;
        }

        if(inFix[i] == ')'){//Desempilha
            do{
                aux = pop(&stack);//Joga no vetor de retorno
                ret[j++] = aux;
            }while(aux != '(');

            continue;
        }

        if(inFix[i] == '*' || inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '/' || inFix[i] == '>' || inFix[i] == '<' || inFix[i] == '='){//Operator (INSERIR '/' AO INVÉS DE DIV)
            char cPrec = searchStachMorePrecedence(stack, inFix[i]);
            if(cPrec != '%')
                do{
                    aux = pop(&stack);//Joga no vetor de retorno
                    ret[j++] = aux;
                }while(aux != cPrec);

            continue;
        }
    }

    if(stack != NULL)
        do{
            ret[j++] =  pop(&stack);
        }while(stack != NULL);  
    
    return ret;
}

//################################################################