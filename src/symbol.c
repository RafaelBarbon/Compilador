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

void insertInFix(ExpressionAnalyzer **list, char lexeme[30], LexemeType type) {
    ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));

    strcpy(new->lexeme,lexeme);
    new->type = type;
    new->next = NULL;

    if((*list) == NULL) {
        (*list) = new;
        return;
    }

    ExpressionAnalyzer *aux = *list;
    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;
}

void insertPosFix(ExpressionAnalyzer **PosFix, ExpressionAnalyzer *Expression){
     ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));

    strcpy(new->lexeme, Expression->lexeme);
    new->type = Expression->type;
    new->next = NULL;

    if((*PosFix) == NULL) {
        (*PosFix) = new;
        return;
    }

    ExpressionAnalyzer *aux = *PosFix;
    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;

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

//Return the type of the var/func (Used on expression analyzer)
SymbolType searchVarFuncType(Symbol *l, char *lexeme){
    for(; l != NULL; l = l->next) {
        if(isEqualString(l->lexeme, lexeme))
            return l->type;
    }
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
void push(simpleStack **stack, ExpressionAnalyzer *op){
    simpleStack *new = (simpleStack *)malloc(sizeof(simpleStack));
    new->c = op;
    new->next = *stack;
    *stack = new;
}

ExpressionAnalyzer* pop(simpleStack **stack) {
    if((*stack) == NULL)
        return NULL;

    ExpressionAnalyzer *ret = (*stack)->c;

    simpleStack *old = (*stack);
    (*stack) = (*stack)->next;

    free(old);
    return ret;
}

//searchStackMorePrecedence(&stack, inFix, PosFix)
void searchStackMorePrecedence(simpleStack **stack, ExpressionAnalyzer *op, ExpressionAnalyzer **PosFix){
    simpleStack *aux = (*stack);
    int i = 0;
    LexemeType auxType = op->type;
    switch (auxType){
        case OpMaisMenos:
            while(aux != NULL){
                //printf("loop? %c   %c", op, aux->c);
                //getchar();
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) {//copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case OpMultDiv:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OpMaisMenos || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case E:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OU)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Nao || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case Nao:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == E || aux->c->type == OU)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Nao || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case OU:
            while(aux != NULL){
                if(aux->c->type == AbreP)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == E || aux->c->type == Nao || aux->c->type == OU || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case Rel:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        case UnarioN:
        case UnarioP:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    insertPosFix(PosFix, pop(stack));
                }
                aux = aux->next;
            }
            break;
        default:
            return;
    }
}

void verifyUnaryOperators(ExpressionAnalyzer **inFix) {
    /*
    Se é o primeiro:
        Se é +, descarta
        Se é -, atribui unario
    loop
        Se atual for + ou - e atual não for varint/funcint/num, atribui unario
    */

    ExpressionAnalyzer *aux = (*inFix), *auxFree = NULL, *last = NULL;
    while(aux != NULL) {
        if(aux->type == OpMaisMenos && aux->next != NULL) {
            if(last == NULL && isEqualString(aux->lexeme, "-")) { //unário negativo
                aux->type = UnarioN;
            } else if(last == NULL && isEqualString(aux->lexeme, "+")) { //unário positivo (remove)
                aux->type = UnarioP;
            } else if((last->type != FuncInt || last->type != VarInt || last->type != Num)) { //unário positivo (remove)
                if(isEqualString(aux->lexeme, "+")){
                    aux->type = UnarioP;
                } else if(isEqualString(aux->lexeme, "-")) { //unário negativo
                    aux->type = UnarioN;
                }
            }
        }
        last = aux;
        aux = aux->next;
    }

}


//Número               -> N(simbolo)
//Relação              -> R(simbolo)
//div                  -> /
//variável ou função   -> V(simbolo)
//Boleano              -> B(simbolo)
//E                    -> &
//NAO                  -> !
//OU                   -> |
//UniárioNeg           -> U
//UnárioPos            -> N

//[V, +, R]
//[Vestrela, +, Rmenor]


void convertPosFix(ExpressionAnalyzer **inFixIn, ExpressionAnalyzer **PosFix){
    verifyUnaryOperators(inFixIn);
    //printf("ENTROU POSFIX");
    simpleStack *stack = NULL;

    /*
    Se num ou var ou func, copia
    Se (, empilha
    Se ), desempilha até o primeiro (
    Se o tipo for OpMultDiv, OpMaisMenos, Rel, Nao, E, OU
    */

    ExpressionAnalyzer *aux;
    for(ExpressionAnalyzer *inFix = (*inFixIn); inFix != NULL; inFix = inFix->next) {
        //printf("%c", inFix[i]);
        //getchar();
        if(inFix->type == VarInt || inFix->type == VarBool || inFix->type == Num || inFix->type == FuncBool || inFix->type == FuncInt)//variable or number or function
            insertPosFix(PosFix, inFix);
        else if(inFix->type == AbreP)//Empilha
            push(&stack, inFix);
        else if(inFix->type == FechaP){//Desempilha
            do{
                aux = pop(&stack);//Joga na PosFix até achar o '('
                if(aux->type != AbreP)
                    insertPosFix(PosFix, aux);
            } while(aux->type != AbreP);
        }
        else if(inFix->type == OpMaisMenos || inFix->type == OpMultDiv || inFix->type == Rel || inFix->type == Nao || inFix->type == E || inFix->type == OU || inFix->type == UnarioN || inFix->type == UnarioP) {
            if(stack == NULL)
                push(&stack, inFix);
            else{
                searchStackMorePrecedence(&stack, inFix, PosFix); //Vai retornar uma string, concatenar com a  *ret
                push(&stack,inFix);
                //printf("AQUI O %s %d", ret, strlen(ret));
                //getchar();
            }
        }
    }

    if(stack != NULL) {
        do{
            insertPosFix(PosFix, pop(&stack));
            //printf("LOOP?");
        }while(stack != NULL);
    }
}

//################################################################