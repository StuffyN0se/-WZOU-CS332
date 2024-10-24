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

void printFileInfo(const char *filePath) {
    struct stat fileStat;
    if (stat(filePath, &fileStat) < 0) {
        perror("stat");
        return;
    }

    // Print information about the file
    printf("File: %s\n", filePath);
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Permissions: %o\n", fileStat.st_mode & 0777); // File permissions
    printf("Last modified: %ld\n", fileStat.st_mtime);
}

int main (int argc, char **argv) {

     if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(-1);
    }

    printFileInfo(argv[1]);
    return 0;
}