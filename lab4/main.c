#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int QUEUE_SIZE = 1000;
int CYLINDER_LEN = 5000;
int NUM_ALGORITHMS = 6;



void fcfs(int* steps_moved, int* queue, int start_head_pos) {
    int i, head_pos = start_head_pos;
    for (i = 0; i < QUEUE_SIZE; i++) {
        *steps_moved += abs(queue[i] - head_pos);
        head_pos = queue[i];
    }
}

void sstf(int* steps_moved, int* queue, int start_head_pos) {
    *steps_moved = 2;
}

void scan(int* steps_moved, int* queue, int start_head_pos) {
    *steps_moved = 3;
}

void look(int* steps_moved, int* queue, int start_head_pos) {
    *steps_moved = 4;
}

void cscan(int* steps_moved, int* queue, int start_head_pos) {
    *steps_moved = 5;
}

void clook(int* steps_moved, int* queue, int start_head_pos) {
    *steps_moved = 6;
}

void run_algorithms(int* queue) {
    int* num_moves = (int*)malloc(NUM_ALGORITHMS * sizeof(int));
    int start_head_pos = 53;

    fcfs(num_moves, queue, start_head_pos);
    printf("FCFS completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[0]);

    sstf(num_moves+1, queue, start_head_pos);
    printf("SSTF completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[1]);
    
    scan(num_moves+2, queue, start_head_pos);
    printf("SCAN completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[2]);

    look(num_moves+3, queue, start_head_pos);
    printf("Look completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[3]);

    cscan(num_moves+4, queue, start_head_pos);
    printf("C-SCAN completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[4]);

    clook(num_moves+5, queue, start_head_pos);
    printf("C-Look completed, required the head pointer to move a total of %d cylinder steps.\n", num_moves[5]);
}

int main() {
    srand(time(NULL));
    int* queue = (int*)malloc(QUEUE_SIZE * sizeof(int));

    int i;
    for (i = 0; i < QUEUE_SIZE; i++) queue[i] = rand() % 5000;

    run_algorithms(queue);
}
