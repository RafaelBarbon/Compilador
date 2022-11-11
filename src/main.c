#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexico.h"
#include "error.h"
#include "symbol.h"
#include "sintatico.h"
#include "token.h"
#include "verifyChar.h"
#include "sintatico.h"

// Control variables
Token *tokenList = NULL;
Symbol *symbolList = NULL;
ExpressionAnalyzer *inFix = NULL;

int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor
bool debug = false;
bool insertArray = false;
bool error = false;

void updateCursor(char *c) {
    *c = getc(sourceFile);
    if(*c == '\n')
        lineCount++;
}

int main(int argc, char *argv[]) {
    if(argc < 1) {
        detectError(6, 0, '\0');
        exit(1);
    } else if(argc > 2 && strcmp(argv[2],"1") == 0) {
        debug = true;
        printf("\n\nWARN - Modo debug ativo\n\n");
    }

    sourceFile = fopen(argv[1], "r");

    if(!sourceFile) {
        detectError(7, 0, '\0');
        exit(1);
    }
    else if(debug)
        printf("DEBUG - Arquivo aberto com sucesso.\n");

    char c;

    updateCursor(&c);

    syntacticAnalyzer(&c, &tokenList, &symbolList, &inFix);
    char ret[30] = {0};

    // TODO implementar no sintático o PosFix
    // TODO Fazer a análise da expressão posFix
    // TODO Geração de código

    fclose(sourceFile);

    //printToken(tokenList);
    printf("\n\n%s\n\n", error ? "FALHOU" : "COMPILOU");


    freeToken(&tokenList);
    freeSymbol(&symbolList);

    return 0;
}
