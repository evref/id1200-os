#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int QUEUE_SIZE = 1000;
int CYLINDER_LEN = 5000;
int NUM_ALGORITHMS = 6;

int comp_int (int a, int b)
{
    return (a > b) - (a < b);
}

void fcfs(int* steps_moved, int* queue, int start_head_pos) {
    int i, head_pos = start_head_pos;
    for (i = 0; i < QUEUE_SIZE; i++) {
        *steps_moved += abs(queue[i] - head_pos);
        head_pos = queue[i];
    }
}

void sstf(int* steps_moved, int* queue, int start_head_pos) {
    int head_pos = start_head_pos;
    int q[QUEUE_SIZE];
    int i = 0;
    int low;
    int high;
    int dist_low;
    int dist_high;

    memcpy(q, queue, sizeof(int));
    qsort(q, QUEUE_SIZE, sizeof(int), comp_int);

    while(q[i] <= head_pos){i++;}   //optimera med binary search
    low = i-1, high = i;
    while (low >= 0 && high <5000){
        dist_low = abs(head_pos-q[low]);
        dist_high = abs(head_pos-q[high]);
        if(dist_low < dist_high){
            *steps_moved += dist_low;
            head_pos = q[low];
            low--;
        } else{
            *steps_moved += dist_high;
            head_pos = q[high];
            high++;
        }
    }
    while (low >= 0){
        dist_low = abs(head_pos-q[low]);
        *steps_moved += dist_low;
        head_pos = q[low];
        low--;
    }
    while (high <5000){
        dist_high = abs(head_pos-q[high]);
        *steps_moved += dist_high;
        head_pos = q[high];
        high++;
    }
}

void scan(int* steps_moved, int* queue, int start_head_pos) {
    int head_pos = start_head_pos;
    int q[QUEUE_SIZE];
    int i = 0;
    int temp;

    memcpy(q, queue, sizeof(int));
    qsort(q, QUEUE_SIZE, sizeof(int), comp_int);

    while(q[i] <= head_pos){i++;}   //optimera med binary search
    temp = i;
    while(i>0){
        i--;
        *steps_moved += head_pos - q[i]; // huvudet går nedåt, detta blir positivt
        head_pos = q[i];
    }
    *steps_moved += head_pos;
    head_pos = 0;
    i = temp;
    while(i<5000){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }
}

void look(int* steps_moved, int* queue, int start_head_pos) {
    int head_pos = start_head_pos;
    int q[QUEUE_SIZE];
    int i = 0;
    int temp;

    memcpy(q, queue, sizeof(int));
    qsort(q, QUEUE_SIZE, sizeof(int), comp_int);

    while(q[i] <= head_pos){i++;}   //optimera med binary search
    temp = i;
    while(i>0){
        i--;
        *steps_moved += head_pos - q[i]; // huvudet går nedåt, detta blir positivt
        head_pos = q[i];
    }
    i = temp;
    while(i<5000){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }
}

void cscan(int* steps_moved, int* queue, int start_head_pos) {
    int head_pos = start_head_pos;
    int q[QUEUE_SIZE];
    int i = 0;
    int temp;

    memcpy(q, queue, sizeof(int));
    qsort(q, QUEUE_SIZE, sizeof(int), comp_int);

    while(q[i] <= head_pos){i++;}   //optimera med binary search
    temp = i;
    while(i<5000){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }
    if(temp == 0) return;
    i = 0;

    *steps_moved += 4999 - head_pos;
    head_pos = 4999;
    *steps_moved += 5000;
    head_pos = 0;
    while(i<temp){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }
}

void clook(int* steps_moved, int* queue, int start_head_pos) {
    int head_pos = start_head_pos;
    int q[QUEUE_SIZE];
    int i = 0;
    int temp;

    memcpy(q, queue, sizeof(int));
    qsort(q, QUEUE_SIZE, sizeof(int), comp_int);

    while(q[i] <= head_pos){i++;}   //optimera med binary search
    temp = i;
    while(i<5000){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }

    *steps_moved += head_pos;
    head_pos = 0;
    while(i<temp){
        *steps_moved += q[i] - head_pos; //positiv summa då huvudet går uppåt
        head_pos = q[i];
        i++;
    }
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
