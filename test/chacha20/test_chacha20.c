#include "test_chacha20.h"

// ============================================================================

//! Load r with random data.
void test_chacha20_rand( uint32_t* r, int l_r ) {
  FILE* fd = fopen( "/dev/urandom", "rb" );
  fread( r, sizeof( uint32_t ), l_r, fd );
  fclose( fd );
}

//! Print out python code to represent an input/output array.
void test_chacha20_dump( char* id, uint32_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id );

  for( int i = 0; i < l_x; i++ ) {
    printf( "%08X", x[ i ] );
  }

  printf( "' )\n" );  
}

//! Run N interations of the chacha20 test function.
void test_chacha20(int n) {

    uint32_t input [16];
    uint32_t output[16];
  
    printf( "import sys, binascii\n" );

    for(int i = 0; i < n; i ++) {

        printf("#ChaCha20 %d/%d\n",i,n);
        
        test_chacha20_rand(input , 16);
        test_chacha20_rand(output, 16);

        test_chacha20_dump("input  ", input, 16);

        uint32_t count_c = test_util_rdcycle();
        uint32_t count_i = test_util_rdinstret();

        chacha20_block(output, input);

        count_c = test_util_rdcycle()  - count_c;
        count_i = test_util_rdinstret()- count_i;
        
        test_chacha20_dump("output ", output, 16);

        printf("# cycles = %lu\n", count_c);
        printf("# instrs = %lu\n", count_i);

    }
    
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Cipher.AES as AES" );

  test_fini();

  return 0;
}

// ============================================================================
