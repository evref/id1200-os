#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#define NUM_THREADS 4

pthread_mutex_t lock;

struct thread_args {
    int *buffer_addr;
};

struct thread_result {
    int iterations;
};

void *thread_func(void *args) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    struct thread_args *t_args = args;
    struct thread_result *res = malloc(sizeof *res);

    while (1) {
        pthread_mutex_lock(&lock);
        if (*t_args->buffer_addr >= 15) {
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("TID: %ld, PID: %ld, Buffer: %d\n", tid, pid, *t_args->buffer_addr);
        *t_args->buffer_addr += 1;
        res->iterations += 1;
        pthread_mutex_unlock(&lock);
    }
    char pluralletter;
    if (res->iterations > 1 || res->iterations == 0) pluralletter = 's';
    printf("TID %ld worked on the buffer %d time%c", tid, res->iterations, pluralletter);
    printf("\n");

    
    return res;
}

int main() {
    pthread_t threads[NUM_THREADS];
    void *out_void;
    struct thread_result *out;
    int buffer = 0, result;
    struct thread_args args = {.buffer_addr = &buffer};

    pthread_mutex_init(&lock, NULL);

    int i, iterations = 0;
    for (i = 0; i < NUM_THREADS; i++) {
        result = pthread_create(&threads[i], NULL, thread_func, &args);
        assert(!result);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        result = pthread_join(threads[i], &out_void);
        assert(!result);
        out = out_void;
        iterations += out->iterations;
    }
    printf("Total buffer accesses: %d\n", iterations);

    pthread_mutex_destroy(&lock);

    return 0;
}
