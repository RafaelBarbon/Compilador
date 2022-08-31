#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

// Biblioteca QT para interface grafica



// Control variables
Token *tokenList = NULL;
int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor

void updateCursor(char *c) {
    *c = getc(sourceFile);
    // DEBUG
    //printf("%c ", *c);
}

bool isSpaceCode(char c) {
    if(c == '\n')
        lineCount++;
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool isNotEndOfFile(char c) {
    return c != EOF;
}

bool isDigit(char c) {
    return c >= 48 && c <= 57;
}

bool isLetter(char c) {
    return c >= 65 && c <= 90 || c >= 97 && c <= 122;
}

bool isAritmeticOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

bool isRelationalOperator(char c) {
    return c == '!' || c == '>' || c == '<' || c == '=';
}

bool isPonctuation(char c) {
    return c == ';' || c == ',' || c == '(' || c == ')' || c == '.';
}

bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}

bool isIdentifier(char c) {
    return isDigit(c) || isLetter(c) || c == '_';
}

void symbolError(char c) {
    char error[2] = {0};
    error[0] = c;
    //printf("\nDEBUG: ERROR %d\n", c);
    insertToken(&tokenList, error, "serro");
    printf("\nSimbolo nao encontrado na linha %d\n", lineCount);
    //exit(1);
}

void treatDigit(char *c){
    char word[30] = {0};
    int i=0;
    word[i++] = *c;
    updateCursor(&(*c));

    while(isDigit(*c) && isNotEndOfFile(*c)){
        word[i++] = *c;
        updateCursor(&(*c));
    }
    flagUpdate = false;

    insertToken(&tokenList, word, "snumero");
}

void treatAttribution(char *c) {
    //printf("DEBUG - Trata atribuicao");
    updateCursor(&(*c));
    if(isNotEndOfFile(*c) && *c == '=')
        insertToken(&tokenList, ":=", "satribuicao");
    else {
        insertToken(&tokenList, ":", "sdoispontos");
        flagUpdate = false;
    }
}

void treatArithmeticOperator(char *c) {
    //printf("\nDEBUG - Trata operador aritmetico\n");
    switch(*c){
        case '+':
            insertToken(&tokenList, "+", "smais");
        break;
        case '-':
            insertToken(&tokenList, "-", "smenos");
        break;
        case '*':
            insertToken(&tokenList, "*", "smult");
        break;
            symbolError(*c);
    }
}

void treatRelationalOperator(char *c) {
    //printf("\nDEBUG - Trata operador relacional\n");
    switch(*c) {
        case '!':
            updateCursor(&(*c));
            if(isNotEndOfFile(*c) && *c == '='){
                insertToken(&tokenList, "!=", "sdif");
                flagUpdate = false;
            } else
                symbolError('!');
            break;
        case '<': 
            updateCursor(&(*c));
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(&tokenList, "<=", "smenorig");
            else{
                insertToken(&tokenList, "<", "smenor");
                flagUpdate = false;
            }
            break;
        case '>':
            updateCursor(&(*c)); 
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(&tokenList,">=","smaiorig");
            else{
                insertToken(&tokenList, ">", "smaior");
                flagUpdate = false;
            }
            break;
        case '=': 
            insertToken(&tokenList, "=", "sig");
            break;
        default:
            symbolError(*c);
    }
}

void treatPunctuation(char *c) {
    //printf("\nDEBUG - Pontuacao\n");
    switch(*c) {
        case ';': 
            insertToken(&tokenList, ";", "sponto_virgula");
            break;
        case ',': 
            insertToken(&tokenList, ",", "svirgula");
            break;
        case '(': 
            insertToken(&tokenList, "(", "sabre_parenteses");
            break;
        case ')': 
            insertToken(&tokenList, ")", "sfecha_parenteses");
            break;
        case '.': 
            insertToken(&tokenList, ".", "sponto");
            break;
        default:
            symbolError(*c);
    }
}

void identifyReservedWord(char *c) {
    char word[30] = {0};
    int i = 0; // Contador para tamanho máximo do identificador
    //printf("Teste0");
    if(!isLetter(*c)) {
        printf("DEBUG: ERRO - comeco do identificador");
        exit(1);
    }
    
    word[i++] = *c;
    //printf("Teste1");
    updateCursor(&(*c));
    //printf("Teste2");
    while(!isSpaceCode(*c) && isNotEndOfFile(*c) && i < 30 && isIdentifier(*c)) {
        word[i++] = *c;
        updateCursor(&(*c));
    }
    flagUpdate = false;
    //printf("Terminou de identificar a palavra");
    if(isEqualString(word, "programa"))
        insertToken(&tokenList, word, "sprograma");
    else if(isEqualString(word, "se"))
        insertToken(&tokenList, word, "sse");
    else if(isEqualString(word, "entao"))
        insertToken(&tokenList, word, "sentao");
    else if(isEqualString(word, "senao"))
        insertToken(&tokenList, word, "ssenao");
    else if(isEqualString(word, "enquanto"))
        insertToken(&tokenList, word, "senquanto");
    else if(isEqualString(word, "faca"))
        insertToken(&tokenList, word, "sfaca");
    else if(isEqualString(word, "inicio"))
        insertToken(&tokenList, word, "sinicio");
    else if(isEqualString(word, "fim"))
        insertToken(&tokenList, word, "sfim");
    else if(isEqualString(word, "escreva"))
        insertToken(&tokenList, word, "sescreva");
    else if(isEqualString(word, "leia"))
        insertToken(&tokenList, word, "sleia");
    else if(isEqualString(word, "var"))
        insertToken(&tokenList, word, "svar");
    else if(isEqualString(word, "inteiro"))
        insertToken(&tokenList, word, "sinteiro");
    else if(isEqualString(word, "booleano"))
        insertToken(&tokenList, word, "sbooleano");
    else if(isEqualString(word, "verdadeiro"))
        insertToken(&tokenList, word, "sverdadeiro");
    else if(isEqualString(word, "falso"))
        insertToken(&tokenList, word, "sfalso");
    else if(isEqualString(word, "procedimento"))
        insertToken(&tokenList, word, "sprocedimento");
    else if(isEqualString(word, "funcao"))
        insertToken(&tokenList, word, "sfuncao");
    else if(isEqualString(word, "div"))
        insertToken(&tokenList, word, "sdiv");
    else if(isEqualString(word, "e"))
        insertToken(&tokenList, word, "se");
    else if(isEqualString(word, "ou"))
        insertToken(&tokenList, word, "sou");
    else if(isEqualString(word, "nao"))
        insertToken(&tokenList, word, "snao");
    else
        insertToken(&tokenList, word, "sidentificador");
}

void colectToken(char *c) {
    //printf("Teste coleta token:[%c]", *c);
    if(isDigit(*c)){        
        treatDigit(c);
    }else if(isLetter(*c)){
        identifyReservedWord(c);
    }else if(*c == ':'){
        treatAttribution(c);    
    }else if(isAritmeticOperator(*c)){
        treatArithmeticOperator(c);
    }else if(isRelationalOperator(*c)){
        treatRelationalOperator(c);
    }else if(isPonctuation(*c)){
        treatPunctuation(c);
    }else{
        symbolError(*c);
    }
        
}

int main(int argc, char *argv[]) {

    if(argc < 1) {
        printf("Erro! O nome do arquivo a ser analisado deve ser informado!");
        exit(1);
    }

    sourceFile = fopen(argv[1], "r");

    if(!sourceFile) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    else
        printf("DEBUG - Arquivo aberto com sucesso.\n");

    char c;
    updateCursor(&c);

    while(isNotEndOfFile(c)) {
        if(c == '{') {
            updateCursor(&c);
            while(c != '}' && isNotEndOfFile(c)) {//Adicionar erro n fechou comentario 
                if(c == '\n')
                    lineCount++;
                updateCursor(&c);
            }
            if(c == EOF){
                printf("\nErro: esperado simbolo } na linha %d\n", lineCount);
                break;
            }
            updateCursor(&c);
        } else if (isSpaceCode(c)) {
            updateCursor(&c);
            while(isSpaceCode(c) && isNotEndOfFile(c))
                updateCursor(&c);
            if(c == EOF)
                break;
        } 
        else {
            colectToken(&c);
            
            if(flagUpdate)
                updateCursor(&c);
            else 
                flagUpdate = true;
        }
    }

    fclose(sourceFile);

    printToken(tokenList);

    freeToken(&tokenList);

    return 0;
}

