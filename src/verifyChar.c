#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isSpaceCode(char c, int lineCount) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool isNotEndOfFile(char c) {
    return c != EOF;
}

bool isDigit(char c) {
    return c >= 48 && c <= 57;
}

bool isLetter(char c) {
    return c >= 65 && c <= 90 || c >= 97 && c <= 122;
}

bool isAritmeticOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

bool isRelationalOperator(char c) {
    return c == '!' || c == '>' || c == '<' || c == '=';
}

bool isPonctuation(char c) {
    return c == ';' || c == ',' || c == '(' || c == ')' || c == '.';
}

bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}

bool isIdentifier(char c) {
    return isDigit(c) || isLetter(c) || c == '_';
}