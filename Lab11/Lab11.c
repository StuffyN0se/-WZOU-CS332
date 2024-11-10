#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    FILE *fp1, *fp2;
    char line[BUFSIZ];
    int quit = 0;


        if (argc != 3) {
            printf("Usage: %s <command1> <command2>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        /* create a pipe, fork/exec command argv[1], in "read" mode */
        /* read mode - parent process reads stdout of child process */
        if ((fp1 = popen(argv[1], "r")) == NULL) {
            perror("popen");
            exit(EXIT_FAILURE);
        }
        /* create a pipe, fork/exec command argv[2], in "write" mode */
        /* write mode - parent process writes to stdin of child process */
        if ((fp2 = popen(argv[2], "w")) == NULL) {
            perror("popen");
            exit(EXIT_FAILURE);
        }
        /* read stdout from child process 1 and write to stdin of
        child process 2 */
        while (fgets(line, BUFSIZ, fp1) != NULL) {
            if (fputs(line, fp2) == EOF) {
                printf("Error writing to pipe\n");
                exit(EXIT_FAILURE);
            }
        }
        /* wait for child process to terminate */
        if ((pclose(fp1) == -1) || pclose(fp2) == -1) {
            perror("pclose");
            exit(EXIT_FAILURE);
        }

        if (strcmp(argv[1], "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }
    return 0;

}
