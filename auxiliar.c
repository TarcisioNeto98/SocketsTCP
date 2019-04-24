#include <stdio.h>
#include <stdlib.h>

void falha(char string[]){
    printf("%s\n", string);
    exit(0);
}

int tam_string(char string[]){
    int i = 0;
    while(string[i] != '\0') i++;
    return i;
}

void esvazia(char string[]){
    int i = 0;
    while(i < tam_string(string)){
        string[i] = ' ';
        i++;
    }
}
