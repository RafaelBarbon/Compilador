#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "verifyChar.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <sstream>
using namespace std;


// Find the specific error to be shown
char detectError(int errorCode, int line, char symbol, Ui::MainWindow *ui) {
    error = true;
    std::ostringstream ss;
    switch(errorCode) {
        case 1:
            ss << "\nErro L:"<< line << " Simbolo "<< symbol <<" nao encontrado.\n";
            printf("\nErro L%d: Simbolo \'%c\' nao encontrado.\n", line, symbol);
            break;
        case 2:
            ss << "\nErro L:"<< line << " Identificador iniciando com digitos.\n";
            printf("\nErro L%d: Identificador iniciando com digitos.\n", line);
            break;
        case 3:
            ss << "\nErro L:"<< line << " Numero informado excede o limite de 30 digitos.\n";
            printf("\nErro L%d: Numero informado excede o limite de 30 digitos.\n", line);
            break;
        case 4:
            ss << "\nErro L:"<< line << " Identificador excede o tamanho limite de 30 caracteres.\n";
            printf("\nErro L%d: Identificador excede o tamanho limite de 30 caracteres.\n", line);
            break;
        case 5:
            ss << "\nErro L:"<< line << " Comentario nao concluido.\n";
            printf("\nErro L%d: Comentario nao concluido.\n", line);
            break;
        case 6:
            ss << "\nErro! O nome do arquivo a ser analisado deve ser informado!";
            printf("\nErro! O nome do arquivo a ser analisado deve ser informado!");
            break;
        case 7:
            ss << "\nErro ao abrir o arquivo.\n";
            printf("\nErro ao abrir o arquivo.\n");
            break;
        case 8:
            ss << "\nErro L:"<< line << " Simbolo programa nao encontrado\n";
            printf("\nErro L%d: Simbolo programa nao encontrado\n", line);
            break;
        case 9:
            ss << "\nErro L:"<< line << " Nome do programa esperado nao encontrado\n";
            printf("\nErro L%d: Nome do programa esperado nao encontrado\n", line);
            break;
        case 10:
            ss << "\nErro L:"<< line << " Comando fora do escopo\n";
            printf("\nErro L%d: Comando fora do escopo\n", line);
            break;
        case 11:
            ss << "\nErro L:"<< line << " Nome da variavel esperado nao encontrado\n";
            printf("\nErro L%d: Nome da variavel esperado nao encontrado\n", line);
            break;
        case 12:
            ss << "\nErro L:"<< line << " Simbolo ',' ou ':' esperado nao encontrado\n";
            printf("\nErro L%d: Simbolo ',' ou ':' esperado nao encontrado\n", line);
            break;
        case 13:
            ss << "\nErro L:"<< line << " Tipo de argumento desconhecido\n";
            printf("\nErro L%d: Tipo de argumento desconhecido\n", line);
            break;
        case 14:
            ss << "\nErro L:"<< line << " Nome de procedimento esperado nao encontrado\n";
            printf("\nErro L%d: Nome de procedimento esperado nao encontrado\n", line);
            break;
        case 15:
            ss << "\nErro L:"<< line << " Nome de funcao esperado nao encontrado\n";
            printf("\nErro L%d: Nome de funcao esperado nao encontrado\n", line);
            break;
        case 16:
            ss << "\nErro L:"<< line << " Palavra reservada \"inicio\" nao encontrada\n";
            printf("\nErro L%d: Palavra reservada \"inicio\" nao encontrada\n", line);
            break;
        case 17:
            ss << "\nErro L:"<< line << " Expressao invalida\n";
            printf("\nErro L%d: Expressao invalida\n", line);
            break;
        case 18:
            ss << "\nErro L:"<< line << " Palavra reservada \"entao\" nao encontrada\n";
            printf("\nErro L%d: Palavra reservada \"entao\" nao encontrada\n", line);
            break;
        case 19:
            ss << "\nErro L:"<< line << " Palavra reservada \"faca\" nao encontrada\n";
            printf("\nErro L%d: Palavra reservada \"faca\" nao encontrada\n", line);
            break;
        case 20:
            ss << "\nErro L:"<< line << " Chamada de procedimento invalida\n";
            printf("\nErro L%d: Chamada de procedimento invalida\n", line);
            break;
        case 21:
            ss << "\nErro L:"<< line << " Variavel duplicada\n";
            printf("\nErro L%d: Variavel duplicada\n", line);
            break;
        case 22:
            ss << "\nErro L:"<< line << " Variavel nao declarada\n";
            printf("\nErro L%d: Variavel nao declarada\n", line);
            break;
        case 23:
            ss << "\nErro L:"<< line << " Funcao duplicada\n";
            printf("\nErro L%d: Funcao duplicada\n", line);
            break;
        case 24:
            ss << "\nErro L:"<< line << " Funcao nao declarada\n";
            printf("\nErro L%d: Funcao nao declarada\n", line);
            break;
        case 25:
            ss << "\nErro L:"<< line << " Procedimento nao declarado\n";
            printf("\nErro L%d: Procedimento nao declarado\n", line);
            break;
        case 26:
            ss << "\nErro L:"<< line << " Procedimento duplicado\n";
            printf("\nErro L%d: Procedimento duplicado\n", line);
            break;
        case 27:
            ss << "\nErro L:"<< line << " Expressao com conflito de tipo\n";
            printf("\nErro L%d: Expressao com conflito de tipo\n", line);
            break;
        case 28:
            ss << "\nErro L:"<< line << " Nao e posivel atribuir um valor a uma funcao fora de seu escopo\n";
            printf("\nErro L%d: Nao e posivel atribuir um valor a uma funcao fora de seu escopo\n", line);
            break;
        case 29:
            ss << "\nErro ao salvar o codigo gerado\n";
            printf("\nErro ao salvar o codigo gerado\n");
            break;
        default:
            ss << "\nErro desconhecido!\n";
            printf("\nErro desconhecido!\n");
    }
    std::string str = ss.str();
    ui->listWidget->addItem(str.c_str());

}
