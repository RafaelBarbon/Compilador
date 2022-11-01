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
int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor
bool debug = false;
bool insertArray = false;

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

    //syntacticAnalyzer(&c, &tokenList, &symbolList);
    char ret[30] = {0};

    //VVAR+VRAFA
    // TODO - atribuir o nome e os operadores no infix para ser analisado no posFix, colocar espaços após o nome de var para não ocorrer de: Z<0 = VzR>N0
    //TODO - Tratar Unário 
    // TODO implementar no sintático

    printf("%s",convertPosFix("(V+N*N/(N+V)R(V*V+N))&(VRN)",27, ret));

    fclose(sourceFile);

    //printToken(tokenList);
    printf("\n\nCOMPILOU\n\n");

    freeToken(&tokenList);
    freeSymbol(&symbolList);

    return 0;
}
