#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

// Biblioteca QT para interface grafica



// Control variables
Token *tokenList = NULL;
int lineCount = 0;
FILE *arq;

void updateCursor(char *c) {
    *c = getc(arq);
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


void identifyReservedWord(char *c) {
    char word[30] = {0};
    int i = 0; // Verificar o tamanho máximo do identificador
    if(!isLetter(c)) {
        printf("DEBUG: ERRO - comeco do identificador");
        exit(1);
    }
    word[i++] = c;
    updateCursor(&(*c));
    while(!isSpaceCode(*c) && *c != EOF && i < 30 && (isDigit(c) || isLetter(c) || c == '_')) {
        word[i++] = *c;
        updateCursor(&(*c));
    }
    // TODO: Adicionar lexema para a struct do token
    switch(word) {
        case "programa":
            insertToken(&tokenList, word, "sprograma");
            break;
        case "se":
            insertToken(&tokenList, word, "sse");
            break;
        case "entao":
            insertToken(&tokenList, word, "sentao");
            break;
        case "senao":
            insertToken(&tokenList, word, "ssenao");
            break;
        case "enquanto":
            insertToken(&tokenList, word, "senquanto");
            break;
        case "faca":
            insertToken(&tokenList, word, "sfaca");
            break;
        case "inicio":
            insertToken(&tokenList, word, "sinicio");
            break;
        case "fim":
            insertToken(&tokenList, word, "sfim");
            break;
        case "escreva":
            insertToken(&tokenList, word, "sescreva");
            break;
        case "leia":
            insertToken(&tokenList, word, "sleia");
            break;
        case "var":
            insertToken(&tokenList, word, "svar");
            break;
        case "inteiro":
            insertToken(&tokenList, word, "sinteiro");
            break;
        case "booleano":
            insertToken(&tokenList, word, "sbooleano");
            break;
        case "verdadeiro":
            insertToken(&tokenList, word, "sverdadeiro");
            break;
        case "falso":
            insertToken(&tokenList, word, "sfalso");
            break;
        case "procedimento":
            insertToken(&tokenList, word, "sprocedimento");
            break;
        case "funcao":
            insertToken(&tokenList, word, "sfuncao");
            break;
        case "div":
            insertToken(&tokenList, word, "sdiv");
            break;
        case "e":
            insertToken(&tokenList, word, "se");
            break;
        case "ou":
            insertToken(&tokenList, word, "sou");
            break;
        case "nao":
            insertToken(&tokenList, word, "snao");
            break;
        default: // Variable
            insertToken(&tokenList, word, "sidentificador");
    }
}

void colectToken(char *c) {
    identifyReservedWord(*c);
}

int main() {

    *arq = fopen("/testes/gera1.txt");
    if(!arq) {
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

    fclose(arq);

    return 0;
}

