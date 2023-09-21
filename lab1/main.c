#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int status;
    int pid = fork();

    if(pid == 0) {
        printf("Hello from child!\n");
    } else if(pid < 0) {
        perror("fork");
        exit(1);
    } else {
        wait(&status);
        printf("Hello from parent at %i\n", pid);
    }

    return 0;
}