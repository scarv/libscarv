
#include <stdio.h>
#include "test_util.h"

uint32_t __attribute__ ((noinline)) perm(uint32_t in, uint32_t mask) {

    asm volatile (
        "xc.gpr2xcr c0,a0           \n"
        "xc.gpr2xcr c1,a1           \n"
        "xc.pbit    c0,c1,0b11111   \n"
        "xc.xcr2gpr a0,c0           \n"
    );

}

uint32_t __attribute__ ((noinline)) iperm(uint32_t in, uint32_t mask) {

    asm volatile (
        "xc.gpr2xcr c0,a0           \n"
        "xc.gpr2xcr c1,a1           \n"
        "xc.ipbit   c0,c1,0b11111   \n"
        "xc.xcr2gpr a0,c0           \n"
    );

}

int main(int argc, char ** argv) {

    printf("# bitperm test\n");

    uint32_t mask = 0x00000000;
    uint32_t in   = 0x00000001;
    uint32_t out  = perm(in,mask);

    printf("m=0x%08X, i=0x%08X, o=0x%08X\n", mask, in, out);
    
    in   = out;
    out  = iperm(in,mask);

    printf("m=0x%08X, i=0x%08X, o=0x%08X\n", mask, in, out);

}

