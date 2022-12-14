#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "verifyChar.h"


// Find the specific error to be shown
void detectError(int errorCode, int line, char symbol) {
    error = true;
    switch(errorCode) {
        case 1:
            printf("\nErro L%d: Simbolo \'%c\' nao encontrado.\n", line, symbol);
            break;
        case 2:
            printf("\nErro L%d: Identificador iniciando com digitos.\n", line);
            break;
        case 3:
            printf("\nErro L%d: Numero informado excede o limite de %d digitos.\n", line, maxIdentifierLength);
            break;
        case 4:
            printf("\nErro L%d: Identificador excede o tamanho limite de %d caracteres.\n", line, maxIdentifierLength);
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
            printf("\nErro L%d: Simbolo ',' ou ':' esperado nao encontrado\n", line);
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
        case 20:
            printf("\nErro L%d: Chamada de procedimento invalida\n", line);
            break;
        case 21:
            printf("\nErro L%d: Variavel duplicada\n", line);
            break;
        case 22:
            printf("\nErro L%d: Variavel nao declarada\n", line);
            break;
        case 23:
            printf("\nErro L%d: Funcao duplicada\n", line);
            break;
        case 24:
            printf("\nErro L%d: Funcao nao declarada\n", line);
            break;
        case 25:
            printf("\nErro L%d: Procedimento nao declarado\n", line);
            break;
        case 26:
            printf("\nErro L%d: Procedimento duplicado\n", line);
            break;
        case 27:
            printf("\nErro L%d: Expressao com conflito de tipo\n", line);
            break;
        case 28:
            printf("\nErro L%d: Nao e posivel atribuir um valor a uma funcao fora de seu escopo\n", line);
            break;
        case 29:
            printf("\nErro ao salvar o codigo gerado\n");
            break;
        default:
            printf("\nErro desconhecido!\n");
    }
}
