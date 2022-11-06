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

void searchStackMorePrecedence(simpleStack **stack, char op, int *j, char *stringRet){
    simpleStack *aux = (*stack);
    int i = 0;
    switch (op){
        case '+':
        case '-':
            while(aux != NULL){
                //printf("loop? %c   %c", op, aux->c);
                //getchar();
                if(aux->c == '(' || aux->c == '!' || aux->c == '|' || aux->c == '&' || aux->c == 'R')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == '/' || aux->c == '*' || aux->c == '+' || aux->c == '-') {//copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    stringRet[i++] = pop(stack);
                }
                aux = aux->next;
            }
            break;
        case '*':
        case '/':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '+' || aux->c == '-' || aux->c == '!' || aux->c == '|' || aux->c == '&' || aux->c == 'R')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == '*' || aux->c == '/') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    stringRet[i++] = pop(stack);
                }
                aux = aux->next;
            }
            break;
        case '&':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == '!' || aux->c == '&' || aux->c == 'R' || aux->c == '*' || aux->c == '/' || aux->c == '-' || aux->c == '+') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    stringRet[i++] = pop(stack);
                }
                aux = aux->next;
            }
            break;
        case '!':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '&' || aux->c == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == '!' || aux->c == 'R' || aux->c == '*' || aux->c == '/' || aux->c == '-' || aux->c == '+') { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    stringRet[i++] = pop(stack);
                }
                aux = aux->next;
            }
            break;
        case '|':
            while(aux != NULL){
                if(aux->c == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == '&' || aux->c == '!' || aux->c == '|' || aux->c == 'R' || aux->c == '*' || aux->c == '/' || aux->c == '-' || aux->c == '+'){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                        stringRet[i++] = pop(stack);
                }
                aux = aux->next;
            }
            break;
        case 'R':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '!' || aux->c == '|' || aux->c == '&')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c == 'R' || aux->c == '*' || aux->c == '/' || aux->c == '-' || aux->c == '+'){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    stringRet[i++] = pop(stack);
                }
                aux = aux->next;
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

char* convertPosFix(char *inFix, int size, char *ret){
    //printf("ENTROU POSFIX");
    simpleStack *stack = NULL;
    int j = 0;
    //char *ret = (char *)malloc(size * sizeof(char));
    char aux;
    for(int i = 0; i < size; i++){
        //printf("%c", inFix[i]);
        //getchar();
        if(inFix[i] == 'N' || inFix[i] == 'V')//variable or number
            ret[j++] = inFix[i];
        else if(inFix[i] == '(')//Empilha
            push(&stack, '(');
        else if(inFix[i] == ')'){//Desempilha
            do{
                aux = pop(&stack);//Joga no vetor de retorno
                if(aux != '(')
                    ret[j++] = aux;
            } while(aux != '(');
        }
        else if(inFix[i] == '*' || inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '/' || inFix[i] == 'R' || inFix[i] == '!' || inFix[i] == '|' || inFix[i] == '&'){
            char retMorePrecedence[30] = {0};
            if(stack == NULL)
                push(&stack, inFix[i]);
            else{
                searchStackMorePrecedence(&stack, inFix[i], &j, retMorePrecedence); //Vai retornar uma string, concatenar com a  *ret
                push(&stack,inFix[i]);
                //printf("AQUI O %s %d", ret, strlen(ret));
                //getchar();
                for(int k = 0; k < strlen(retMorePrecedence); k++){
                    //printf("\nJJJ  %d KKK %d\n%s\n\n", j, k, ret);
                    //getchar();
                    if(retMorePrecedence[k] != '(')
                        ret[j++] = retMorePrecedence[k];
                }
            }
        }
    }

    if(stack != NULL) {
        do{
            ret[j++] = pop(&stack);
            //printf("LOOP?");
        }while(stack != NULL);
    }

    return ret;
}

//################################################################