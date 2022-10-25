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
    Symbol *l = *stack;
    for(; l != NULL && l->type == Var; l = l->next) {
        l->type = type;
    }
}

void putTypeFunc(Symbol **stack, SymbolType type) {
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
    bool sameScope = true;
    for(; l != NULL; l = l->next) {
        if(l->scope)
            sameScope = false;
        if(isEqualString(l->lexeme, lexeme) && sameScope || l->scope && isEqualString(l->lexeme, lexeme))//Pesquisa as var no escopo local  || Verifica com os nomes do procedimentos/funções do escopo anterior
            return true;
    }
    return false;
}

bool verifyProcedureFunctionDuplicity(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme))
            return true;
    return false;
}

bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && l->type == Procedimento)
            return true;
    return false;
}

bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == FuncBooleana || l->type == FuncInteira)){
            return true;
        }
    return false;
}

bool verifyIntVarFuncDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == VarInteira || l->type == FuncInteira))
            return true;
    return false;
}

bool verifyVarFuncDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == VarBooleana || l->type == FuncBooleana || l->type == VarInteira || l->type == FuncInteira))
            return true;
    return false;
}

bool verifyVarDeclaration(Symbol *symbol, char *lexeme){
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && l->type == VarInteira)
            return true;
    return false;
}

void unStack(Symbol **symbol) {
    Symbol *aux = (*symbol), *aux2;
    while(aux != NULL && !aux->scope){
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

char pop(simpleStack **stack){
    if((*stack) == NULL)
        return '%';

    char ret = (*stack)->c;

    simpleStack *old = (*stack);
    (*stack) = (*stack)->next;

    free(old);
    return ret;
}

char unstackOperator(simpleStack **stack, char op){
    simpleStack *aux = (*stack), *before = NULL;
    char ret;
    while(aux != NULL){
        if(aux->c != op){
            before = aux;
            aux = aux->next;
        }
        ret = aux->c;
        before->next = aux->next;
        return ret;
    }
    return '%'; //pilha vazia
}

void searchStackMorePrecedence(simpleStack **stack, char op, int *j, char *stringRet){
    simpleStack *aux = (*stack);
    int i = 0;
    bool first = true;
    char compare = aux->c;
    switch (compare){
        case '*':
            while(aux != NULL){
                if(compare == '(' || compare == '+' || compare == '-')//Até encontrar '(', final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '/' || compare == '*') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '+':
            while(aux != NULL){
                if(compare == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '/' || compare == '*' || compare == '-' || compare == '+'){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '-':
            while(aux != NULL){
                if(compare == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '/' || compare == '*' || compare == '+' || compare == '-') {//copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '/':
            while(aux != NULL){
                if(compare == '(' || compare == '+' || compare == '-')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '*' || compare == '/') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '&':
            while(aux != NULL){
                if(compare == '(' || compare == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '!' || compare == '&') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '!':
            while(aux != NULL){
                if(compare == '(' || compare == '&' || compare == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '!') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        case '|':
            while(aux != NULL){
                if(compare == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(compare == '&' || compare == '!' || compare == '|'){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(first)
                        stringRet[i++] = pop(stack);
                    else
                        stringRet[i++] = unstackOperator(stack, op);//desempilha
                }
                aux = aux->next;
                first = false;
            }
            break;
        default:
            return;
    }
    *j = (*j) + (--i);
    return;
}


//Número               -> N
//Relação              -> R
//div                  -> /
//variável ou função   -> V
//Boleano              -> B
//E                    -> &
//NAO                  -> !
//OU                   -> |
//UniárioNeg           -> U
//UnárioPos            -> N

char* convertPosFix(char *inFix, int size){
    simpleStack *stack = NULL;
    int j = 0;
    char *ret = (char *)malloc(size * sizeof(char));
    char aux;
    for(int i =0; i < size; i++){
        if(inFix[i] == 'N' || inFix[i] == 'V')//variable or number
            ret[j++] = inFix[i];
        else if(inFix[i] == '(')//Empilha
            push(&stack, '(');
        else if(inFix[i] == ')'){//Desempilha
            do{
                ret[j++] = aux = pop(&stack);//Joga no vetor de retorno
            }while(aux != '(');
        }
        else if(inFix[i] == '*' || inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '/' || inFix[i] == 'R'){
            char ret[30] = {0};
            searchStackMorePrecedence(&stack, inFix[i], &j, ret); //Vai retornar uma string, concatenar com a  *ret
            if(strlen(ret) != 0)
                for(int k = 0; k < strlen(ret); k++)
                    ret[j++] = ret[k];
        }
    }

    if(stack != NULL) {
        do{
            ret[j++] = pop(&stack);
        }while(stack != NULL);
    }

    return ret;
}

//################################################################