#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int param = 0;
    char instruction[] = "LDC     ";
    char line[20] = {0};
    char result[4], spaces[] = "    ";
    for(int i = 3;i>=0; param /= 10){
        result[i] = param > 0 ? param  % 10 + 48 : 32;
        i--;
    }
    printf("\n%s\n", result);
    if(result[0] == 32){
        for(int i = 1, j = 0; i < 4; i++){
            if(result[i] != 32){
                result[j++] = result[i];
                result[i] = 32;
            }
        }
    }

    strcat(line, spaces);
    strcat(line, instruction);
    strcat(line, result);
    strcat(line, spaces);

    printf("\n%s\n", line);
    return 0;
}