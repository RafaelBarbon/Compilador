#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct instructionVector {
    char label[4];
    char instruction[8];
    char param1[4];
    char param2[4]; 
    struct instructionVector *next;
}InstructionVector;

void insertInstruction(InstructionVector **instructionVector, char inst[21]);

void printInstructions(InstructionVector *instructions);

// Function which collect all instructions from object to execute
void readInstructions(FILE *file, InstructionVector **instructionVector);

int toInt(char *number);

void freeInstructions(InstructionVector **instructionVector);

#endif