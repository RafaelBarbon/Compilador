#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "symbol.h"
#include "token.h"
#include "verifyChar.h"

// Biblioteca QT para interface grafica



// Control variables
Token *tokenList = NULL;
int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor
bool debug = false;

void updateCursor(char *c) {
    *c = getc(sourceFile);
    if(debug)
        printf("%c ", *c);
}

void symbolError(char c) {
    char error[2] = {0};
    error[0] = c;
    if(debug)
        printf("\nDEBUG: ERROR %d\n", c);
    insertToken(&tokenList, error, "serro");
    detectError(1,lineCount,c);
}

void treatDigit(char *c){
    char word[30] = {0};
    int i=0;
    bool erro = false;
    word[i++] = *c;
    updateCursor(&(*c));

    while(isDigit(*c) && i < 30 && isNotEndOfFile(*c)){
        word[i++] = *c;
        updateCursor(&(*c));
    }
    // Exceed array limit for digits
    if(i == 30) {
        while(isDigit(*c) && isNotEndOfFile(*c))
            updateCursor(&(*c));
        erro = true;
    }
    // Identifier starting with digits
    if(isIdentifier(*c)) {
        detectError(2,lineCount, '\0');
        while(isIdentifier(*c) && isNotEndOfFile(*c))
            updateCursor(&(*c));
        insertToken(&tokenList, "Identificador inicio digito", "serro");
        erro = true;
    } else if(erro) {
        detectError(3,lineCount,'\0');
        insertToken(&tokenList, "Numero execede o limite", "serro");
    }
    flagUpdate = false;
    if(!erro)
        insertToken(&tokenList, word, "snumero");
}

void treatAttribution(char *c) {
    if(debug)
        printf("\nDEBUG - Trata atribuicao\n");
    updateCursor(&(*c));
    if(isNotEndOfFile(*c) && *c == '=')
        insertToken(&tokenList, ":=", "satribuicao");
    else {
        insertToken(&tokenList, ":", "sdoispontos");
        flagUpdate = false;
    }
}

void treatArithmeticOperator(char *c) {
    if(debug)
        printf("\nDEBUG - Trata operador aritmetico\n");
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
    if(debug)
        printf("\nDEBUG - Trata operador relacional\n");
    switch(*c) {
        case '!':
            updateCursor(&(*c));
            if(isNotEndOfFile(*c) && *c == '=')
                insertToken(&tokenList, "!=", "sdif");
            else{
               symbolError('!');
               flagUpdate = false;
            }
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
    if(debug)
        printf("\nDEBUG - Pontuacao\n");
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

    word[i++] = *c;
    updateCursor(&(*c));
    while(!isSpaceCode(*c, &lineCount) && isNotEndOfFile(*c) && i < 30 && isIdentifier(*c)) {
        word[i++] = *c;
        updateCursor(&(*c));
    }
    // identifier Length Error
    if(i == 30) {
        detectError(4, lineCount, '\0');
        while(isIdentifier(*c) && isNotEndOfFile(*c))
            updateCursor(&(*c));
        insertToken(&tokenList, "Identificador muito longo", "serro");
        return;
    }
    flagUpdate = false;
    if(debug)
        printf("Terminou de identificar a palavra");
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
    if(debug)
        printf("Teste coleta token:[%c]\n", *c);
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
        detectError(6, 0, '\0');
        exit(1);
    } else if(argc > 2 && strcmp(argv[2],"1") == 0) {
        debug = true;
        activateDebugToken();
        activateDebugSymbol();
    }

    sourceFile = fopen(argv[1], "r");

    if(!sourceFile) {
        detectError(7, 0, '\0');
        exit(1);
    }
    else if(debug)
        printf("DEBUG - Arquivo aberto com sucesso.\n");

    char c;
    int openCommentLine;
    updateCursor(&c);

    while(isNotEndOfFile(c)) {
        if(c == '{') {
            openCommentLine = lineCount;
            updateCursor(&c);
            while(c != '}' && isNotEndOfFile(c)) {
                if(c == '\n')
                    lineCount++;
                updateCursor(&c);
            }
            if(c == EOF){
                detectError(5,openCommentLine,'\0');
                break;
            }
            updateCursor(&c);
        } else if (isSpaceCode(c, &lineCount)) {
            updateCursor(&c);
            while(isSpaceCode(c, &lineCount) && isNotEndOfFile(c))
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

