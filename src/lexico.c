#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

// Biblioteca QT para interface grafica



// Control variables
Token *tokenList = NULL;
int lineCount = 0;
FILE *sourceFile;

void updateCursor(char *c) {
    *c = getc(sourceFile);
}

bool isSpaceCode(char c) {
    if(c == '\n')
        lineCount++;
    return c == ' ' || c == '\t' || c == '\n';
}

bool isDigit(char c) {
    return c >= 48 && c <= 57;
}

bool isLetter(char c) {
    return c >= 65 && c <= 90 || c >= 97 && c <= 122;
}

bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}


void identifyReservedWord(char *c) {
    char word[30] = {0};
    int i = 0; // Verificar o tamanho máximo do identificador
    if(!isLetter(*c)) {
        printf("DEBUG: ERRO - comeco do identificador");
        exit(1);
    }
    word[i++] = *c;
    updateCursor(&(*c));
    while(!isSpaceCode(*c) && *c != EOF && i < 30 && (isDigit(*c) || isLetter(*c) || *c == '_')) {
        word[i++] = *c;
        updateCursor(&(*c));
    }
    // TODO: Adicionar lexema para a struct do token
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
    identifyReservedWord(c);
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

    char c;
    updateCursor(&c);

    while(c != EOF) {
        if(c == '{') {
            updateCursor(&c);
            while(c != '}' && c != EOF)
                updateCursor(&c);
            updateCursor(&c);
        } else if (isSpaceCode(c)) {
            updateCursor(&c);
            while(isSpaceCode(c) && c != EOF)
                updateCursor(&c);
            updateCursor(&c);
        } else {
            colectToken(&c);
            updateCursor(&c);
        }
    }

    fclose(sourceFile);

    return 0;
}

