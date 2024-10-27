
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 

static pid_t child_pid;

static void sig_usr(int signal) {  // Function to handle received signals
    switch(signal) {               // Check which signal was received
        case SIGINT:              // If Ctrl-C was pressed
            printf("\nParent: Sending SIGINT to child\n");
            kill(child_pid, SIGINT);   // Forward SIGINT to child process
            break;
            
        case SIGTSTP:             // If Ctrl-Z was pressed
            printf("\nParent: Sending SIGTSTP to child\n");
            kill(child_pid, SIGTSTP);  // Forward SIGTSTP to child process
            break;
            
        case SIGQUIT:             // If Ctrl-\ was pressed
            printf("\nParent: Received SIGQUIT, terminating...\n");
            exit(0);              // Terminate parent process
            break;
            
        default:                  // For any other signal
            printf("received signal %d\n", signal);
    }
}

int main(int argc, char **argv) {
    pid_t pid;
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }
    // Register signal handler for SIGINT (Ctrl-C)
    if (signal(SIGINT, sig_usr) == SIG_ERR) {
        printf("can't catch SIGINT\n");
        exit(-1);
    }
    // Register signal handler for SIGTSTP (Ctrl-Z)
    if (signal(SIGTSTP, sig_usr) == SIG_ERR) {
        printf("can't catch SIGTSTP\n");
        exit(-1);
    }
    // Register signal handler for SIGQUIT (Ctrl-\)
    if (signal(SIGQUIT, sig_usr) == SIG_ERR) {
        printf("can't catch SIGQUIT\n");
        exit(-1);
    }

    pid = fork();
    if (pid == 0) { /* this is child process */
        // Reset signal handlers to default behavior for child
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        
        execvp(argv[1], &argv[1]);

        printf("If you see this statement then execl failed ;-(\n");
        perror("execvp");
        exit(-1);
    } 
    else if (pid > 0) { /* this is the parent process */
        child_pid = pid;
        printf("Wait for the child process to terminate\n");
        wait(&status); /* wait for the child process to terminate */

        if (WIFEXITED(status)) { /* child process terminated normally */
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } 
        else { /* child process did not terminate normally */
            printf("Child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine
            how the child process was terminated */
        }
    } 
    else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }
    printf("[%ld]: Exiting program .....\n", (long)getpid());
    return 0;
}