#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    FILE *fp;
    char output[BUFSIZ];
    int quit = 0;       //loop number
    char command[BUFSIZ];

    //starts loop
    while (quit == 0){
        printf("Please Enter Command: ");

        //gets command from stdin
        if(fgets(command, BUFSIZ, stdin) == NULL){
            perror("There was an error getting commands");
            exit(EXIT_FAILURE);
        }
        //removes new line character
        command[strcspn(command, "\n")] = 0;
        
        //if user inputs quit then break
        if (strcmp(command, "quit") == 0){
            printf("Quit read exit program");
            break;
        }

        /* create a pipe, fork/exec command argv[1], in "read" mode */
        /* read mode - parent process reads stdout of child process */
        if ((fp = popen(command, "r")) == NULL) {
            perror("There was an error creating pipe");
            exit(EXIT_FAILURE);
        }

        while (fgets(output, BUFSIZ, fp) != NULL) {
             printf("%s", output);
        }
        /* wait for child process to terminate */
        if (pclose(fp) == -1) {
            perror("pclose");
            exit(EXIT_FAILURE);
        }

    }
    return 0;

}
