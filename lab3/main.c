#include <stdio.h>
#include <stdlib.h>


unsigned long nums[] = { 1, 256, 32768, 32769, 128, 65534, 33153 };
unsigned short ptable[256];
signed char *mem;
int nextFreeSpace = 0;
FILE *bs;



int get_offset(unsigned int num){
    return num & 0xff;
}
int get_pgnum(unsigned int num){
    return (num >> 8) & 0xff;
}


char get_value(unsigned short paddress){
    return mem[paddress];
}

void allocate_frame(char page){
    fseek(bs, page<<8, SEEK_SET);
    fread(mem+nextFreeSpace, 1, 256, bs);
    ptable[page] = (nextFreeSpace>>8) | 0x100; //frame plus validbit
    nextFreeSpace+=256;
}

unsigned short get_physical_address(unsigned short vaddress){
    int pnum = get_pgnum(vaddress);
    int offset = get_offset(vaddress);
    printf("ERROR CHECK: ");
    if(!(ptable[pnum] & 0x100)){ // if page address not in page table
        allocate_frame(pnum);
    }
    printf("%d", pnum);
    printf(", %d\n", ptable[pnum]);
    return ((ptable[pnum] & 0xff) << 8) | offset;
}

void testfunc(){
    FILE *in = fopen("addresses.txt", "r");
    FILE *out = fopen("output.txt", "a");
    printf("TEST START\n");
    int address;
    int paddress;
    while(fscanf(in, "%d", &address)){
        printf("TEMP CHECK\n");
        paddress = get_physical_address(address);
        printf("PRINTING ");
        fprintf(out, "Virtual address: %d Physical address: %d Value: %d\n", address, paddress, get_value(paddress));
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
