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
int main (int argc, char **argv) {
struct dirent *dirent;
DIR *parentDir;
if (argc < 2) {
printf ("Usage: %s <dirname>\n", argv[0]);
exit(-1);
}
parentDir = opendir (argv[1]);
if (parentDir == NULL) {
printf ("Error opening directory '%s'\n", argv[1]);
exit (-1);
}
int count = 1;
while((dirent = readdir(parentDir)) != NULL){
printf ("[%d] %s (%s)\n", count, dirent->d_name, filetype(dirent->d_type));
count++;
}

int fd;
struct stat statbuf;
if ((fd = open(argv[1], O_RDONLY)) == -1) {
printf("Error opening file %s\n", argv[1]);
perror("open");
exit(-1);
}
read(fd, &statbuf, sizeof(struct stat));
close(fd);
printstat(statbuf);

void printstat(struct stat statbuf);

int i;
struct stat buf;
char *ptr;
for (i = 1; i < argc; i++) {
printf("%s: ", argv[i]);
if (lstat(argv[i], &buf) < 0) {
printf("lstat error");
continue;
}
if (S_ISREG(buf.st_mode))
ptr = "regular";
else if (S_ISDIR(buf.st_mode))
ptr = "directory";
else if (S_ISCHR(buf.st_mode))
ptr = "character special";
else if (S_ISBLK(buf.st_mode))
ptr = "block special";
else if (S_ISFIFO(buf.st_mode))
ptr = "fifo";
else if (S_ISLNK(buf.st_mode))
ptr = "symbolic link";
else if (S_ISSOCK(buf.st_mode))
ptr = "socket";
else
ptr = "** unknown mode **";
printf("%s\n", ptr);
printstat(buf);
}
closedir (parentDir);
return 0;
}




