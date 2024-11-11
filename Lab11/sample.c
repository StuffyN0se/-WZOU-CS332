#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int quit = 0;
    char input[BUFSIZ];

    while (quit ==0){
        printf("Please enter a word: ");
        fgets(input, BUFSIZ, stdin);

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0){
            printf("quit read kill program");
            break;
        }
        else{
            printf("The input is %s\n", input);
        }
    }
    return 0;
}