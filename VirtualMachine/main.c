#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "instruction.h"
#include <stdbool.h>


bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}

void executeProgram(InstructionVector *instructions) {
    int stack[500] = 0, addr = 1, aux; 

    while(instructions != NULL){

        if(isEqualString(instructions->instruction, "LDC     ")) {
            addr++;
            stack[addr] = toInt(instructions->param1);
        } else if(isEqualString(instructions->instruction, "LDV     ")) {
            addr++;
            stack[addr] = stack[toInt(instructions->param1)];
        } else if(isEqualString(instructions->instruction, "ADD     ")) {
            stack[addr-1] = stack[addr-1] + stack[addr];
            addr--;
        } else if(isEqualString(instructions->instruction, "SUB     ")) {
            stack[addr-1] = stack[addr-1] - stack[addr];
            addr--;
        } else if(isEqualString(instructions->instruction, "MULT    ")) {
            stack[addr-1] = stack[addr-1] * stack[addr];
            addr--;
        } else if(isEqualString(instructions->instruction, "DIVI    ")) {
            stack[addr-1] = stack[addr-1] / stack[addr];
            addr--;
        } else if(isEqualString(instructions->instruction, "INV     ")) {
            stack[addr] = - stack[addr];
        } else if(isEqualString(instructions->instruction, "AND     ")) {
            if(stack[addr-1] == 1 && stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "OR      ")) {
            if(stack[addr-1] == 1 || stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "NEG     ")) {
            stack[addr] = 1 - stack[addr];
        } else if(isEqualString(instructions->instruction, "CME     ")) {
            if(stack[addr-1] < stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "CMA     ")) {
            if(stack[addr-1] > stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "CEQ     ")) {
            if(stack[addr-1] == stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "CDIF    ")) {
            if(stack[addr-1] != stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "CMEQ    ")) {
            if(stack[addr-1] <= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "CMAQ    ")) {
            if(stack[addr-1] >= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions->instruction, "STR     ")) {
            stack[toInt(instructions->param1)] = stack[addr];
            addr--;
        } else if(isEqualString(instructions->instruction, "JMP     ")) {
            
        } else if(isEqualString(instructions->instruction, "JMPF    ")) {

        } else if(isEqualString(instructions->instruction, "RD      ")) {
            addr++;
            scanf("%d", &aux);
            stack[addr] = aux;
        } else if(isEqualString(instructions->instruction, "PRN     ")) {
            printf("\n%d", stack[addr]);
            addr--;
        } else if(isEqualString(instructions->instruction, "START   ")) {
            addr--;
        } else if(isEqualString(instructions->instruction, "ALLOC   ")) {

        } else if(isEqualString(instructions->instruction, "DALLOC  ")) {

        } else if(isEqualString(instructions->instruction, "HLT     ")) {
            return;
        } else if(isEqualString(instructions->instruction, "CALL    ")) {

        } else if(isEqualString(instructions->instruction, "RETURN  ")) {
            
        } else if(isEqualString(instructions->instruction, "RETURNF ")) {

        }
        instructions = instructions->next;
    }
}

int main() {
    FILE *sourceFile; 
    sourceFile = fopen("AssemblyCode.obj", "r");

    if(!sourceFile) {
        printf("\nError! File could not be opened!\n");
        exit(1);
    }

    InstructionVector *instructions = NULL;
    Stack *stack = NULL;
    
    readInstructions(sourceFile, &instructions);

    printInstructions(instructions);

    //executeProgram(instructions);

    fclose(sourceFile);
    freeInstructions(&instructions);
    freeStack(&stack);

    return 0; 
}