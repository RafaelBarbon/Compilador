#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Check for space characters
bool isSpaceCode(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Check if the cursor have been reached the end of file
bool isNotEndOfFile(char c) {
    return c != EOF;
}

// Check if the character is a digit
bool isDigit(char c) {
    return c >= 48 && c <= 57;
}

// Check if the character is a letter
bool isLetter(char c) {
    return c >= 65 && c <= 90 || c >= 97 && c <= 122;
}

// Check if the character is an arithmetic operator
bool isArithmeticOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// Check if the character is a relational operator
bool isRelationalOperator(char c) {
    return c == '!' || c == '>' || c == '<' || c == '=';
}

// Check if the character is puntuation
bool isPonctuation(char c) {
    return c == ';' || c == ',' || c == '(' || c == ')' || c == '.';
}

// Check if the strings are the same
bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;
}

// Check if the character is a valid identifier
bool isIdentifier(char c) {
    return isDigit(c) || isLetter(c) || c == '_';
}
