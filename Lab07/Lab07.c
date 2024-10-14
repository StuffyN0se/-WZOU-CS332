#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv) {
int writeFileDescriptor;
pid_t pid;
int status;
time_t start, end;
char time_Start[100];
char time_End[100];
double duration;
char time_duration[100];

writeFileDescriptor = open("Output.log", O_CREAT|O_WRONLY|O_APPEND, 0700);  //opens or if the file doesnt exist create a output log 

if (writeFileDescriptor == -1) {
    perror("Error opening file");
    return 1; // Exit with error
}

//starts timer
start = time(NULL);
snprintf(time_Start, sizeof(time_Start), "Time start: %s", ctime(&start));
//write start time into the output
write(writeFileDescriptor, time_Start, strlen(time_Start));

pid = fork();
if (pid == 0) { /* this is child process */
execl("../Lab07/sampleHW","sampleHW", (char *)NULL);                //execute file via filepath (used sampel HW1 provided in file)
printf("If you see this statement then execl failed ;-(\n");
perror("execl");
exit(-1);
} else if (pid > 0) { /* this is the parent process */
printf("Wait for the child process to terminate\n");
wait(&status); /* wait for the child process to terminate */
if (WIFEXITED(status)) { /* child process terminated normally */

//record end time
end = time(NULL);
snprintf(time_End, sizeof(time_End), "\tTime end: %s", ctime(&end));
//write end time into output file
write(writeFileDescriptor, time_End, strlen(time_End));

duration = difftime(end, start);
snprintf(time_duration, sizeof(time_duration), "Total Duration: %.2f seconds\n", duration);
write(writeFileDescriptor, time_duration, strlen(time_duration));

printf("Child process exited with status = %d\n", WEXITSTATUS(status));
} else { /* child process did not terminate normally */
printf("Child process did not terminate normally!\n");
/* look at the man page for wait (man 2 wait) to determine
how the child process was terminated */
}
} else { /* we have an error */
perror("fork"); /* use perror to print the system error message */
exit(EXIT_FAILURE);
}
printf("[%ld]: Exiting program .....\n", (long)getpid());
return 0;
}
/*
This is output
Time start: Mon Oct 14 02:41:22 2024
	Time end: Mon Oct 14 02:41:22 2024
Total Duration: 0.00 seconds
*/