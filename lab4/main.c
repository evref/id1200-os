#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int QUEUE_SIZE = 1000;
int CYLINDER_LEN = 5000;
int NUM_ALGORITHMS = 6;



void fcfs(int* steps_moved, int* queue) {
    *steps_moved = 1;
}

void sstf(int* steps_moved, int* queue) {
    *steps_moved = 2;
}

void scan(int* steps_moved, int* queue) {
    *steps_moved = 3;
}

void look(int* steps_moved, int* queue) {
    *steps_moved = 4;
}

void cscan(int* steps_moved, int* queue) {
    *steps_moved = 5;
}

void clook(int* steps_moved, int* queue) {
    *steps_moved = 6;
}

void run_algorithms(int* queue) {
    int* num_moves = (int*)malloc(NUM_ALGORITHMS * sizeof(int));

    fcfs(num_moves, queue);
    printf("FCFS completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[0]);

    sstf(num_moves+1, queue);
    printf("SSTF completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[1]);
    
    scan(num_moves+2, queue);
    printf("SCAN completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[2]);

    look(num_moves+3, queue);
    printf("Look completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[3]);

    cscan(num_moves+4, queue);
    printf("C-SCAN completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[4]);

    clook(num_moves+5, queue);
    printf("C-Look completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[5]);
}

int main() {
    srand(time(NULL));
    int* queue = (int*)malloc(QUEUE_SIZE * sizeof(int));

    int i;
    for (i = 0; i < QUEUE_SIZE; i++) {
        queue[i] = rand() % 5000;
        if (i % 50) printf("%d\n", queue[i]);
    }

    run_algorithms(queue);
}
