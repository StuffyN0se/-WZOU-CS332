#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


//identifies the type of file 
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

//function to recursively go through directories and their subdirectories
void traverse_directory(const char *directory) {
    //creates strut to store directories
    struct dirent *dirent;
    //parent directory is user input 
    DIR *parentDir = opendir(directory);

    if (parentDir == NULL) {
        printf ("Error: Directory not found'%s'\n", directory);
        return;
    }
    while((dirent = readdir(parentDir)) != NULL){

        //sees if directory is . or . or starts with . and skips them
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0 || dirent->d_name[0] == '.') {
            continue; 
        }
        //prints out the current file name and file type
        printf ("   -%s (%s)\n", dirent->d_name, filetype(dirent->d_type));

        //creates buffer to store the current filePath
        char filePath[1000];
        snprintf(filePath, sizeof(filePath), "%s%s", directory, dirent->d_name);

        //if current file is a directory call on function recursively to go through the directory
        if (dirent->d_type == DT_DIR) {
        printf("Opening Directory: %s\n", dirent->d_name);
        traverse_directory(filePath); 
        }
    }
closedir (parentDir);
}
int main (int argc, char **argv) {

     if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(-1);
    }
    // Start traversal from the directory user inputted
    traverse_directory(argv[1]);
    return 0;
}