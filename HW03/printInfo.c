#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>


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

int countWords(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("fopen");
        return -1;
    }

    int wordCount = 0;
    char c;
    int inWord = 0;

    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            if (inWord) {
                wordCount++;
                inWord = 0; 
            }
        } else {
            inWord = 1;
        }
    }
    if (inWord) {
        wordCount++;
    }

    fclose(file);
    return wordCount;
}

void printFileInfo(const char *filePath) {
    struct stat fileStat;
    if (stat(filePath, &fileStat) < 0) {
        perror("stat");
        return;
    }
    int wordCount = countWords(filePath);
    if (wordCount == -1) {
        printf("Error counting words in file %s\n", filePath);
        return;
    }
    // Print information about the file
    printf("File: %s | Size: %ld bytes | Word Count: %d\n", filePath,  fileStat.st_size, wordCount);

}

int main (int argc, char **argv) {
     if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(-1);
    }
    printFileInfo(argv[1]);
    return 0;
}