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

// Verify variable duplicity (need to check if duplicity on global variabes are allowed)
bool searchDuplicity(Symbol *l, char *lexeme){
    for(; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme))
            return false; 
    return true;  //Se não tiver duplicidade retorna true. 
}

// Verify if the procedure was already declared (check if search duplicity can overwrite this)
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && symbol->type == Procedimento)
            return true;
    return false;
}

// Verify if the function was already declared (check if search duplicity can overwrite this)
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && (symbol->type == FuncBooleana || symbol->type == FuncInteira))
            return true;
    return false;
}

// Verify if the int var/func was declared
bool verifyIntVarFuncDeclaration(Symbol *symbol, char *lexeme){ //
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && (symbol->type == VarInteira || symbol->type == FuncInteira))
            return true;
    return false;
}

// verify if the var/func was declared
bool verifyVarFuncDeclaration(Symbol *symbol. char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0)
            return true;
    return false;
}

// Verify if the int var was declared
bool verifyVarDeclaration(Symbol *symbol, char *lexeme){
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(strcmp(symbol->lexeme, lexeme) == 0 && symbol->type == VarInteira)
            return true;
    return false;
} 

void unStack(Symbol **symbol) {
    Symbol *aux = (*symbol), *aux2;
    while(aux != NULL || !aux->scope){
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
    (*stack) = (*stack)->prox;
    
    free(old);
    return ret;
}

char unstackOperator(simpleStack **stack, char op){
    simpleStack *aux = (*stack), before = NULL;
    char ret;
    while(aux != NULL){
        if(aux->c != 'op'){
            before = aux;
            aux = aux->next;
        } 
        ret = aux->c;
        before->next = aux->next;
        return ret;
    } 
    return '%'; //pilha vazia
}

char* searchStackMorePrecedence(simpleStack **stack, char op, int *j){
    simpleStack *aux = (*stack);
    int i = 0;
    char ret[] = {0};//Ver como vai ficar o tamanho do ret 
    switch (aux->c){
        case '*':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '+' || aux->c == '-')//Até encontrar '(', final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '/' || aux->c == '*') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '+':
            while(aux != NULL){
                if(aux->c == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '/' || aux->c == '*' || aux->c == '-' || aux->c == '+') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '-':
            while(aux != NULL){
                if(aux->c == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '/' || aux->c == '*' || aux->c == '+' || aux->c == '-')//copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '/':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '+' || aux->c == '-')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '*' || aux->c == '/') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '&':
            while(aux != NULL){
                if(aux->c == '(' || aux->c == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '!', aux->c == '&') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '!':
             while(aux != NULL){
                if(aux->c == '(' || aux->c == '&' || aux->c == '|')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '!') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        case '|':
            while(aux != NULL){
                if(aux->c == '(')//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return; 
                if(aux->c == '&' || aux->c == '!' || aux->c == '|') //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    if(ant == NULL)
                        ret[i++] = pop(stack);
                    else{
                        ret[i++] = unstackOperator(stack, op);//desempilha
                    }
                aux = aux->next;
            }
            break;
        
        default:
            continue;
        }
        *j = (*j) + (--i);
        return ret;
}


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

char* convertPosFix(char *inFix, int size){
    simpleStack *stack = NULL;
    int j = 0;
    char *ret = (char *)malloc(size * sizeof(char));
    char aux;
    for(int i =0; i < tam; i++){
        if(inFix[i] == 'N' || inFix[i] == 'V'){//variable or number
            ret[j++] = inFix[i];
            continue;    
        }

        if(inFix[i] == '('){//Emplinha
            push(&stack, '(');
            continue;
        }

        if(inFix[i] == ')'){//Desempilha
            do{
                ret[j++] = aux = pop(&stack);//Joga no vetor de retorno
            }while(aux != '(');
            continue;
        }

        if(inFix[i] == '*' || inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '/' || inFix[i] == 'R'){
            char cPrec = searchStachMorePrecedence(&stack, inFix[i], &j); //Vai retornar uma string, concatenar com a  *ret
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