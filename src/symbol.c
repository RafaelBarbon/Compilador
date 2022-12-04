#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "symbol.h"
#include "error.h"
#include "verifyChar.h"


// Insert a new symbol into stack
void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory) {
    Symbol *new = (Symbol *)malloc(sizeof(Symbol));

    strcpy(new->lexeme,lexeme);
    new->scope = scope;
    new->type = type;
    new->memory = memory;
    new->next = *stack;

    (*stack) = new;
}

// Insert the type of symbol of variables
void putType(Symbol **stack, SymbolType type) {
    Symbol *l = *stack;
    for(; l != NULL && l->type == Var; l = l->next) {
        l->type = type;
    }
}

// Insert the type of symbol of function
void putTypeFunc(Symbol **stack, SymbolType type) {
    (*stack)->type = type; // Necessary due to declaration format
}

// Print all symbols in stack
void printStack(Symbol *l) {
    while(l != NULL) { // Used for debug and correction
        printf("\nLexeme: %-30s \t\t Type: %s\nScope: %s Memory: %d\n\n", l->lexeme, symbolTypeToString(l->type), l->scope ? "Sim" : "Nao", l->memory);
        l = l->next;
    }
}

// Free memory
void freeSymbol(Symbol **l) {
    Symbol *aux = (*l), *aux2;
    while(aux != NULL) {
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}

// Convert enum to string
char* symbolTypeToString(SymbolType type) {
    switch(type) { // Used for debug and correction
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

// Verify variable duplicity (need to check if duplicity on global variables are allowed)
bool searchDuplicity(Symbol *l, char *lexeme) {
    bool sameScope = true;
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(aux->scope)
            sameScope = false;
        if(isEqualString(aux->lexeme, lexeme) && sameScope || aux->scope && isEqualString(aux->lexeme, lexeme)) // Search the variables in the local scope || Check with the names of the procedures and functions of the previous scopes
            return true;
    }
    return false;
}

// Returns the address of the declared procedure
int searchProcAddr(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == Procedimento))
            return l->memory;
    return -1;
}

// Returns the address of the declared function or variable
int searchVarFuncAddress(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == VarBooleana || l->type == VarInteira || l->type == FuncInteira || l->type == FuncBooleana))
            return l->memory;
    return -1;
}

// Return the type of the var/func (Used on expression analyzer)
SymbolType searchVarFuncType(Symbol *l, char *lexeme) {
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(isEqualString(aux->lexeme, lexeme))
            return aux->type;
    }
    return Programa;
}

// Returns the type of the specified function or variable name
bool verifyProcedureFunctionDuplicity(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme))
            return true;
    return false;
}

// Verify if the procedure or function have been already declared
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && l->type == Procedimento)
            return true;
    return false;
}

// Verify if the procedure was already declared (check if search duplicity can overwrite this)
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == FuncBooleana || l->type == FuncInteira))
            return true;
    return false;
}

// Verify if the function was already declared (check if search duplicity can overwrite this)
bool verifyVarFuncDeclaration(Symbol *symbol, char *lexeme) {
    for(Symbol *l = symbol; l != NULL; l = l->next)
        if(isEqualString(l->lexeme, lexeme) && (l->type == VarBooleana || l->type == FuncBooleana || l->type == VarInteira || l->type == FuncInteira))
            return true;
    return false;
}

// verify if the var/func was declared
bool verifyVarDeclaration(Symbol *symbol, char *lexeme, int *memory){
    for(Symbol *l = symbol; l != NULL; l = l->next) {
        if(isEqualString(l->lexeme, lexeme) && l->type == VarInteira) {
            *memory = l->memory;
            return true;
        }
    }
    return false;
}

// Unstack until the next scope (local variable region)
int unStack(Symbol **symbol) {
    int countVars = 0;
    Symbol *aux = (*symbol), *aux2;
    while(aux != NULL && !aux->scope) {
        if(aux->type == VarInteira || aux->type == VarBooleana) {
            countVars++; // Will count the variables to be deallocated in the code generation
        }
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    aux->scope = false;
    *symbol = aux;
    return countVars;
}

//################################################################# Posfix conversion

// Push stack (Used on expression analyzer)
void push(simpleStack **stack, ExpressionAnalyzer *op){
    simpleStack *new = (simpleStack *)malloc(sizeof(simpleStack));
    ExpressionAnalyzer *ex = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));
    ex->type = op->type;
    strcpy(ex->lexeme, op->lexeme);
    new->c = ex;
    new->next = *stack;
    *stack = new;
}

// Pop stack (Used on expression analyzer)
ExpressionAnalyzer pop(simpleStack **stack) {
    ExpressionAnalyzer ret;

    if((*stack) == NULL){
        strcpy(ret.lexeme, "VAZIA");
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

// Print the simple stack used to analyze the expression
void printSimpleStack(simpleStack *s) {
    simpleStack *pointer = s; // Used on debug and code correction
    printf("\n\nSTACK:\n");
    while(pointer != NULL) {
        printf(" %d ", pointer->c->type);
        pointer = pointer->next;
    }
}

// Free the simple stack memory allocated used to analyze the expression
void freeSimpleStack(simpleStack **st) {
    simpleStack *aux = (*st), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    *st = aux;
}

// Free the expression memory allocated used on semantic to analyze expressions
void freeExpression(ExpressionAnalyzer **l) {
    ExpressionAnalyzer *aux = (*l), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    (*l) = NULL;
}

// Print the expression (Used on DEBUG mode to POS_FIX conversion)
void printExpression(ExpressionAnalyzer *ex, char *ty, bool type) {
    ExpressionAnalyzer *aux = ex;
    printf("\n\nDEBUG - Semantico - %s\n",ty); // Used on debug and code correction
    while(aux != NULL) {
        if(type)
            printf(" %d ",aux->type);
        else
            printf(" %s ",aux->lexeme);
        aux = aux->next;
    }
    printf("\n\n");
}

// Make a copy of a expression (Used to make a copy from POS_FIX expression to analyze the expression type (Semantic Analayzer))
void copyExpression(ExpressionAnalyzer **dest, ExpressionAnalyzer *src) {
    if(debug)
        printf("DEBUG - Semantico - Copy Expression");
    ExpressionAnalyzer *aux = src;
    while(aux != NULL) {
        ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer)), *nextInsert = NULL;
        new->next = NULL;
        strcpy(new->lexeme, aux->lexeme);
        if(aux->type == FuncBool || aux->type == VarBool) // Treat the boolean type of the variable/function
            new->type = Booleano;
        else if(aux->type == FuncInt || aux->type == VarInt) // Treat the integer type of the variable/function
            new->type = Inteiro;
        else
            new->type = aux->type;
        if((*dest) == NULL){
            (*dest) = new;
        }else{
            nextInsert =(*dest);
            while(nextInsert->next != NULL) { // Insert in the end of expression
                nextInsert = nextInsert->next;
            }
            nextInsert->next = new;
        }
        aux = aux->next;
    }
}

// Get the variable type (integer or boolean)
LexemeType getVarType(Symbol *l, char *lexeme) {
    bool sameScope = true;
    for(Symbol *aux = l; aux != NULL; aux = aux->next) { // Search in the Symbol Table
        if(isEqualString(aux->lexeme, lexeme)){
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
    detectError(22, lineCount, '\0');// Didn't found the variable in the Symbol Table - variable undeclared or not in the same scope
}

// Check if the lexeme informed is a function and returns it's type
LexemeType isFunction(Symbol *l, char *lexeme) {
    for(Symbol *aux = l; aux != NULL; aux = aux->next) {
        if(isEqualString(aux->lexeme, lexeme)){
            if(aux->type == FuncBooleana)
                return FuncBool;
            else if(aux->type == FuncInteira)
                return FuncInt;
            else
                return Rel; // Error
        }
        if(aux->scope){
            return Rel;
        }
    }
}

// Used on syntatic to insert the found expression
void insertInFix(ExpressionAnalyzer **list, char lexeme[maxIdentifierLength], LexemeType type) {
    if(list == NULL)
        return;

    ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));

    if(debug)
        printf("\nDEBUG - Insert INFIX - %s", lexeme);

    strcpy(new->lexeme,lexeme);
    new->type = type;

    new->next = NULL;
    if((*list) == NULL) {
        *list = new;
        return;
    }
    ExpressionAnalyzer *aux = *list;
    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new;
}

// Used on semantic to insert the IN_FIX convertion of the expression
void insertPosFix(ExpressionAnalyzer **PosFix, ExpressionAnalyzer *Expression) {
    ExpressionAnalyzer *new = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));

    if(debug)
        printf("\nDEBUG - Insert POSFIX");

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

// Find the next operator with more precedence to insert correctly in the POS_FIX expression
void searchStackMorePrecedence(simpleStack **stack, ExpressionAnalyzer *op, ExpressionAnalyzer **PosFix){
    if(debug)
        printf("DEBUG - Semantico - Search Stack more precedence");
    simpleStack *aux = (*stack);
    int i = 0;
    LexemeType auxType = op->type;
    ExpressionAnalyzer ret;

    /*
    Precedence order:
        Unary
        MULT/DIV
        ADD/SUB
        Relational operators
        NOT
        AND
        OR
    */

    switch (auxType){
        case OpMaisMenos:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                }else
                    aux = aux->next;
            }
            break;
        case OpMultDiv:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OpMaisMenos || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == OpMultDiv || aux->c->type == UnarioN || aux->c->type == UnarioP) { // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);;
                } else
                    aux = aux->next;
            }
            break;
        case E:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == OU) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == Nao || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case Nao:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == E || aux->c->type == OU) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == Nao || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP) { // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case OU:
            while(aux != NULL){
                if(aux->c->type == AbreP) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == E || aux->c->type == Nao || aux->c->type == OU || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
                    aux = aux->next;
                    ret = pop(stack);
                    insertPosFix(PosFix, &ret);
                } else
                    aux = aux->next;
            }
            break;
        case Rel:
            while(aux != NULL){
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos || aux->c->type == UnarioN || aux->c->type == UnarioP){ // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
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
                if(aux->c->type == AbreP || aux->c->type == Nao || aux->c->type == OU || aux->c->type == E || aux->c->type == Rel || aux->c->type == OpMultDiv || aux->c->type == OpMaisMenos) // Util find '(' OR empty stack or the first operator with less procedence
                    return;
                if(aux->c->type == UnarioN || aux->c->type == UnarioP){ // Insert POS_FIX all operators with precedence grather than or equals to the one that will be inserted in the STACK
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

// Used to identify Unary operators in the IN_FIX expression and change their type to 'UnarioP' or 'UnarioN' (Used before POS_FIX conversion)
void verifyUnaryOperators(ExpressionAnalyzer **inFix) {
    /*
    If is the first and the lexeme is + or -:
        Attribute unary
    If actual is + or - and previous token is not varint/funcInt/num:
        Attribute unary
    */
    if(debug)
        printf("DEBUG - Semantico - Verify Unary Operators");
    ExpressionAnalyzer *aux = (*inFix), *auxFree = NULL, *last = NULL, *aux2 = NULL;
    while(aux != NULL) {
        if(aux->next != NULL) {
            if(aux->type == OpMaisMenos) {
                if(last == NULL && isEqualString(aux->lexeme, "-")) { // Negative unary
                    aux->type = UnarioN;
                } else if(last == NULL && isEqualString(aux->lexeme, "+")) { // Positive unary
                    aux->type = UnarioP;
                } else if((last->type != FuncInt && last->type != VarInt && last->type != Inteiro && last->type != FechaP)) { // Positive unary
                    if(isEqualString(aux->lexeme, "+")) {
                        aux->type = UnarioP;
                    } else if(isEqualString(aux->lexeme, "-")) { // Negative unary
                        aux->type = UnarioN;
                    }
                }
            } else if(aux->type == Nao && aux->next != NULL && aux->next->type == Nao) { // (NAO NAO) anulate themselves
                if(last != NULL)
                    last->next = aux->next->next;
                else
                    aux2 = aux->next->next;
                free(aux->next);
                free(aux);
                if(last != NULL)
                    aux = last;
                else {
                    aux = aux2;
                    (*inFix) = aux2;
                    continue;
                }
            }
        }
        last = aux;
        aux = aux->next;
    }
    if(debug)
        printExpression(*inFix, "Type VerifyUn",true);
}

// Convert the IN_FIX expression to POS_FIX expression
void convertPosFix(ExpressionAnalyzer **inFixIn, ExpressionAnalyzer **PosFix){
    verifyUnaryOperators(inFixIn); // Check and convert the types of proper unary operators

    if(debug) {
        printf("DEBUG - Semantico - ENTROU POSFIX\n");
        printExpression(*inFixIn, "IN_FIX_DEPOIS", false);
    }
    simpleStack *stack = NULL;

    /*
    If number or variable or function, copy
    If (, push on stack
    If ), unstack (pop) until the first (
    If the type is OpMultDiv, OpMaisMenos, Rel, Nao, E, OU, UnarioN, UnarioP analyze the stack to search the operators with more precedence and stack the current operator
    */

    ExpressionAnalyzer aux;
    for(ExpressionAnalyzer *inFix = (*inFixIn); inFix != NULL; inFix = inFix->next) {
        if(inFix->type == VarInt || inFix->type == VarBool || inFix->type == Inteiro || inFix->type == FuncBool || inFix->type == FuncInt || inFix->type == Booleano) // Variable or number or function
            insertPosFix(PosFix, inFix);
        else if(inFix->type == AbreP){ // Insert Stack
            push(&stack, inFix);
        }
        else if(inFix->type == FechaP){ // Unstack
            do{
                aux = pop(&stack); // Insert POS_FIX until find '('
                if(aux.type != AbreP)
                    insertPosFix(PosFix, &aux);
            } while(aux.type != AbreP);
        }
        else if(inFix->type == OpMaisMenos || inFix->type == OpMultDiv || inFix->type == Rel || inFix->type == Nao || inFix->type == E || inFix->type == OU || inFix->type == UnarioN || inFix->type == UnarioP) {
            if(stack == NULL){
                push(&stack, inFix);
            }
            else{
                searchStackMorePrecedence(&stack, inFix, PosFix); // Unstack operators with equal or more precendece
                push(&stack,inFix);
            }
        }
    }

    if(stack != NULL) { // Unstack the operators that remains in the stack
        do{
            aux = pop(&stack);
            if(aux.type != AbreP || aux.type != FechaP)
                insertPosFix(PosFix, &aux);
        } while(stack != NULL);
    }
}
