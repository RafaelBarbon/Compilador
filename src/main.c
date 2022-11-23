#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexic.h"
#include "error.h"
#include "symbol.h"
#include "syntatic.h"
#include "token.h"
#include "verifyChar.h"

// Control variables
Token *tokenList = NULL; // Used to store built tokens from source file (lexic and syntatic)
Symbol *symbolList = NULL; // Used to store all identifiers (syntatic and semantic)
ExpressionAnalyzer *inFix = NULL; // Used to store the expressions (semantic)

int lineCount = 1; // Source file line counter
FILE *sourceFile, *outputCode;
bool flagUpdate = true; // Flag to allow cursor update to next character in source file (lexic)
bool debug = false; // Flag to allow logs in debug mode
bool insertArray = false; // Flag used to collect the expressions (attributions, conditionals and loops) (semantic)
bool error = false; // Flag to identify if any errors have occur
int label = 1; // Label for code generation
int address = 0; // Address 0 is used for store function return values

// Update the cursor in source file to get the next character
void updateCursor(char *c) {
    *c = getc(sourceFile);
    if(*c == '\n')
        lineCount++;
}

int main(int argc, char *argv[]) {
    if(argc < 1) { // Check if source file have been informed
        detectError(6, 0, '\0');
        exit(1);
    } else if(argc > 2 && strcmp(argv[2],"1") == 0) { // Check for debug mode activation
        debug = true;
        printf("\n\nWARN - Modo debug ativo\n\n");
    }

    sourceFile = fopen(argv[1], "r");

    if(!sourceFile) {
        detectError(7, 0, '\0');
        exit(1);
    } else if(debug)
        printf("DEBUG - Arquivo fonte aberto com sucesso.\n");

    outputCode = fopen("AssemblyCode.obj", "w");

    char c; // Used as cursor to get each character in source file

    updateCursor(&c);

    syntacticAnalyzer(&c, &tokenList, &symbolList, &inFix);

    fclose(sourceFile);
    fclose(outputCode);

    //printToken(tokenList);
    printf("\n%s\n\n", error ? "FALHOU" : "COMPILOU");


    freeToken(&tokenList);
    freeSymbol(&symbolList);

    return 0;
}
