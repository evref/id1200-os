#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>


/*
-- HOW TO RUN --

Using gcc:
    'gcc part2.c'
    './a.out' for default file name "text.txt" or
    './a.out your_file_path.txt' if you wish to use it on another file
*/


void error_w_msg(char* msg) {
    perror(msg);
    exit(-1);
}

int main(int argc, char* argv[]) {
    switch (fork()) {
        case -1: // fork error
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0: // child process
            char* path = "text.txt";
            if (argc > 1) path = argv[1];

            char msg_buffer[1024];

            // open stream to file
            FILE *file_ptr = fopen(path, "r");
            if (file_ptr == NULL) error_w_msg("fopen");
            
            // read contents of file into msg_buffer
            int i = 0;
            char ch;
            do {
                ch = fgetc(file_ptr);
                msg_buffer[i] = ch;
                i++;
            } while (ch != EOF);
            fclose(file_ptr);

            // open writeonly message queue
            mqd_t mqd_wr = mq_open("/mymq", O_CREAT | O_WRONLY, 0600, NULL);
            if (mqd_wr == -1) error_w_msg("mq_open");

            // send message
            mq_send(mqd_wr, msg_buffer, strlen(msg_buffer), 10);
            mq_close(mqd_wr);

            break;
        default: // parent process
            // open readonly message queue
            mqd_t mqd_rd = mq_open("/mymq", O_RDONLY);

            // get mq attributes
            struct mq_attr attr;
            mq_getattr(mqd_rd, &attr);
            char *buffer = calloc(attr.mq_msgsize, 1);
            if (!buffer) error_w_msg("calloc");

            // receive message
            if ((mq_receive(mqd_rd, buffer, attr.mq_msgsize, NULL)) == -1) 
                error_w_msg("mq_receive");
            else {
                int pipefd[2];
                pipe(pipefd);

                // write received msg to pipe
                write(pipefd[1], buffer, strlen(buffer));
                close(pipefd[1]);

                // redirect pipe to stdin
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);

                // run unix command 'wc -w'
                execlp("wc", "wc", "-w", NULL);
            }
            
            // clean up allocated memory
            free(buffer);
            buffer = NULL;
            mq_close(mqd_rd);
            break;
    }

    return 0;
}