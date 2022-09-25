#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void detectError(int errorCode, int line, char symbol) {
    switch(errorCode) {
        case 1:
            printf("\nErro L%d: Simbolo \'%c\' nao encontrado.\n", line, symbol);
            break;
        case 2:
            printf("\nErro L%d: Identificador iniciando com digitos.\n", line);
            break;
        case 3:
            printf("\nErro L%d: Numero informado excede o limite de 30 digitos.\n", line);
            break;
        case 4:
            printf("\nErro L%d: Identificador excede o tamanho limite de 30 caracteres.\n", line);
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
        case 8:
            printf("\nErro L%d: Simbolo programa nao encontrado\n", line);
            break;
        case 9:
            printf("\nErro L%d: Nome do programa esperado nao encontrado\n", line);
            break;
        case 10:
            printf("\nErro L%d: Comando fora do escopo\n", line);
            break;
        case 11:
            printf("\nErro L%d: Nome da variavel esperado nao encontrado\n", line);
            break;
        case 12:
            printf("\nErro L%d: Simbolo ',' ou ';' esperado nao encontrado\n", line);
            break;
        case 13:
            printf("\nErro L%d: Tipo de argumento desconhecido\n", line);
            break;
        case 14:
            printf("\nErro L%d: Nome de procedimento esperado nao encontrado\n", line);
            break;
        case 15:
            printf("\nErro L%d: Nome de funcao esperado nao encontrado\n", line);
            break;
        case 16:
            printf("\nErro L%d: Palavra reservada \"inicio\" nao encontrada\n", line);
            break;
        case 17:
            printf("\nErro L%d: Expressao invalida\n", line);
            break;
        case 18:
            printf("\nErro L%d: Palavra reservada \"entao\" nao encontrada\n", line);
            break;
        case 19:
            printf("\nErro L%d: Palavra reservada \"faca\" nao encontrada\n", line);
            break;
        default:
            printf("\nErro desconhecido!\n");
    }
}