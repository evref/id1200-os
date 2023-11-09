#include <stdio.h>

unsigned long nums[] = { 1, 256, 32768, 32769, 128, 65534, 33153 };
unsigned short ptable[256];
signed char *mem;


int get_offset(unsigned int num){
    return num & 0xff;
}
int get_pgnum(unsigned int num){
    return get_offset(num >> 8);
}


char get_value(unsigned short paddress){
    return mem[paddress];
}

void allocate_frame(char page){
    
}

unsigned short get_physical_address(unsigned short vaddress){
    int pnum = get_pgnum(vaddress);
    int offset = get_offset(vaddress);

    if(!(ptable[pnum] & 0x100)){ // if page address not in page table
        allocate_frame(pnum);
    }

    return ((ptable[pnum] & 0xff) << 8) | offset;
}

int main(){
    mem = malloc(65535);
    printf("Hello, World!\n");

    int i;
    for(i = 0; i < 7; i++) {
        int pgnum = get_pgnum(nums[i]);
        int offset = get_offset(nums[i]);
        printf("%lx | pgnum: %x, offset: %x\n", nums[i], pgnum, offset);
    }
}

