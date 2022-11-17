#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(Stack **stack, int value){
    Stack *new = (Stack *)malloc(sizeof(Stack));
    new->value = value;
    new->next = *stack;
    *stack = new;
}

int pop(Stack **stack) {
    int ret;

    if((*stack) == NULL){
        return -1;
    }

    ret = (*stack)->value;

    Stack *old = (*stack);
    (*stack) = (*stack)->next;

    free(old);
    return ret;
}

void printStack(Stack *s) {
    Stack *pointer = s;
    printf("\n\nSTACK:\n");
    while(pointer != NULL) {
        printf(" %d ", pointer->value);
        pointer = pointer->next;
    }
}

void freeStack(Stack **st) {
    Stack *aux = (*st), *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    *st = aux;
}