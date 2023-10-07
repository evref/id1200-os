#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h> 
#include<unistd.h>

#define MAX 10000

sem_t sem;
sem_t sem2;
int *buffer_addr;

void* reader(int *buffer) {
    pid_t pid = getpid();
    int semval;

    do{
        sem_wait(&sem2);
        sem_wait(&sem);
        sem_getvalue(&sem, &semval);
        if(semval==1)
            printf("The first reader acquires the lock.");
        sem_post(&sem2);
        printf("The reader (%d) reads the value %d", pid, *buffer);
        sem_wait(&sem2);
        sem_getvalue(&sem, &semval);
        if(semval==1)
            printf("The last reader acquires the lock.");
        sem_post(&sem);
        sem_post(&sem2);
        sleep(10);
    }while(1);
}

void* writer(int *buffer) {
    pid_t pid = getpid();

    do{
        sem_wait(&sem2);
        sem_wait(&sem);
        sem_wait(&sem);
        printf("The writer acquires the lock.");
        printf("The reader (%d) writes the value %d", pid, ++(*buffer));
        printf("The writer releases the lock.");
        sem_post(&sem);
        sem_post(&sem);
        sem_post(&sem2);
    }while(*buffer < MAX);

    exit(0);
}

int main(void) {
    int buffer = 0;
    sem_init(&sem, 1, 2);
    sem_init(&sem2, 1, 1);

    pid_t pid = fork();
    switch (pid) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        fork();
        reader(&buffer);
        exit(EXIT_SUCCESS);
    default:
        writer(&buffer);
        exit(EXIT_SUCCESS);
    }
    wait();

    return 0;
}
