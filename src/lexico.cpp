#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
//#include "symbol.h"
#include "token.h"
#include "verifyChar.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Biblioteca QT para interface grafica



void symbolError(char c, Token **tokenList,Ui::MainWindow *ui) {
    char error[2] = {0};
    error[0] = c;
    if(debug)
        printf("\nDEBUG - Lexico - ERROR %d { %c }\n", c, c);
    insertToken(tokenList, error, "serro");
    detectError(1,lineCount,c,ui);
}

void treatDigit(char *c, Token **tokenList,Ui::MainWindow *ui) {
    char word[30] = {0};
    int i=0;
    bool erro = false;
    word[i++] = *c;
    updateCursor(c);
    if(debug)
        printf("\nDEBUG - Lexico - Trata digito\n");

    while(isDigit(*c) && i < 30 && isNotEndOfFile(*c)){
        word[i++] = *c;
        updateCursor(c);
    }
    // Exceed array limit for digits
    if(i == 30) {
        while(isDigit(*c) && isNotEndOfFile(*c))
            updateCursor(c);
        erro = true;
    }
    // Identifier starting with digits
    if(isIdentifier(*c)) {
        detectError(2,lineCount, '\0',ui);
        while(isIdentifier(*c) && isNotEndOfFile(*c))
            updateCursor(c);
        insertToken(tokenList, "Identificador inicio digito", "serro");
        erro = true;
    } else if(erro) {
        detectError(3,lineCount,'\0',ui);
        insertToken(tokenList, "Numero execede o limite", "serro");
    }
    flagUpdate = false;
    if(!erro)
        insertToken(tokenList, word, "snumero");
}

void treatAttribution(char *c, Token **tokenList) {
    if(debug)
        printf("\nDEBUG - Lexico - Trata atribuicao\n");
    updateCursor(c);
    if(isNotEndOfFile(*c) && *c == '=')
        insertToken(tokenList, ":=", "satribuicao");
    else {
        insertToken(tokenList, ":", "sdoispontos");
        flagUpdate = false;
    }
}

void treatArithmeticOperator(char *c, Token **tokenList,Ui::MainWindow *ui) {
    if(debug)
        printf("\nDEBUG - Lexico - Trata operador aritmetico\n");
    switch(*c){
        case '+':
            insertToken(tokenList, "+", "smais");
        break;
        case '-':
            insertToken(tokenList, "-", "smenos");
        break;
        case '*':
            insertToken(tokenList, "*", "smult");
        break;
            symbolError(*c, tokenList,ui);
    }
}

void treatRelationalOperator(char *c, Token **tokenList,Ui::MainWindow *ui) {
    if(debug)
        printf("\nDEBUG - Lexico - Trata operador relacional\n");
    switch(*c) {
        case '!':
            updateCursor(c);
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(tokenList, "!=", "sdif");
            else{
               symbolError('!', tokenList,ui);
               flagUpdate = false;
            }
            break;
        case '<':
            updateCursor(c);
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(tokenList, "<=", "smenorig");
            else{
                insertToken(tokenList, "<", "smenor");
                flagUpdate = false;
            }
            break;
        case '>':
            updateCursor(c);
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(tokenList,">=","smaiorig");
            else{
                insertToken(tokenList, ">", "smaior");
                flagUpdate = false;
            }
            break;
        case '=':
            insertToken(tokenList, "=", "sig");
            break;
        default:
            symbolError(*c, tokenList,ui);
    }
}

void treatPunctuation(char *c, Token **tokenList,Ui::MainWindow *ui) {
    if(debug)
        printf("\nDEBUG - Lexico - Pontuacao\n");
    switch(*c) {
        case ';':
            insertToken(tokenList, ";", "sponto_virgula");
            break;
        case ',':
            insertToken(tokenList, ",", "svirgula");
            break;
        case '(':
            insertToken(tokenList, "(", "sabre_parenteses");
            break;
        case ')':
            insertToken(tokenList, ")", "sfecha_parenteses");
            break;
        case '.':
            insertToken(tokenList, ".", "sponto");
            break;
        default:
            symbolError(*c, tokenList,ui);
    }
}

void identifyReservedWord(char *c, Token **tokenList,Ui::MainWindow *ui) {
    char word[30] = {0};
    int i = 0; // Contador para tamanho máximo do identificador

    if(debug)
        printf("\nDEBUG - Lexico - Identificar palavra reservada\n");
    word[i++] = *c;
    updateCursor(c);
    while(!isSpaceCode(*c) && isNotEndOfFile(*c) && i < 30 && isIdentifier(*c)) {
        word[i++] = *c;
        updateCursor(c);
    }
    // identifier Length Error
    if(i == 30) {
        detectError(4,lineCount, '\0',ui);
        while(isIdentifier(*c) && isNotEndOfFile(*c))
            updateCursor(c);
        insertToken(tokenList, "Identificador muito longo", "serro");
        return;
    }
    flagUpdate = false;
    if(isEqualString(word, "programa"))
        insertToken(tokenList, word, "sprograma");
    else if(isEqualString(word, "se"))
        insertToken(tokenList, word, "sse");
    else if(isEqualString(word, "entao"))
        insertToken(tokenList, word, "sentao");
    else if(isEqualString(word, "senao"))
        insertToken(tokenList, word, "ssenao");
    else if(isEqualString(word, "enquanto"))
        insertToken(tokenList, word, "senquanto");
    else if(isEqualString(word, "faca"))
        insertToken(tokenList, word, "sfaca");
    else if(isEqualString(word, "inicio"))
        insertToken(tokenList, word, "sinicio");
    else if(isEqualString(word, "fim"))
        insertToken(tokenList, word, "sfim");
    else if(isEqualString(word, "escreva"))
        insertToken(tokenList, word, "sescreva");
    else if(isEqualString(word, "leia"))
        insertToken(tokenList, word, "sleia");
    else if(isEqualString(word, "var"))
        insertToken(tokenList, word, "svar");
    else if(isEqualString(word, "inteiro"))
        insertToken(tokenList, word, "sinteiro");
    else if(isEqualString(word, "booleano"))
        insertToken(tokenList, word, "sbooleano");
    else if(isEqualString(word, "verdadeiro"))
        insertToken(tokenList, word, "sverdadeiro");
    else if(isEqualString(word, "falso"))
        insertToken(tokenList, word, "sfalso");
    else if(isEqualString(word, "procedimento"))
        insertToken(tokenList, word, "sprocedimento");
    else if(isEqualString(word, "funcao"))
        insertToken(tokenList, word, "sfuncao");
    else if(isEqualString(word, "div"))
        insertToken(tokenList, word, "sdiv");
    else if(isEqualString(word, "e"))
        insertToken(tokenList, word, "se");
    else if(isEqualString(word, "ou"))
        insertToken(tokenList, word, "sou");
    else if(isEqualString(word, "nao"))
        insertToken(tokenList, word, "snao");
    else
        insertToken(tokenList, word, "sidentificador");
}

void colectToken(char *c, Token **tokenList,Ui::MainWindow *ui) {
    if(debug)
        printf("\nDEBUG - Lexico - Coleta token: [ %c ]\n", *c);
    if(isDigit(*c))
        treatDigit(c, tokenList,ui);
    else if(isLetter(*c))
        identifyReservedWord(c, tokenList,ui);
    else if(*c == ':')
        treatAttribution(c, tokenList);
    else if(isAritmeticOperator(*c))
        treatArithmeticOperator(c, tokenList,ui);
    else if(isRelationalOperator(*c))
        treatRelationalOperator(c, tokenList,ui);
    else if(isPonctuation(*c))
        treatPunctuation(c, tokenList,ui);
    else
        symbolError(*c, tokenList,ui);
}

bool checkComment(char *c,Ui::MainWindow *ui) {
    if(*c == '{') {
        int openCommentLine = lineCount;
        updateCursor(c);
        while(*c != '}' && isNotEndOfFile(*c))
            updateCursor(c);
        if(!isNotEndOfFile(*c)){
            detectError(5,openCommentLine,'\0',ui);
            return false;
        }
        updateCursor(c);
        return true;
    }
    return false;
}

bool checkSpaces(char *c) {
    if(isSpaceCode(*c)) {
        updateCursor(c);
        while(isSpaceCode(*c) && isNotEndOfFile(*c))
            updateCursor(c);
        return true;
    }
    return false;
}

void getToken(char *c, Token **tokenList,Ui::MainWindow *ui) {
    while(isNotEndOfFile(*c) && *tokenList == NULL) {
        if(checkComment(c,ui) || checkSpaces(c))
            continue;
        else {
            colectToken(c, tokenList,ui);

            if(flagUpdate)
                updateCursor(c);
            else
                flagUpdate = true;
        }
    }
    if(!isNotEndOfFile(*c))
        insertToken(tokenList, "Fim de arquivo alcancado", "serro");
}
