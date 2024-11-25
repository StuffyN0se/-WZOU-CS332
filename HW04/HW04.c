#include <stdio.h>      // for printf, standard I/O
#include <stdlib.h>     // for rand(), exit()
#include <unistd.h>     // for fork(), pipe(), close()
#include <pthread.h>    // for thread functions
#include <sys/wait.h>   // for wait()
#include <time.h>       // for srand(time(NULL)) to generate random numbers
#include <sys/types.h>  // for pid_t type
#include <fcntl.h>
#include <stdint.h>


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int pipefd[2];          // variable to store pipe file descriptor
int thread_sums[10];    // global variable to store the sums I will get from child process

//function to generate 500 random integers
void* generate (void *arg){
    int numbers [500];                              //create array to store 500 integers
    for (int i =0; i <500; i++){
        numbers[i] = rand() % 1001;
    }

    pthread_mutex_lock(&mutex);                     //give thread access

    ssize_t bytes_written = write(pipefd[1], numbers, sizeof(int) * 500);
    if (bytes_written != sizeof(int) * 500) {
        fprintf(stderr, "Error: Incomplete write. Only %ld bytes written\n", bytes_written);
    }
    pthread_mutex_unlock(&mutex);                   //take away access

    return NULL;
}

//function to calculate sum of 150 numbers in child process
void* sum (void* arg){
    int thread_num = (intptr_t)arg;        //cast arg to type int (argument in this is is thread number)
    int numbers[150];                      //create int array to store the 150 numbers
    int sum = 0;

    pthread_mutex_lock(&mutex); 

    int read_num = read(pipefd[0], numbers, sizeof(int) * 150);     //read 150 numbers from the pipe based on bytes. So the function is reading 600 bytes of data.
    if (read_num == -1){
        perror("Error reading from pipe");
        pthread_exit(NULL);
    }
    // if more or less than 150 numbers is detected print error
    else if (read_num != sizeof(int)* 150){
        perror("Error : Did not recieve 150 integers\n");
    }

    pthread_mutex_unlock(&mutex);

    // loop to add all the nubmers up if 150 integers is recieved
    for (int i = 0; i <150; i++){
            sum += numbers[i];
        }
    

    pthread_mutex_lock(&mutex);         //give thread access
    thread_sums[thread_num] = sum;      //store the sum in array using thread number as index
    pthread_mutex_unlock(&mutex);       //remove access
    return NULL;
}

int main (int argc, char **argv ) {
    srand(time(NULL)); // prevents same nubmers from being generated

    if(pipe(pipefd) == -1){
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();                 //create child process
    if (pid == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if (pid > 0){                       //checks to see if process is parent 
        close(pipefd[0]);
        
        pthread_t parent_threads[3];    //create array to store the ID of the 3 threads
        for (int i = 0; i <3; i++){     //create 3 threads one
            if(pthread_create(&parent_threads[i], NULL, generate, NULL) != 0) {   //thread will run generate function
                perror("Error creating parent thread");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < 3; i++) {
            if (pthread_join(parent_threads[i], NULL) != 0) { //join threads all the numbers will be combined at this point
                perror("Error joining parent thread");
                exit(EXIT_FAILURE);
            }                                  
        }
        wait(NULL);                     //wait for child process to terminate
    }

    else if (pid == 0){                 //checks to see if process is the child
        //child processes here
        close(pipefd[1]);

        usleep(100);                       //makes a delay for child before reading from pipe to avoid error

        FILE* fp = fopen("output.txt","w");             //opens file for write
        if (fp == NULL) {
	        perror("Error opening file output.txt for writing\n");
	        exit(EXIT_FAILURE);
        }
        //redirects standard output to fp
        if (dup2(fileno(fp), STDOUT_FILENO) == -1) {
            perror("Error redirecting standard output to file");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        fclose(fp);

        pthread_t child_threads[10];                    //creates an array to store thread ID
        for (int i = 0; i <10; i++){
            if(pthread_create(&child_threads[i], NULL, sum, (void*)(intptr_t)i) != 0){     //thread is created and calls on sum function the function will pass a int from 0-9 to be used as the thread number (used as index later on)
                perror("Error creating child thread");
                exit(EXIT_FAILURE);                                                                        
            }                                                                        
        }                                                                           

        for(int i = 0; i < 10; i++) {
            if (pthread_join(child_threads[i], NULL) != 0) {
                perror("Error joining child thread");
                exit(EXIT_FAILURE);
            }
        }   

        //calculates the average
        int total = 0;
        for(int i =0; i < 10; i++){
            total += thread_sums[i];
        }
        int average = total/10;
        //prints out average (which will be directed to output file)
        printf("The average is: %d\n", average);

        exit(0);
    }
}