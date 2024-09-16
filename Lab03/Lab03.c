#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char** readStr(int *numStr){
    char input[100];
    char** strArr;
    int length = 0;
    printf("How many words are you going to enter? ");
    scanf("%d", numStr);
    strArr = malloc(*numStr * sizeof(char *));
    
    while(getchar() != '\n');
    printf("\n");
    for(int i = 0; i < *numStr; i++){
        printf("Enter word number %d: ", i + 1);
        fgets(input, sizeof(input), stdin);
        length = strlen(input);
        input[length - 1] = '\0';
        strArr[i] = malloc(length * sizeof(char));
        strcpy(strArr[i], input);
    }
    return strArr;
}

void insertionSort(char** str, int numStr){
    for (int i = 1; i < numStr; i++){
        char *key = str[i];
        int current = i - 1;
        while (current >= 0 && strcmp(str[current], key) > 0){
            str[current + 1] = str[current];
            current = current - 1;
        }
        str[current + 1] = key;
    }
}

void displayStrings(char** str, int numStr) {
    printf("\nSorted Strings: ");
    for (int i = 0; i < numStr; i++) {
        printf("%s ", str[i]);
    }
}

int main(int argc, char** argv){
    int numStr = 0;
    char **str = readStr(&numStr);
    insertionSort(str, numStr);
    displayStrings(str, numStr);
    printf("\n");

    for (int i = 0; i < numStr; i++) {
        free(str[i]);
    }
    free(str);

    return 0;
}
