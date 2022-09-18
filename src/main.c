#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexico.h"
#include "error.h"
#include "symbol.h"
#include "token.h"
#include "verifyChar.h"

// Control variables
Token *tokenList = NULL;
int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor
bool debug = false;

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
    int openCommentLine;
    updateCursor(&c);

    while(isNotEndOfFile(c)) {
        if(c == '{') {
            openCommentLine = lineCount;
            updateCursor(&c);
            while(c != '}' && isNotEndOfFile(c)) {
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
        }
        else {
            colectToken(&c, &tokenList, lineCount);

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
