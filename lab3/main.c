#include <stdio.h>
#include <stdlib.h>

struct key_value{
    int key;
    int value;
};

unsigned long nums[] = { 1, 256, 32768, 32769, 128, 65534, 33153 };
int ptable[256];
signed char *mem;
int nextFreeSpace = 0;
FILE *bs;
struct key_value tlb[16];
int tlb_idx = 0;


int get_offset( int num){
    return num & 0xff;
}
int get_pgnum( int num){
    return (num >> 8) & 0xff;
}


signed char get_value( int paddress){
    return *(mem+paddress);
}

void allocate_frame(unsigned char page){
    fseek(bs, page<<8, SEEK_SET);
    fread(mem+nextFreeSpace, 1, 256, bs);
    ptable[page] = (nextFreeSpace>>8) | 0x100; //frame plus validbit
    printf("(%d, %d) ", page, ptable[page]);
    nextFreeSpace+=256;
}

int get_physical_address(int vaddress) {
    printf("ERROR");
    int pnum = get_pgnum(vaddress);
    int offset = get_offset(vaddress);

    // check if page is in TLB
    int i;
    for(i = 0; i < tlb_idx; i++) {
        if(tlb[i].key == pnum) {
            printf("It's a match!");
            return (tlb[i].value << 8) | offset;
        }
    }

    printf(" CHECK: ");
    if(!(ptable[pnum] & 0x100)) { // if page address not in page table
        allocate_frame(pnum);
    }

    // add pnum and paddress to tlb
    tlb[tlb_idx].key = pnum;
    tlb[tlb_idx].value = ptable[pnum] & 0xff;

    if(tlb_idx != 15) {
        tlb_idx += 1;
    }

    printf("%d", pnum);
    printf(", %d", ptable[pnum] & 0xff);
    printf(", %d\n", offset);
    return ((ptable[pnum] & 0xff) << 8) | offset;
}

void testfunc() {
    FILE *in = fopen("addresses.txt", "r");
    FILE *out = fopen("output.txt", "a");
    printf("TEST START\n");
    unsigned short address;
    unsigned short paddress;
    while(fscanf(in, "%hd", &address) != EOF) {
        printf("TEMP ");
        printf("%d", address);
        printf(" CHECK\n");
        paddress = get_physical_address(address);
        printf("PRINTING ");
        fprintf(out, "Virtual address: %d Physical address: %d Value: %hhd\n", address, paddress, get_value(paddress));
        printf("DONE\n");
    }
    printf("TEST CLOSING\n");
    fclose(in);
    fclose(out);
    printf("END TEST\n");
}

int main(){
    mem = malloc(65535);
    bs = fopen("BACKING_STORE.bin", "rb");

    testfunc();

    fclose(bs);
}
