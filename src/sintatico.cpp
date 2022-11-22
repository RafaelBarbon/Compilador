#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexico.h"
#include "error.h"
#include "symbol.h"
#include "token.h"
#include "verifyChar.h"
#include "sintatico.h"

void errorSintax(Token **token, int errorCode, char symbol) {
    freeToken(token);
    detectError(errorCode,lineCount, symbol);
    fclose(sourceFile);
    exit(1);
}

bool verifyRelationalSymbol(Token *token) {
    return isEqualString(token->symbol, "smaior") || isEqualString(token->symbol, "smaiorig") ||
           isEqualString(token->symbol, "sig") || isEqualString(token->symbol, "smenor") ||
           isEqualString(token->symbol, "smenorig") || isEqualString(token->symbol, "sdif");
}

void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix) {
    freeToken(token);
    getToken(c, token);
    //printf("\n%s\n", (*token)->lexeme);
    //Used on expression analyzer
    if(insertArray) {
        //Se for func ou var pesquisa na tabela de simbolos pra pega o tipo
        //printf("\nTOKEN_TYPE_INSERT - %s - %s\n", (*token)->lexeme, (*token)->symbol);
        if(isEqualString((*token)->symbol, "sidentificador")){
            SymbolType type = searchVarFuncType(symbolList, (*token)->lexeme);
            //printf("\nswitch %s - %s\n",symbolTypeToString(type),(*token)->lexeme);
            //getchar();
            switch(type) {
                case FuncBooleana:
                    insertInFix(InFix, (*token)->lexeme, FuncBool);
                    break;
                case FuncInteira:
                    insertInFix(InFix, (*token)->lexeme, FuncInt);
                    break;
                case VarInteira:
                    insertInFix(InFix, (*token)->lexeme, VarInt);
                    break;
                case VarBooleana:
                    insertInFix(InFix, (*token)->lexeme, VarBool);
                    break;
                default:
                    //printf("\nDeu errado o switch\n");
                    break;
            }
        } else if(verifyRelationalSymbol((*token)))
            insertInFix(InFix, (*token)->lexeme, Rel);
        else if(isEqualString((*token)->symbol, "smais") || isEqualString((*token)->symbol, "smenos"))
            insertInFix(InFix, (*token)->lexeme, OpMaisMenos);
        else if(isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv"))
            insertInFix(InFix, (*token)->lexeme, OpMultDiv);
        else if(isEqualString((*token)->symbol, "snumero"))
            insertInFix(InFix, (*token)->lexeme, Inteiro);
        else if(isEqualString((*token)->symbol, "snao"))
            insertInFix(InFix, (*token)->lexeme, Nao);
        else if(isEqualString((*token)->symbol, "se"))
            insertInFix(InFix, (*token)->lexeme, E);
        else if(isEqualString((*token)->symbol, "sou"))
            insertInFix(InFix, (*token)->lexeme, OU);
        else if(isEqualString((*token)->symbol, "sabre_parenteses"))
            insertInFix(InFix, (*token)->lexeme, AbreP);
        else if(isEqualString((*token)->symbol, "sfecha_parenteses")) {
            //printf("\n%d\n", *InFix == NULL ? 0:1);

            insertInFix(InFix, (*token)->lexeme, FechaP);
            //printf("\n\nO que vai colocar no print?\n\n");
            //getchar();
        }
        else if(isEqualString((*token)->symbol, "sverdadeiro"))
            insertInFix(InFix, (*token)->lexeme, Booleano);
        else if(isEqualString((*token)->symbol, "sfalso"))
            insertInFix(InFix, (*token)->lexeme, Booleano);
    }
}

void analyzeExpressionType(ExpressionAnalyzer **expression, LexemeType expectedType) {
    ExpressionAnalyzer *exp = (*expression), Op1, Op2, ant;
    bool FirstNao = false;
    simpleStack *stack = NULL;
    ExpressionAnalyzer *typeResult = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));
    strcpy(typeResult->lexeme, "RESULT");

    while(exp != NULL) {
        if(exp->type == OpMultDiv || exp->type == OpMaisMenos){
            // Coleta os dois elementos no topo da pilha (pop) e realiza a verificação do tipo inteiro para realizar push do tipo final
            Op1 = pop(&stack);
            Op2 = pop(&stack);
            if((Op1.type == Inteiro || Op1.type == FuncInt) && (Op2.type == Inteiro || Op2.type == FuncInt)){
                typeResult->type = Inteiro;
                push(&stack, typeResult);
            }else{
                detectError(27, lineCount,'\0');
                free(typeResult);
                printf("\nT1_Type: %d   -   T2_Type: %d", Op1.type, Op2.type);
                return;
            }
        } else if(exp->type == E || exp->type == OU) {
            // Coleta os dois elementos no topo da pilha (pop) e realiza a verificação do tipo booleano para realizar push do tipo final
            Op1 = pop(&stack);
            Op2 = pop(&stack);

            if((Op1.type ==  Booleano || Op1.type == FuncBool) && (Op2.type == Booleano || Op2.type == FuncBool)){
                typeResult->type = Booleano;
                push(&stack, typeResult);
            }else{
                detectError(27, lineCount,'\0');
                free(typeResult);
                printf("\nT1_Type: %d   -   T2_Type: %d", Op1.type, Op2.type);
                return;
            }
        } else if(exp->type == UnarioN || exp->type == UnarioP || exp->type == Nao) {
            // Verifica unário (+-nao) e o tipo do próximo elemento, colocando na pilha o tipo do próximo elemento
            if(exp->next != NULL) {
                ant = pop(&stack);
                printf("\nPOP - %s", ant.lexeme);
                if(exp->type == Nao){
                    // if(isEqualString(ant.lexeme, "VAZIA")){//Primeiro é uma negação{
                    // 	printf("\nNao ta entrano aqui\n");
                    // 	FirstNao = true;
                    // 	strcpy(typeResult->lexeme, "NAO_FIRST");
                    // 	typeResult->type = Nao;
                    // 	push(&stack, typeResult);
                    // }
                    // if(ant.type == Nao){
                    // 	//Ja fez POP (Anula o Não anterior)
                    // }
                    if(ant.type == Booleano || ant.type == FuncBool) {
                        typeResult->type = Booleano;
                        push(&stack, typeResult);
                        //aux = aux->next->next;
                        //continue;
                    } else {
                        detectError(27, lineCount,'\0');
                        free(typeResult);
                        printf("\nTBool_Type: %s" ,ant.lexeme);
                        return;
                    }
                } else if(ant.type == Inteiro || ant.type == FuncInt) {
                    typeResult->type = Inteiro;
                    push(&stack, typeResult);
                    //aux = aux->next->next;
                    //continue;
                } else {
                    detectError(27, lineCount,'\0');
                    free(typeResult);
                    printf("\nTInt_Type: %d" ,ant.type);
                    return;
                }
            }
        }else if(exp->type == Rel){ //Relacional (Pode ser inteiro ou boleano )
            // Coleta os dois elementos no topo da pilha (pop) e realiza a verificação do tipo booleano para realizar push do tipo final
            Op1 = pop(&stack);
            Op2 = pop(&stack);

            if(((Op1.type == Inteiro ||  Op1.type == FuncInt) && (Op2.type == Inteiro || Op2.type == FuncInt)) || ((Op1.type == Booleano ||  Op1.type == FuncBool) && (Op2.type == Booleano || Op2.type == FuncBool))){
                typeResult->type = Booleano;
                push(&stack, typeResult);
            }else{
                detectError(27, lineCount,'\0');
                free(typeResult);
                printf("\nT1_Type: %d   -   T2_Type: %d", Op1.type, Op2.type);
                return;
            }
        }else {
            // Variáveis e constantes
            push(&stack, exp);
        }
        //ant = exp;
        exp = exp->next;
    }
    // No final deve haver a verificação do tipo do elemento restante, se houver mais de um: erro
    //printSimpleStack(stack);
    //getchar();
    Op1 = pop(&stack);
    if(stack != NULL){//ainda tem operandos na pilhar (A expressão não esta correta)
        //printf("\nTipo do pop: %d FirstNao: %s\n", Op1.type, FirstNao ? "TRUE":"FALSE");
        // if(FirstNao && Op1.type == Booleano) { //Tem operadores NAO no Resto da Pilha
        // 	for(simpleStack *i = stack; i != NULL; i = i->next){
        // 	 	if(i->c->type != NaoFirst)
        // 	 		detectError(27, lineCount,'\0');
        // 	}
        // } else
        detectError(27, lineCount,'\0');
        freeSimpleStack(&stack);
    }else if(Op1.type != expectedType){
        detectError(17, lineCount,'\0');
    }

    free(typeResult);
    //if(debug)
        printf("\nType %d - Expected %d", Op1.type,  expectedType);
}

void semanticAnalyzer(ExpressionAnalyzer **inFix, LexemeType type) {
    ExpressionAnalyzer *posFix = NULL;
    ExpressionAnalyzer *analyze = NULL;
    //if(debug)
        printExpression(*inFix, "IN_FIX", false);
    //printf("\nSEGMENTATION?\n");
    //getchar();
    convertPosFix(inFix, &posFix);
    //if(debug)
    printExpression(posFix, "POS_FIX", false);
    //printExpression(posFix, "TYPE_POSFIX", true);
    copyExpression(&analyze, posFix);
    if(debug)
        printExpression(analyze, "COPY_POS_FIX", false);
    //printf("\nSEGMENTATION?\n");
    //getchar();
    analyzeExpressionType(&analyze, type);
    //generateExpressionCode(posFix);
    //printExpression(*inFix);

    freeExpression(inFix);
    freeExpression(&posFix);
    freeExpression(&analyze);
}

void syntacticAnalyzer(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    //int rotulo = 1;
    getNewToken(c, token, *symbol, inFix);
    if (isEqualString((*token)->symbol, "sprograma")) {
        getNewToken(c, token, *symbol, inFix);
        if (isEqualString((*token)->symbol, "sidentificador")) {
            insertSymbol(symbol, (*token)->lexeme, false, Programa, 0);
            getNewToken(c, token, *symbol, inFix);
            if (isEqualString((*token)->symbol, "sponto_virgula")) {
                analyzeBlock(c, token, symbol, inFix);
                if (isEqualString((*token)->symbol, "sponto")) {
                    if (!isNotEndOfFile(*c) || checkComment(c) || checkSpaces(c)) {
                        if(debug)
                            printf("\nDEBUG - Sintatico - Analisando comentario no final do arquivo\n");
                    } else
                        errorSintax(token, 10, '\0');
                } else
                    errorSintax(token, 1, '.');
            } else
                errorSintax(token, 1, ';');
        } else
            errorSintax(token, 9, '\0');
    } else
        errorSintax(token, 8, '\0');
}

// bloco
void analyzeBlock(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa bloco\n");
    getNewToken(c, token, *symbol, inFix);
    analyzeEtVariables(c, token, symbol);
    analyzeSubroutines(c, token, symbol, inFix);
    analyzeCommands(c, token, symbol, inFix);
}

// declaração de variáveis
void analyzeEtVariables(char *c, Token **token, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa et variaveis\n");
    if (isEqualString((*token)->symbol, "svar")) {
        getNewToken(c, token, *symbol, NULL);
        if (isEqualString((*token)->symbol, "sidentificador")) {
            while (isEqualString((*token)->symbol, "sidentificador")) {
                analyzeVariables(c, token, symbol);
                if (isEqualString((*token)->symbol, "sponto_virgula"))
                    getNewToken(c, token, *symbol, NULL);
                else errorSintax(token, 1,';');
            }
        } else
            errorSintax(token, 11, '\0');
    }
}

// declaração de variáveis
void analyzeVariables(char *c, Token **token, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa variaveis\n");
    do {
        if (isEqualString((*token)->symbol, "sidentificador")) {
            if (!searchDuplicity(*symbol, (*token)->lexeme)) {
                insertSymbol(symbol, (*token)->lexeme, false, Var, 0);
                getNewToken(c, token, *symbol, NULL);
                if (isEqualString((*token)->symbol,"svirgula") || isEqualString((*token)->symbol,"sdoispontos")) {
                    if (isEqualString((*token)->symbol, "svirgula")) {
                        getNewToken(c, token, *symbol, NULL);
                        if (isEqualString((*token)->symbol,"sdoispontos"))
                            errorSintax(token, 11, '\0');
                    }
                } else errorSintax(token, 12, '\0');
            } else errorSintax(token,21,'\0');
        } else errorSintax(token, 11, '\0');

    } while (!isEqualString((*token)->symbol, "sdoispontos"));
    getNewToken(c, token, *symbol, NULL);
    analyzeType(c, token, symbol);
}

// tipo
void analyzeType(char *c, Token **token, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa tipo\n");
    if (isEqualString((*token)->symbol, "sinteiro") || isEqualString((*token)->symbol, "sbooleano")){
        putType(symbol,isEqualString((*token)->symbol, "sinteiro") ? VarInteira : VarBooleana);
        getNewToken(c, token, *symbol, NULL);
    } else errorSintax(token, 13, '\0');
}

// comandos
void analyzeCommands(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa comandos\n");
    if (isEqualString((*token)->symbol, "sinicio")) {
        getNewToken(c, token, *symbol, inFix);
        analyzeSimpleCommand(c, token, symbol, inFix);
        while (!isEqualString((*token)->symbol, "sfim")) {
            if (isEqualString((*token)->symbol, "sponto_virgula")) {
                getNewToken(c, token, *symbol, inFix);
                if (!isEqualString((*token)->symbol, "sfim")) {
                    analyzeSimpleCommand(c, token, symbol, inFix);
                }
            } else errorSintax(token, 1, ';');
        }
        getNewToken(c, token, *symbol, inFix);
    } else errorSintax(token, 16, '\0');
}

// comandos
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa comando simples\n");
    if(isEqualString((*token)->symbol, "sidentificador"))
        analyzeAttributionProcedureCall(c, token, symbol, inFix);
    else if(isEqualString((*token)->symbol, "sse"))
        analyzeConditional(c, token, symbol, inFix);
    else if(isEqualString((*token)->symbol, "senquanto"))
        analyzeWhile(c, token, symbol, inFix);
    else if(isEqualString((*token)->symbol, "sleia"))
        analyzeRead(c, token, symbol);
    else if(isEqualString((*token)->symbol, "sescreva"))
        analyzeWrite(c, token, symbol);
    else
        analyzeCommands(c, token, symbol, inFix);
}

// atribuição_chprocedimento
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa atribuicao chamada procedimento\n");
    char nameVarOrProcedure[30];
    strcpy(nameVarOrProcedure, (*token)->lexeme);
    getNewToken(c, token, *symbol, inFix);
    if (isEqualString((*token)->symbol, "satribuicao"))
        analyzeAttribution(c, token, (*symbol), inFix, nameVarOrProcedure);
    else
        procedureCall(c, token, nameVarOrProcedure, symbol);
}

void analyzeAttribution(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix, char *name) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa atribuicao\n");

    insertArray = true;
    getNewToken(c, token, symbol, inFix);

    analyzeExpression(c, token, symbol, inFix);

    //printf("\nToken in buffer after getti TOKEN: %s\n", (*token)->lexeme);
    insertArray = false;
    LexemeType type = getVarType(symbol, name);
    if(type == Rel)
        errorSintax(token,28,'\0');
    semanticAnalyzer(inFix, type);

    // Verificar chamada de função e identificador seguido de expressões aritméticas e/ou booleana, terminando por ;
}

void procedureCall(char *c, Token **token, char *nameProcedure, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Chamada procedimento\n");

    if(isEqualString((*token)->symbol, "sponto_virgula") || isEqualString((*token)->symbol, "sfim") || isEqualString((*token)->symbol, "ssenao")) { //Pode chamar no ultimo comando ou logo após um condicional com um comando comando so e o senao
        if(verifyProcedureDeclaration((*symbol), nameProcedure)) {
            // Geração de código
        } else errorSintax(token, 25, '\0');
    } else errorSintax(token, 20, '\0');
}

void analyzeFunctionCall(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa chamada funcao\n");
    getNewToken(c, token, symbol, inFix);
}

// comando leitura
void analyzeRead(char *c, Token **token, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa leia\n");
    getNewToken(c, token, NULL, NULL);
    if (isEqualString((*token)->symbol, "sabre_parenteses")) {
        getNewToken(c, token, *symbol, NULL);
        if (isEqualString((*token)->symbol, "sidentificador")) {
            if (verifyVarDeclaration(*symbol, (*token)->lexeme)){ // Pesquisa a declaração da variável e se é inteira
                getNewToken(c, token, *symbol, NULL);
                if (isEqualString((*token)->symbol,"sfecha_parenteses"))
                    getNewToken(c, token, *symbol, NULL);
                else errorSintax(token, 1, ')');
            } else errorSintax(token,22,'\0');
        } else errorSintax(token, 11, '\0');
    } else errorSintax(token, 1, '(');
}

// comando escrita
void analyzeWrite(char *c, Token **token, Symbol **symbol) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa escreva\n");
    getNewToken(c, token, *symbol, NULL);
    if (isEqualString((*token)->symbol, "sabre_parenteses")) {
        getNewToken(c, token, NULL, NULL);
        if (isEqualString((*token)->symbol, "sidentificador")) {
            if (verifyVarDeclaration(*symbol, (*token)->lexeme)){// Pesquisa declaração de função e variável do tipo inteiro /////// TODO escreva é só p/ variáveis
                getNewToken(c, token, NULL, NULL);
                if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
                    getNewToken(c, token, NULL, NULL);
                } else errorSintax(token, 1, ')');
            } else errorSintax(token,22,'\0');
        } else errorSintax(token, 11, '\0');
    } else errorSintax(token, 1, '(');
}

// comando repetição
void analyzeWhile(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix/*, int rotulo*/) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa enquanto\n");
    //int auxrot1 = rutulo,auxrot2;
    //Gera(rotulo,NULL,' ',' ')
    //while (Gera(auxrot2, NULL, auxrot1, ' ') == true) {
        //rotulo++;
        insertArray = true;
        getNewToken(c, token, *symbol, inFix);
        analyzeExpression(c, token, (*symbol), inFix);
        insertArray = false;
        semanticAnalyzer(inFix, Booleano);
        if (isEqualString((*token)->symbol, "sfaca")) {
            //auxrot2 = rotulo;
            //if (Gera(' ', JMPF, rotulo, ' ') == true)
                //rotulo = rotulo + 1;
            getNewToken(c, token, *symbol, inFix);
            analyzeSimpleCommand(c, token, symbol, inFix);
            // Gera(' ',JMP,auxrot1,' ')  {retorna início loop}
            // if(Gera(auxrot2,NULL,' ', ' ')  == false)
            //    exit;
        } else
            errorSintax(token, 19, '\0');
    //}
}

// comando condicional
void analyzeConditional(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa Se\n");
    insertArray = true;
    getNewToken(c, token, *symbol, inFix);
    analyzeExpression(c, token, (*symbol), inFix);
    insertArray = false;
    semanticAnalyzer(inFix, Booleano);
    if (isEqualString((*token)->symbol, "sentao")) {
        getNewToken(c, token, *symbol, inFix);
        analyzeSimpleCommand(c, token, symbol, inFix);
        if (isEqualString((*token)->symbol, "ssenao")) {
            getNewToken(c, token, *symbol, inFix);
            analyzeSimpleCommand(c, token, symbol, inFix);
        }
    } else
        errorSintax(token, 18, '\0');
}

// etapa de declaração de sub-rotinas
void analyzeSubroutines(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix/*, int rotulo*/) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa Subrotina\n");
    //int auxrot, flag = 0;
    //if (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
        //auxrot = rotulo;
        //if (GERA(' ', JMP, rotulo, ' ') == true)
            //exit;
        //rotulo++;
        //flag = 1;
    //} else errorSintax(token,1,lineCount,'\0');

    while (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
        if (isEqualString((*token)->symbol, "sprocedimento"))
            analyzeProcedureDeclaration(c, token, symbol, inFix);
        else
            analyzeFunctionDeclaration(c, token, symbol, inFix);
        if (isEqualString((*token)->symbol, "sponto_virgula")) {
            getNewToken(c, token, *symbol, inFix);
        }else
            errorSintax(token, 1, ';');
    }
    //if (flag = 1)
        //if (Gera(auxrot, NULL, ' ', ' ') == true)
            //inicio_principal();
}

// declaração de procedimento
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa declaracao procedimento\n");
    getNewToken(c, token, *symbol, inFix);
    //nivel = "L" // marca ou novo galho
    if (isEqualString((*token)->symbol, "sidentificador")) {
        if (!verifyProcedureFunctionDuplicity(*symbol, (*token)->lexeme)){// Pesquisa se o procedimento não existe
            insertSymbol(symbol, (*token)->lexeme, true, Procedimento, 0); // guarda na TabSimb
            //Gera(rotulo, NULL, ' ', ' ');								// CALL irá buscar este rotulo na TabSimb}
            //rotulo++;
            getNewToken(c, token, *symbol, inFix);
            if (isEqualString((*token)->symbol, "sponto_virgula"))
                analyzeBlock(c, token, symbol, inFix);
            else errorSintax(token, 1, ';');
        } else errorSintax(token, 26, '\0');
    } else errorSintax(token, 14, '\0');
    //printf("\n\nANTEEESS DE DESMPILHAR O NIVEL\n");
    //printStack((*symbol));
    unStack(symbol);// DESEMPILHA OU VOLTA NÍVEL();
    //printf("\n\nDEPOIIISS DE DESMPILHAR O NIVEL\n");
    //printStack((*symbol));
}

// declaração de função
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa declaracao Funcao\n");
    getNewToken(c, token, *symbol, inFix);
    if (isEqualString((*token)->symbol, "sidentificador")) {
        if (!verifyProcedureFunctionDuplicity(*symbol, (*token)->lexeme)){// Verifica se a função não foi declarada
            insertSymbol(symbol, (*token)->lexeme, true, Func, 0);
            getNewToken(c, token, *symbol, inFix);
            if (isEqualString((*token)->symbol, "sdoispontos")) {
                getNewToken(c, token, *symbol, inFix);
                if (isEqualString((*token)->symbol, "sinteiro") || isEqualString((*token)->symbol, "sbooleano")){
                    putTypeFunc(symbol,isEqualString((*token)->symbol, "sinteiro") ? FuncInteira : FuncBooleana);//TABSIMB[pc].tipo = "funcao inteiro";//TABSIMB[pc].tipo = "funcao booleana";
                    getNewToken(c, token, *symbol, inFix);
                    if (isEqualString((*token)->symbol, "sponto_virgula"))
                        analyzeBlock(c, token, symbol, inFix);
                } else
                    errorSintax(token, 13, '\0');
            } else
                errorSintax(token, 1, ':');
        } else
            errorSintax(token,23,'\0');
    } else errorSintax(token, 15, '\0');
    //printf("\n\nANTEEESS DE DESMPILHAR O NIVEL\n");
    //printStack((*symbol));
    unStack(symbol);// DESEMPILHA OU VOLTA NÍVEL();
    // printf("\n\nDEPOIIISS DE DESMPILHAR O NIVEL\n");
    // printStack((*symbol));
}

// expressão
void analyzeExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa Expressao\n");
    analyzeSimpleExpression(c, token, symbol, inFix);
    if (verifyRelationalSymbol(*token)) {
        getNewToken(c, token, symbol, inFix); //Adicionar no InFix
        analyzeSimpleExpression(c, token, symbol, inFix);
    }
}

// expressão simples
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa Expressao Simples\n");
    if (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos")){
        getNewToken(c, token, symbol, inFix); //Adicionar no InFix
    }
    analyzeTerm(c, token, symbol, inFix);
    while (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos") || isEqualString((*token)->symbol,"sou")) {
        getNewToken(c, token, symbol, inFix); //Adicionar no IxFix
        analyzeTerm(c, token, symbol, inFix);
    }
}

// termo
void analyzeTerm(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa termo\n");
    analyzeFactor(c, token, symbol, inFix);
    while (isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv") || isEqualString((*token)->symbol, "se")) {
        getNewToken(c, token, symbol, inFix); //Adicionar no InFix
        analyzeFactor(c, token, symbol, inFix);
    }
}


// fator
void analyzeFactor(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix) {
    if(debug)
        printf("\nDEBUG - Sintatico - Analisa Fator\n");
    if (isEqualString((*token)->symbol,"sidentificador")) { // Variável ou Função
        if (verifyVarFuncDeclaration(symbol,  (*token)->lexeme)) { // Coleta o identificador correspondente para verificar seu tipo
            if (verifyFunctionDeclaration(symbol, (*token)->lexeme))
                analyzeFunctionCall(c, token, symbol, inFix);
            else
                getNewToken(c, token, symbol, inFix);
        } else errorSintax(token,24,'\0');
    } else if (isEqualString((*token)->symbol,"snumero")) {
        getNewToken(c, token, symbol, inFix);
    } else if (isEqualString((*token)->symbol,"snao")) {
        getNewToken(c, token, symbol, inFix);
        analyzeFactor(c, token, symbol, inFix);
    } else if (isEqualString((*token)->symbol,"sabre_parenteses")) {
        getNewToken(c, token, symbol, inFix);
        analyzeExpression(c, token, symbol, inFix);
        if (isEqualString((*token)->symbol,"sfecha_parenteses")){
            getNewToken(c, token, symbol, inFix);
        } else
            errorSintax(token, 1, ')');
    } else if (isEqualString((*token)->symbol, "sverdadeiro") || isEqualString((*token)->symbol, "sfalso")){
        getNewToken(c, token, symbol, inFix);
    } else
        errorSintax(token, 17, '\0');
}

