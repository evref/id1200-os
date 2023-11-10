#include <stdio.h>
#include <stdlib.h>


unsigned long nums[] = { 1, 256, 32768, 32769, 128, 65534, 33153 };
int ptable[256];
signed char *mem;
int nextFreeSpace = 0;
FILE *bs;



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

int get_physical_address(int vaddress){
    printf("ERROR");
    int pnum = get_pgnum(vaddress);
    int offset = get_offset(vaddress);
    printf(" CHECK: ");
    if(!(ptable[pnum] & 0x100)){ // if page address not in page table
        allocate_frame(pnum);
    }
    printf("%d", pnum);
    printf(", %d", ptable[pnum] & 0xff);
    printf(", %d\n", offset);
    return ((ptable[pnum] & 0xff) << 8) | offset;
}

void testfunc(){
    FILE *in = fopen("addresses.txt", "r");
    FILE *out = fopen("output.txt", "a");
    printf("TEST START\n");
    unsigned short address;
    unsigned short paddress;
    while(fscanf(in, "%hd", &address) != EOF){
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
