
#include <stdio.h>
#include "test_util.h"

#include "scarv/kernels/present.h"

uint64_t test_rand() {

  uint64_t tr;

  FILE* fd = fopen( "/dev/urandom", "rb" );
  fread( &tr, sizeof( tr), 1, fd );
  fclose( fd );

  return tr;
} 

void print_ui64(uint64_t * state) {
    uint8_t * p = (uint8_t*)state;

    printf("0x");
    for(int i = 0; i < 8; i ++) {
        int k =   7-i;
        uint8_t c = p[k];
        printf("%.2X", c);
        //printf("%d ", k);
    }
}

void test_present_slayer(uint32_t num) {

    for(uint32_t i = 0; i < num; i++) {
    
        uint64_t input = test_rand();

        printf("# present slayer %d/%d\n",i,num);

        printf("input  = "); print_ui64(&input); printf("\n");
    
        uint32_t count_c = test_util_rdcycle();
        uint32_t count_i = test_util_rdinstret();
        
        uint64_t output = present_slayer(input);
    
        count_c = test_util_rdcycle()  - count_c;
        count_i = test_util_rdinstret()- count_i;

        printf("output = "); print_ui64(&output); printf("\n");
        printf("# cycles = %lu\n", count_c);
        printf("# instrs = %lu\n", count_i);

        input = output;

    }
}

int main(int argc, char ** argv) {
    test_present_slayer(100);
}

