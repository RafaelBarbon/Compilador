#include "stack.h"

void printStack(int *s, int addr) {
    printf("\nSTACK");
    while(addr != -1) {
       printf("\n%d", s[addr]);
       addr--;
    }
}

// void freeStack(Stack **st) {
//     Stack *aux = (*st), *aux2;
//     while(aux != NULL){
//         aux2 = aux->next;
//         free(aux);
//         aux = aux2;
//     }
//     *st = aux;
// }