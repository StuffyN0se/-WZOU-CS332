rectory Traversal Program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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

// Hold file information
typedef struct {
    char name[1000];
    char path[1000];
    long size;
    unsigned char type;
    int depth;
} FileInfo;

// Print file stats
void printstat(struct stat statbuf) {
    printf("File size: %ld bytes\n", statbuf.st_size);
}

// Sorts files from largest to smallest
int compareBySize(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileB->size - fileA->size);  // sort from largest to smallest
}

// Recursively traverse directories and store directory entries
void traverse_directory(const char *directory, FileInfo **files, int *fileCount, int print_size, int sizeFilter, int subStr, const char *subString, int depth) {
    struct dirent *dirent;
    DIR *parentDir = opendir(directory);

    if (parentDir == NULL) {
        printf("Unable to open directory: '%s'\n", directory);
        return;
    }
    // Read directory
    while ((dirent = readdir(parentDir)) != NULL) {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0 || dirent->d_name[0] == '.') {
            continue;
        }

        char filePath[1000];    // Variable to store filepath
        snprintf(filePath, sizeof(filePath), "%s/%s", directory, dirent->d_name);

        struct stat buf;
        if (lstat(filePath, &buf) == -1) {
            perror("lstat error");
            continue;
        }

        // If sizeFilter is turned on (0 = off 1 = on)
        if (sizeFilter > 0 && buf.st_size <= sizeFilter) {
            continue;
        }

        // Checks to see if substring is in file name if -f is 1
        if (subStr == 1 && strstr(dirent->d_name, subString) == NULL) {
            continue;
        }

        // Stores file info in array
        *files = realloc(*files, (*fileCount + 1) * sizeof(FileInfo)); //dynamically allocate mem for file info
        strncpy((*files)[*fileCount].name, dirent->d_name, sizeof((*files)[*fileCount].name) - 1);  //stores and copies name
        strncpy((*files)[*fileCount].path, filePath, sizeof((*files)[*fileCount].path) - 1); //stores and copies path
        (*files)[*fileCount].size = buf.st_size;    //store file size
        (*files)[*fileCount].type = dirent->d_type;     //store fiel type
        (*files)[*fileCount].depth = depth + 1;     //stores current depth
        (*fileCount)++;

        if (dirent->d_type == DT_DIR) {
            traverse_directory(filePath, files, fileCount, print_size, sizeFilter, subStr, subString, depth + 1);
        }
    }
    
    closedir(parentDir);
}

int main(int argc, char **argv) {
    int print_size = 0;
    int sizeFilter = 0;
    int subStr = 0;
    int reverse = 0;
    char subString[1000] = {0};
    const char *directory = ".";

    //checks command line to see if options were entered
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-S") == 0) {
            print_size = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            subStr = 1;
            strncpy(subString, argv[++i], sizeof(subString) - 1);
        } else if (strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            sizeFilter = atol(argv[++i]);
        } else {
            directory = argv[i];
        }
    }

    FileInfo *files = NULL;  //creates array to store info
    int fileCount = 0;

    traverse_directory(directory, &files, &fileCount, print_size, sizeFilter, subStr, subString, 0);

    //sort by size (large to small)
    if (reverse) {
        qsort(files, fileCount, sizeof(FileInfo), compareBySize);
    }

    //print files
    for (int i = 0; i < fileCount; i++) {
        for (int j = 0; j < files[i].depth; j++) printf("\t");
        
        printf("%s (%s)", files[i].name, filetype(files[i].type));

        if (print_size) {
            printf(" - File size: %ld bytes", files[i].size);
        }
        printf("\n");
    }
    free(files);
    return 0;
}