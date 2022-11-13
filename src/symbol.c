#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "symbol.h"
#include "error.h"
#include "verifyChar.h"


void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory) {
    Symbol *new = (Symbol *)malloc(sizeof(Symbol));

    strcpy(new->lexeme,lexeme);
    new->scope = scope;
    new->type = type;
    new->memory = memory;
    new->next = *stack;

    (*stack) = new;
}

void insertInFix(ExpressionAnalyzer **list, char lexeme[30], LexemeType type) {
    
    if(list == NULL)
        return;
        
    ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));

    //printf("\nInsert INFIX - %s", lexeme);
    //getchar();

    strcpy(new->lexeme,lexeme);
    // printf("\nPassou STRCPY");
    // getchar();
    new->type = type;

    new->next = NULL;
    //printf("\n%s %d",new->lexeme, new->type);
    //getchar();
    if((*list) == NULL) {
        //printf("\nInsert Infix: %s", lexeme);
        //printf("\nSegmentation0");
        //getchar();
        *list = new;
        return;
    }
    // printf("\nSegmentation1");
    // getchar();
    ExpressionAnalyzer *aux = *list;
    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;
    // printf("\nSegmentation2");
    // getchar();
    //printf("\nSaiu Inser Token");
    //getchar();
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
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(aux->scope)
            sameScope = false;
        if(isEqualString(aux->lexeme, lexeme) && sameScope || aux->scope && isEqualString(aux->lexeme, lexeme))//Pesquisa as var no escopo local  || Verifica com os nomes do procedimentos/funções do escopo anterior
            return true;
    }
    return false;
}

//Return the type of the var/func (Used on expression analyzer)
SymbolType searchVarFuncType(Symbol *l, char *lexeme) {
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(isEqualString(aux->lexeme, lexeme))
            return aux->type;
    }
}

LexemeType getVarType(Symbol *l, char *lexeme) {
    bool sameScope = true;
    //printStack(l);
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(isEqualString(aux->lexeme, lexeme)){

            //("\n\nTIIIPOOOOO %d bool %s",aux->type,sameScope?"t":"s");
            if(aux->type == VarBooleana || aux->type == VarInteira)
                return aux->type == VarBooleana ? Booleano : Inteiro;
            else if(sameScope && (aux->type == FuncBooleana || aux->type == FuncInteira))
                return aux->type == FuncBooleana ? Booleano : Inteiro;
            else
                return Rel;// Error
        }
        if(aux->scope){
            sameScope = false;
        }
    }
    detectError(22, lineCount, '\0');//Não encontrou a variável na tabela de simbolos(Nao esta declarada ou não é visivel)
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
    aux->scope = false;
    *symbol = aux;
}

//################################################################# Posfix conversion
//Simple stack functions (Posfix conversion)
void push(simpleStack **stack, ExpressionAnalyzer *op){
    simpleStack *new = (simpleStack *)malloc(sizeof(simpleStack));
    ExpressionAnalyzer *ex = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));
    ex->type = op->type;
    strcpy(ex->lexeme, op->lexeme);
    new->c = ex;
    new->next = *stack;
    *stack = new;
}

ExpressionAnalyzer pop(simpleStack **stack) {

    ExpressionAnalyzer ret;

    if((*stack) == NULL){
        strcpy(ret.lexeme, "VAZIA");
        // ret.type = Inteiro;
        return ret;
    }

    strcpy(ret.lexeme, (*stack)->c->lexeme);

    ret.type = (*stack)->c->type;

    simpleStack *old = (*stack);
    (*stack) = (*stack)->next;

    free(old->c);
    free(old);
    return ret;
}

void printSimpleStack(simpleStack *s) {
    simpleStack *pointer = s;
    printf("\n\nSTACK:\n");
    while(pointer != NULL) {
        printf(" %d ", pointer->c->type);
        pointer = pointer->next;
    }
}

void freeSimpleStack(simpleStack **st) {
    simpleStack *aux = (*st), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    *st = aux;
}

void freeExpression(ExpressionAnalyzer **l) {
    ExpressionAnalyzer *aux = (*l), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}

void printExpression(ExpressionAnalyzer *ex, char *ty, bool type) {
    ExpressionAnalyzer *aux = ex;
    printf("\n\n%s\n",ty);
    while(aux != NULL) {
        if(type)
            printf(" %d ",aux->type);
        else
            printf(" %s ",aux->lexeme);
        aux = aux->next;
    }
    printf("\n\n");
}

void copyExpression(ExpressionAnalyzer **dest, ExpressionAnalyzer *src) {
    ExpressionAnalyzer *aux = src;
    while(aux != NULL){
        ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer)), *nextInsert = NULL;
        new->next = NULL;
        strcpy(new->lexeme, aux->lexeme);
        if(aux->type == FuncBool || aux->type == VarBool)
            new->type = Booleano;
        else if(aux->type == FuncInt || aux->type == VarInt)
            new->type = Inteiro;
        else
            new->type = aux->type;
        if((*dest) == NULL){
            (*dest) = new;
        }else{
            nextInsert =(*dest);
            while(nextInsert->next != NULL) {
                nextInsert = nextInsert->next;
            }
            nextInsert->next = new;
        }
        aux = aux->next;
    }
}

//searchStackMorePrecedence(&stack, inFix, PosFix)
void searchStackMorePrecedence(simpleStack **stack, ExpressionAnalyzer *op, ExpressionAnalyzer **PosFix){
    simpleStack *aux = (*stack);
    int i = 0;
    LexemeType auxType = op->type;
    ExpressionAnalyzer ret;
    //printf("\nAUXTYPE - %s %d", op->lexeme, auxType);
    switch (auxType){
        case OpMaisMenos:
            while(aux != NULL){
                //printf("\nDEBUG - %s   %d", aux-c->lexeme, aux->c->type);
                //getchar();
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) {//copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                }else
                    aux = aux->next;
            }
            break;
        case OpMultDiv:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OpMaisMenos || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);;
                } else
                    aux = aux->next;
            }
            break;
        case E:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OU)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Nao || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case Nao:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == E || aux->c->type == OU)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Nao || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case OU:
            while(aux != NULL){
                if(aux->c->type == AbreP)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == E || aux->c->type == Nao || aux->c->type == OU || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case Rel:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case UnarioN:
        case UnarioP:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos)//Até encontrar (, final da pilha ou primeiro operador com precedência menor
                    return;
                if(aux->c->type == UnarioN || aux->c->type == UnarioP){ //copiando na saída todos os operadores com precedência maior ou igual ao que será empilhado
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
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
    ExpressionAnalyzer *aux = (*inFix), *auxFree = NULL, *last = NULL, *aux2 = NULL;
    while(aux != NULL) {
        if(aux->next != NULL){
            if(aux->type == OpMaisMenos) {
                if(last == NULL && isEqualString(aux->lexeme, "-")) { //unário negativo
                    aux->type = UnarioN;
                } else if(last == NULL && isEqualString(aux->lexeme, "+")) { //unário positivo (remove)
                    aux->type = UnarioP;
                } else if((last->type != FuncInt && last->type != VarInt && last->type != Inteiro)) { //unário positivo (remove)
                    if(isEqualString(aux->lexeme, "+")){
                        aux->type = UnarioP;
                    } else if(isEqualString(aux->lexeme, "-")) { //unário negativo
                        aux->type = UnarioN;
                    }
                }
            } else if(aux->type == Nao && aux->next != NULL && aux->next->type == Nao){ //(NAO NAO) (Se anulam)
                if(last != NULL)
                    last->next = aux->next->next;
                else
                    aux2 = aux->next->next;
                free(aux->next);
                free(aux);
                if(last != NULL)
                    aux = last;
                else{
                    aux = aux2;
                    (*inFix) = aux2;
                    continue;
                }
            }
        }
        last = aux;
        aux = aux->next;
    }
    //printExpression(*inFix, "Type VerifyUn",true);
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
    printExpression(*inFixIn, "IN_FIX_DEPOIS", false);
    //printf("\nENTROU POSFIX");
    simpleStack *stack = NULL;

    /*
    Se num ou var ou func, copia
    Se (, empilha
    Se ), desempilha até o primeiro (
    Se o tipo for OpMultDiv, OpMaisMenos, Rel, Nao, E, OU
    */

    ExpressionAnalyzer aux;
    for(ExpressionAnalyzer *inFix = (*inFixIn); inFix != NULL; inFix = inFix->next) {
        if(inFix->type == VarInt || inFix->type == VarBool || inFix->type == Inteiro || inFix->type == FuncBool || inFix->type == FuncInt || inFix->type == Booleano)//variable or number or function
            insertPosFix(PosFix, inFix);
        else if(inFix->type == AbreP){//Empilha
            push(&stack, inFix);
        }
        else if(inFix->type == FechaP){//Desempilha
            do{
                aux = pop(&stack);//Joga na PosFix até achar o '('
                if(aux.type != AbreP)
                    insertPosFix(PosFix, &aux);
            } while(aux.type != AbreP);
        }
        else if(inFix->type == OpMaisMenos || inFix->type == OpMultDiv || inFix->type == Rel || inFix->type == Nao || inFix->type == E || inFix->type == OU || inFix->type == UnarioN || inFix->type == UnarioP) {
            if(stack == NULL){
                push(&stack, inFix);
            }
            else{
                searchStackMorePrecedence(&stack, inFix, PosFix);
                push(&stack,inFix);
            }
        }
    }

    if(stack != NULL) {
        do{
            aux = pop(&stack);
            if(aux.type != AbreP || aux.type != FechaP)
                insertPosFix(PosFix, &aux);
        }while(stack != NULL);
    }
}

//################################################################