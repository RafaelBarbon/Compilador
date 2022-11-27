#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"


void insertInstruction(InstructionVector *instructionVector, char inst[21], int *InstructionAddr) {
    InstructionVector novo;

    for(int i = 0, j = 0; i < 20; i++) {
        if(i == 4 || i == 12 || i == 16 || i == 20){
            j = 0;
        }
        if(i < 4)
            novo.label[j++] = inst[i];
        else if(i < 12)
            novo.instruction[j++] = inst[i];
        else if(i < 16)
            novo.param1[j++] = inst[i];
        else if(i < 20)
            novo.param2[j++] = inst[i];
    }
    novo.label[4] = '\0';
    novo.instruction[8] = '\0';
    novo.param1[4] = '\0';
    novo.param2[4] = '\0';
    instructionVector[(*InstructionAddr)] = novo;
    (*InstructionAddr) = *InstructionAddr + 1;
}

int toInt(char *number) {
    int result = 0;
    for(int i = 0; number[i] >= 48 && number[i] <= 57; i++) {
        result += number[i] - 48;
        result *= 10;
    }
    result /= 10;
    return result;
}

void printInstructions(InstructionVector *instructions, int size) {
    printf("INSTRUCTIONS\n");
    for(int i = 0; i < size; i++)
        printf("LABEL: %4.4s\t INST: %8.8s\tPARAM1: %4.4s\tPARAM2: %4.4s\n", instructions[i].label, instructions[i].instruction, instructions[i].param1, instructions[i].param2);
    printf("\n");
}


void readInstructions(FILE *file, InstructionVector *instructionVector, int *InstructionAddr) {
    char instruction[22];
    while(!feof(file)){
        fgets(instruction, 22, file);
        //printf("%s {SIZE = %d}", instruction, strlen(instruction));
        insertInstruction(instructionVector, instruction, InstructionAddr); 
    }
}

// void freeInstructions(InstructionVector **instructionVector) {
//     InstructionVector *aux = *instructionVector, *aux2 = NULL;
//     while(aux != NULL) {
//         aux2 = aux->next;
//         free(aux);
//         aux = aux2;
//     }
//     *instructionVector = NULL;
// }