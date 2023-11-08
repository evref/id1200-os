#include <stdio.h>

unsigned int nums[] = { 1, 256, 32768, 32769, 128, 65534, 33153 };

int get_offset(unsigned int num) {
    return num & 0xff;
}

int get_pgnum(unsigned int num) {
    return get_offset(num >> 8);
}

int main() {
   printf("Hello, World!\n");

   int i;
   for(i = 0; i < 7; i++) {
       int pgnum = get_pgnum(nums[i]);
       int offset = get_offset(nums[i]);
       printf("%x | pgnum: %x, offset: %x\n", nums[i], pgnum, offset);
   }
}

