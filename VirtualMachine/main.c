#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "instruction.h"
#include <stdbool.h>
#include <string.h>


bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}

int searchLabelIndex(InstructionVector *instructions, int numberOfInstructions, char *label){
    for(int i = 0; i < numberOfInstructions; i++){
        if(isEqualString(instructions[i].label, label))
            return i;
    }
    return -1;
}

void executeProgram(InstructionVector *instructions, int numberOfInstructions) {
    int stack[500] = {0}, addr = 0, aux, instructionAddr = 0, n, m; 

    while(instructionAddr != numberOfInstructions){
        printf("\n\nInstruction: %s %s %s %s", instructions[instructionAddr].label, instructions[instructionAddr].instruction, instructions[instructionAddr].param1, instructions[instructionAddr].param2);
        getchar();
        if(isEqualString(instructions[instructionAddr].instruction, "LDC     ")) {
            addr++;
            stack[addr] = toInt(instructions[instructionAddr].param1);
        } else if(isEqualString(instructions[instructionAddr].instruction, "LDV     ")) {
            addr++;
            stack[addr] = stack[toInt(instructions[instructionAddr].param1)];
        } else if(isEqualString(instructions[instructionAddr].instruction, "ADD     ")) {
            stack[addr-1] = stack[addr-1] + stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "SUB     ")) {
            stack[addr-1] = stack[addr-1] - stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "MULT    ")) {
            stack[addr-1] = stack[addr-1] * stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "DIVI    ")) {
            stack[addr-1] = stack[addr-1] / stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "INV     ")) {
            stack[addr] = - stack[addr];
        } else if(isEqualString(instructions[instructionAddr].instruction, "AND     ")) {
            if(stack[addr-1] == 1 && stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "OR      ")) {
            if(stack[addr-1] == 1 || stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "NEG     ")) {
            stack[addr] = 1 - stack[addr];
        } else if(isEqualString(instructions[instructionAddr].instruction, "CME     ")) {
            if(stack[addr-1] < stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMA     ")) {
            if(stack[addr-1] > stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CEQ     ")) {
            if(stack[addr-1] == stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CDIF    ")) {
            if(stack[addr-1] != stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMEQ    ")) {
            if(stack[addr-1] <= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMAQ    ")) {
            if(stack[addr-1] >= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "STR     ")) {
            stack[toInt(instructions[instructionAddr].param1)] = stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "JMP     ")) {
            aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
            instructionAddr = aux;//Instrução logo após o "LABEL NULL";
        } else if(isEqualString(instructions[instructionAddr].instruction, "JMPF    ")) {
            if(stack[addr] == 0){
                aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
                instructionAddr = aux;//Instrução logo após o "LABEL NULL";
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "RD      ")) {
            addr++;
            scanf("%d", &aux);
            stack[addr] = aux;
        } else if(isEqualString(instructions[instructionAddr].instruction, "PRN     ")) {
            printf("\n\n\n\n\n\n%d", stack[addr]);
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "START   ")) {
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "ALLOC   ")) {
            printf("\nANTES ALLOC\n\n");
            printStack(stack, addr);
            m = toInt(instructions[instructionAddr].param1);
            n = toInt(instructions[instructionAddr].param2);
            for(int k = 0; k < n; k++){
                addr++;
                stack[addr] = stack[m + k];
            }
            printf("\nDEPOIS ALLOC\n\n");
            printStack(stack, addr);
        } else if(isEqualString(instructions[instructionAddr].instruction, "DALLOC  ")) {
            printf("\nANTES DALLOC\n\n");
            printStack(stack, addr);
            m = toInt(instructions[instructionAddr].param1);
            n = toInt(instructions[instructionAddr].param2);
            for(int k = n - 1; k >= 0; k--){
                stack[m+k] = stack[addr];
                addr--;
            }
            printf("\nDEPOIS DALLOC\n\n");
            printStack(stack, addr);
        } else if(isEqualString(instructions[instructionAddr].instruction, "HLT     ")) {
            return;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CALL    ")) {
            addr++;
            stack[addr] = instructionAddr+1;
            aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
            instructionAddr = aux;//Instrução logo após o "LABEL NULL";
        } else if(isEqualString(instructions[instructionAddr].instruction, "RETURN  ")) {
            instructionAddr = (stack[addr] - 1); //Atualiza no final 
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "RETURNF ")) { //VERIFICAR SE Ë ESSE MESMO O RETORNO QUE PRECISA 
            instructionAddr = stack[addr] - 1;
            addr--;
        }
       
        instructionAddr++;
    }
}

int main() {
    FILE *sourceFile; 
    int instructionAddr = 0;
    sourceFile = fopen("AssemblyCode.obj", "r");

    if(!sourceFile) {
        printf("\nError! File could not be opened!\n");
        exit(1);
    }

    InstructionVector instructions[2048] = {0};
    // Stack *stack = NULL;
    
    readInstructions(sourceFile, instructions, &instructionAddr);

    //printInstructions(instructions, instructionAddr);

    executeProgram(instructions, instructionAddr);

    fclose(sourceFile);
    // freeInstructions(&instructions);
    // freeStack(&stack);

    return 0; 
}