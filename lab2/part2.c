#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h> 
#include<unistd.h>
#include<sys/wait.h>
#include<sys/mman.h>

#define MAX 5


//kompilera med:
// gcc -pthread [filnamn].c

sem_t* sem;
sem_t* sem2;


void* reader(int* buffer) {
    pid_t pid = getpid();
    int semval;

    do{
        sem_wait(sem2);
        sem_wait(sem);
        sem_getvalue(sem, &semval);
        if(semval==1)
            printf("The first reader acquires the lock.\n");
        sem_post(sem2);
        printf("The reader (%d) reads the value %d\n", pid, *buffer);
        sem_wait(sem2);
        sem_getvalue(sem, &semval);
        if(semval==1)
            printf("The last reader releases the lock.\n");
        sem_post(sem);
        sem_post(sem2);
        sleep(1);
    }while(*buffer < MAX);
}

void* writer(int* buffer) {
    pid_t pid = getpid();

    do{
        sem_wait(sem2);
        sem_wait(sem);
        sem_wait(sem);
        printf("The writer acquires the lock.\n");
        (*buffer)++;
        printf("The writer (%d) writes the value %d\n", pid, *buffer);
        printf("The writer releases the lock.\n");
        sem_post(sem);
        sem_post(sem);
        sem_post(sem2);
        sleep(1);
    }while(*buffer < MAX);

    exit(0);
}

int main(void) {
    int wstatus;
    int* buffer = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem2 = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(sem, 1, 2);
    sem_init(sem2, 1, 1);

    pid_t pid = fork();
    switch (pid) {
    case -1:
        perror("fork\n");
        exit(EXIT_FAILURE);
    case 0:
        fork();
        reader(buffer);
        break;
    default:
        writer(buffer);
    }

    return 0;
}
