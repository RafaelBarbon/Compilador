#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc < 1) {
        printf("Erro! O nome do arquivo a ser analisado deve ser informado!");
        exit(1);
    }

    FILE *arq = fopen(argv[1], "r");

    if(!arq) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    for(char c = getc(arq); c != EOF; c = getc(arq)) {
        printf("%d ", c);
        if(c == 10)
            printf("\n");
    }

    fclose(arq);
}