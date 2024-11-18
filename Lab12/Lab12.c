/* 
  Simple Pthread Program to find the sum of a vector.
  Uses mutex locks to update the global sum. 
  Author: Purushotham Bangalore
  Date: Jan 25, 2009

  To Compile: gcc -O -Wall pthread_psum.c -lpthread
  To Run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

struct Variable {
  int N, size;
  double sum;
  double *a;
  long tid;
};

void *compute(void *arg) {
    struct Variable *var = (struct Variable *)arg; // Cast argument to structure pointer
    int myStart, myEnd, myN, i;
    long tid = (long)arg;

    // determine start and end of computation for the current thread
    myN = var->N/var->size;
    myStart = var->tid*myN;
    myEnd = myStart + myN;
    if (var->tid == (var->size-1)) myEnd = var->N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++)
      mysum += var->a[i];

    // grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);
    var->sum += mysum;
    pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {
    int N = 0;
    int size = 0;
    double *a = NULL;
    double sum = 0.0;
    struct Variable *vars = NULL;
    pthread_t *threads = NULL;

        if (argc != 3) {
        printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
        exit(-1);
    }

    // Parse input arguments
    N = atoi(argv[1]); // Number of elements
    size = atoi(argv[2]); // Number of threads

    // Allocate and initialize the vector
    a = (double *)malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) {
        a[i] = (double)(i + 1);
    }

    // Allocate thread IDs and structure instances
    threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
    vars = (struct Variable *)malloc(sizeof(struct Variable) * size);

    // Initialize structures and create threads
    for (long i = 0; i < size; i++) {
        vars[i].N = N;
        vars[i].size = size;
        vars[i].sum = sum;
        vars[i].a = a;
        vars[i].tid = i;
        pthread_create(&threads[i], NULL, compute, (void *)&vars[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
        sum = vars[i].sum; // Accumulate the global sum
    }

    // Verify the result
    printf("The total is %g, it should be equal to %g\n", sum, ((double)N * (N + 1)) / 2);


    return 0;
}

