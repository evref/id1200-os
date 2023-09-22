#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


/*
-- HOW TO RUN --

Using gcc:
    'gcc part1.c'
    './a.out'
*/

int main() {
    int pipefd[2];

    pipe(pipefd);

    switch (fork()) {
        case -1: // fork error
            break;
        case 0: // child
            close(pipefd[0]); // close pipe read channel
            dup2(pipefd[1], STDOUT_FILENO); 
            execlp("ls", "ls", "/", NULL); // execute unix command 'ls /'
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
            break;
        default: // parent
            close(pipefd[1]); // close pipe write channel
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execlp("wc", "wc", "-l", NULL);
            break;
    }
    
    return 0;
}