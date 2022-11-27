#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct instructionVector {
    char label[5];
    char instruction[9];
    char param1[5];
    char param2[5]; 
}InstructionVector;

void insertInstruction(InstructionVector *instructionVector, char inst[21], int *InstructionAddr);

void printInstructions(InstructionVector *instructions, int size);

// Function which collect all instructions from object to execute
void readInstructions(FILE *file, InstructionVector *instructionVector, int *InstructionAddr);

int toInt(char *number);

void freeInstructions(InstructionVector **instructionVector);

#endif