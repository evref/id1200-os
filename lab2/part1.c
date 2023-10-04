#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int NUM_THREADS = 3;

void *threadfunction(void *arg) {
    int *iterations = (int *)malloc(64);
    int *buffer = (int *)arg;

    while (1) {
        if (*buffer >= 15) break;
        printf("TID: <tid>, PID: <pid>, Buffer: %d\n", *buffer);
        *buffer += 1;
        *iterations += 1;
    }
    char pluralletter;
    if (*iterations > 1 || *iterations == 0) pluralletter = 's';
    printf("TID <tid> worked on the buffer %d time%c", *iterations, pluralletter);
    printf("\n");
    
    return iterations;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int buffer = 0;

    int i, iterations = 0;
    for (i = 0; i < 3; i++) iterations += pthread_create(&threads[i], NULL, threadfunction, &buffer);

    void *threadresults[NUM_THREADS];

    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], &threadresults[i]);
        iterations += *(int *)threadresults[i];
    }
    printf("Total buffer accesses: %d\n", iterations);

    return 0;
}