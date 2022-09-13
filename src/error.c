#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void detectError(int errorCode, int line, char symbol) {
    switch(errorCode) {
        case 1:
            printf("\nErro L%d: Simbolo \'%c\' nao encontrado.\n", line, symbol);
            break;
        case 2:
            printf("\nErro L%d: identificador iniciando com digitos.\n", line);
            break;
        case 3:
            printf("\nErro L%d: numero informado excede o limite de 30 digitos.\n", line);
            break;
        case 4:
            printf("\nErro L%d: identificador excede o tamanho limite de 30 caracteres.\n", line);
            break;
        case 5:
            printf("\nErro L%d: Comentario nao concluido.\n", line);
            break;
        case 6:
            printf("\nErro! O nome do arquivo a ser analisado deve ser informado!");
            break;
        case 7:
            printf("\nErro ao abrir o arquivo.\n");
            break;
        default:
            printf("\nErro desconhecido!\n");
    }
}