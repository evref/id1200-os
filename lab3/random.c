#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void init(int *sequence, int refs, int pages) {
    int high = (int)(pages*((float)HIGH/100));

    for (int i = 0; i<refs; i++) {
        if(rand() % 100 > FREQ) /* the frequently case */
            sequence[i] = rand() % high;
        else /* the less frequently case */
            sequence[i] = high + rand() % (pages - high);
    }
}

int main(int argc, char *argv[]) {
    /* could be command line arguments */
    int refs = 10;
    int pages = 100;

    int *sequence = (int*)malloc(refs * sizeof(int));
    init(sequence, refs, pages);

    /* a small experiment to show that it works */
    for(int i = 1; i < refs; i++)
        printf(", %d", sequence[i]);

    printf("\n");
    return 0;
}
