#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

//Simple stack functions (Posfix conversion)
typedef struct Stack {
    int value;
    struct Stack *next;
}Stack;


void push(Stack **stack, int value);

int pop(Stack **stack);  

void printStack(Stack *s);

void freeStack(Stack **st);
#endif