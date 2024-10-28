#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>


char *filetype(unsigned char type) {
    char *str;
    switch(type) {
        case DT_BLK: str = "block device"; break;
        case DT_CHR: str = "character device"; break;
        case DT_DIR: str = "directory"; break;
        case DT_FIFO: str = "named pipe (FIFO)"; break;
        case DT_LNK: str = "symbolic link"; break;
        case DT_REG: str = "regular file"; break;
        case DT_SOCK: str = "UNIX domain socket"; break;
        case DT_UNKNOWN: str = "unknown file type"; break;
        default: str = "UNKNOWN";
    }
    return str;
}
pid_t pid;
int status;
//traverse direcotory function
void traverse_directory(const char *directory) {
    //creates strut to store directories
    struct dirent *dirent;
    //parent directory is user input 
    DIR *parentDir = opendir(directory);

    if (parentDir == NULL) {
        printf ("Error: Directory not found '%s'\n", directory);
        return;
    }
    while((dirent = readdir(parentDir)) != NULL){

        //sees if directory is . or . or starts with . and skips them
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0 || dirent->d_name[0] == '.') {
            continue; 
        }
        char filePath[1000];
        snprintf(filePath, sizeof(filePath), "%s/%s", directory, dirent->d_name);
        
        pid = fork();
        if (pid == 0) { 
        execl("../HW03/printInfo", "printInfo", filePath, (char *)NULL);
        perror("execl"); // If execl fails, print an error
        printf("If you see this statement then execl failed ;-(\n");
        exit(-1);
        } else if (pid > 0) { 
        // printf("Wait for the child process to terminate\n");
        wait(&status);
        if (WIFEXITED(status)) { 

        printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else { 
        printf("Child process did not terminate normally!\n");
        }
        } else { 
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
        }
    }

closedir (parentDir);
}

int main(int argc, char **argv) {

pid_t pid;

if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(-1);
    }
    // Start traversal from the directory user inputted
    traverse_directory(argv[1]);
return 0;
}
