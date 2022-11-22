#include <stdio.h>
#include <stdlib.h>
#include "verifyChar.h"

void generateAssembly(char *instruction, int param1, int param2){
    //TODO VERIFICAR ADDRESS PARA GERAR O ALLOC, DALOC
    //TODO SE FOR NULL COLOCAR "PARAM1 NULL"
    const char *code;
    FILE *outputFile;
    int result = fputs(code, outputFile);
    if(result == EOF)
        printf("\nErro ao salvar o código gerado");
    char line[20];

    if(isEqualString(instruction, "LDC     ")) {
        
    } else if(isEqualString(instruction, "LDV     ")) {

    } else if(isEqualString(instruction, "ADD     ")) {

    } else if(isEqualString(instruction, "SUB     ")) {

    } else if(isEqualString(instruction, "MULT    ")) {

    } else if(isEqualString(instruction, "DIVI    ")) {

    } else if(isEqualString(instruction, "INV     ")) {

    } else if(isEqualString(instruction, "AND     ")) {

    } else if(isEqualString(instruction, "OR      ")) {

    } else if(isEqualString(instruction, "NEG     ")) {

    } else if(isEqualString(instruction, "CME     ")) {

    } else if(isEqualString(instruction, "CMA     ")) {

    } else if(isEqualString(instruction, "CEQ     ")) {

    } else if(isEqualString(instruction, "CDIF    ")) {

    } else if(isEqualString(instruction, "CMEQ    ")) {

    } else if(isEqualString(instruction, "CMAQ    ")) {

    } else if(isEqualString(instruction, "STR     ")) {

    } else if(isEqualString(instruction, "JMP     ")) {

    } else if(isEqualString(instruction, "JMPF    ")) {

    } else if(isEqualString(instruction, "NULL    ")) {

    } else if(isEqualString(instruction, "RD      ")) {

    } else if(isEqualString(instruction, "PRN     ")) {

    } else if(isEqualString(instruction, "START   ")) {

    } else if(isEqualString(instruction, "ALLOC   ")) { // Verify double situations of alloc

    } else if(isEqualString(instruction, "DALLOC  ")) { // Verify double situations of dalloc

    } else if(isEqualString(instruction, "HLT     ")) {

    } else if(isEqualString(instruction, "CALL    ")) {

    } else if(isEqualString(instruction, "RETURN  ")) {

    } else if(isEqualString(instruction, "RETURNF ")) {

    } else if(isEqualString(instruction, "LDV     ")) {

    } else if(isEqualString(instruction, "ADD     ")) {

    } else if(isEqualString(instruction, "SUB     ")) {

    } else if(isEqualString(instruction, "MULT    ")) {

    } else if(isEqualString(instruction, "DIVI    ")) {

    } else if(isEqualString(instruction, "INV     ")) {

    } else if(isEqualString(instruction, "AND     ")) {

    } else if(isEqualString(instruction, "OR      ")) {

    } else if(isEqualString(instruction, "NEG     ")) {

    } else if(isEqualString(instruction, "CME     ")) {

    } else if(isEqualString(instruction, "CMA     ")) {

    } else if(isEqualString(instruction, "CEQ     ")) {

    } else if(isEqualString(instruction, "CDIF    ")) {

    } else if(isEqualString(instruction, "CMEQ    ")) {

    } else if(isEqualString(instruction, "CMAQ    ")) {

    } else if(isEqualString(instruction, "STR     ")) {

    } else if(isEqualString(instruction, "JMP     ")) {

    } else if(isEqualString(instruction, "JMPF    ")) {

    } else if(isEqualString(instruction, "NULL    ")) {

    } else if(isEqualString(instruction, "RD      ")) {

    } else if(isEqualString(instruction, "PRN     ")) {

    } else if(isEqualString(instruction, "START   ")) {

    } else if(isEqualString(instruction, "ALLOC   ")) { // Verify double situations of alloc

    } else if(isEqualString(instruction, "DALLOC  ")) { // Verify double situations of dalloc

    } else if(isEqualString(instruction, "HLT     ")) {

    } else if(isEqualString(instruction, "CALL    ")) {

    } else if(isEqualString(instruction, "RETURN  ")) {

    } else if(isEqualString(instruction, "RETURNF ")) {

    }
}

