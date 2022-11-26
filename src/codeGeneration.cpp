#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "symbol.h"
#include "verifyChar.h"

//Transforms the integer parameter to string (Used to create the .obj file)
void toString(int param, char result[4]) {
    if(param == 0){
        result[0] = '0';
        result[1] = ' ';
        result[2] = ' ';
        result[3] = ' ';
        return;
    }
    for(int i = 3;i >= 0; param /= 10){
        result[i] = param > 0 ? param  % 10 + 48 : 32;
        i--;
    }
    if(result[0] == 32){
        for(int i = 1, j = 0; i < 4; i++){
            if(result[i] != 32){
                result[j++] = result[i];
                result[i] = 32;
            }
        }
    }
}


//Transforms the string parameter to integer (Used to get lexeme values and use it on generateAssembly)
int toInt(char *number) {
    int result = 0;
    for(int i = 0; number[i] >= 48 && number[i] <= 57; i++) {
        result += number[i] - 48;
        result *= 10;
    }
    result /= 10;
    return result;
}

//Used to concatenate the instructions with their parameters
void strCatAssembly(char *result, char *op2, int tam, int *tamLine){
    for(int i = 0; i < tam; i++){
        result[(*tamLine)++] = op2[i];
    }
}

//Create the instruction according to the parameters and insert it in the .obj file
void generateAssembly(char *instruction, int param1, int param2,Ui::MainWindow *ui) {
    int tamLine = 0;
    char line[21] = {0}, spaces[4] = "    ";
    char param1converted[4] = {0}, param2converted[4] = {0};
    toString(param1, param1converted);
    toString(param2, param2converted);

    if(isEqualString(instruction, "LDC     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "LDV     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "ADD     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "SUB     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "MULT    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "DIVI    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "INV     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "AND     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "OR      ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "NEG     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CME     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CMA     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CEQ     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CDIF    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CMEQ    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CMAQ    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "STR     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "JMP     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "JMPF    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "NULL    ")) {
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "RD      ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "PRN     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "START   ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "ALLOC   ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param2converted, 4, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
    } else if(isEqualString(instruction, "DALLOC  ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param2converted, 4, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
    } else if(isEqualString(instruction, "HLT     ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "CALL    ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, param1converted, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "RETURN  ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    } else if(isEqualString(instruction, "RETURNF ")) {
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, instruction, 8, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
        strCatAssembly(line, spaces, 4, &tamLine);
    }
    if(isEqualString(instruction, "HLT     ")) {
        line[tamLine++] = '\0';
    } else {
        line[tamLine++] = '\n';
        line[tamLine] = '\0';
    }
    int result = fprintf(outputCode,"%s",line);
    if(result == EOF)
        detectError(29,0,'\0',ui);
}

//Generate the commands from the POS_FIX Expression
void generateExpressionCode(ExpressionAnalyzer *posFix, Symbol *symbol,Ui::MainWindow *ui) {
    LexemeType type;
    int addr;
    char converted[4];
    while(posFix != NULL){ //It goes through the posFix expression and generate the assembly commands
        type = posFix->type;
        switch(type){
            case Inteiro:
                generateAssembly("LDC     ", toInt(posFix->lexeme), 0,ui);
                break;
            case Booleano:
                if(isEqualString(posFix->lexeme, "verdadeiro"))
                    generateAssembly("LDC     ", 1, 0,ui);
                else
                    generateAssembly("LDC     ", 0, 0,ui);
                break;
            case VarInt:
            case VarBool: //Search the adress of the variable on the Symbol Table
                addr = searchVarFuncAddress(symbol, posFix->lexeme);//Search Adress
                generateAssembly("LDV     ", addr, 0,ui);
                break;
            case FuncInt:
            case FuncBool://Search the label of the variable on the Symbol Table
                addr = searchVarFuncAddress(symbol, posFix->lexeme);
                generateAssembly("CALL    ", addr, 0,ui);
	            generateAssembly("LDV     ", 0, 0,ui); //The return value of the function will be stored on the zero adress of the memory stack
                break;
            case UnarioN:
                generateAssembly("INV     ", 0, 0,ui);
                break;
            case UnarioP:
                break;
            case OpMultDiv:
                if(isEqualString(posFix->lexeme, "*"))
                    generateAssembly("MULT    ", 0, 0,ui);
                else
                    generateAssembly("DIVI    ", 0, 0,ui);
                break;
            case OpMaisMenos:
                if(isEqualString(posFix->lexeme, "+"))
                    generateAssembly("ADD     ", 0, 0,ui);
                else
                    generateAssembly("SUB     ", 0, 0,ui);
                break;
            case Rel:
                if(isEqualString(posFix->lexeme, ">"))
                    generateAssembly("CMA     ", 0, 0,ui);
                else if(isEqualString(posFix->lexeme, "<"))
                    generateAssembly("CME     ", 0, 0,ui);
                else if(isEqualString(posFix->lexeme, "<="))
                    generateAssembly("CMEQ    ", 0, 0,ui);
                else if(isEqualString(posFix->lexeme, ">="))
                    generateAssembly("CMAQ    ", 0, 0,ui);
                else if(isEqualString(posFix->lexeme, "!="))
                    generateAssembly("CDIF    ", 0, 0,ui);
                else if(isEqualString(posFix->lexeme, "="))
                    generateAssembly("CEQ     ", 0, 0,ui);
                break;
            case Nao:
                generateAssembly("NEG     ", 0, 0,ui);
                break;
            case E:
                generateAssembly("AND     ", 0, 0,ui);
                break;
            case OU:
                generateAssembly("OR      ", 0, 0,ui);
                break;
        }
        posFix = posFix->next;
    }
}
