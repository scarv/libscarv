/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_sha3.h"

// ============================================================================

void test_keccak_dump ( char * id, uint8_t * x, int l_x) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}

void test_keccak_p1600_absorb (
    uint8_t *       x    ,
    int             l_x  ,
    tKeccak1600Lane  state[25]
){
      KeccakP1600_Initialize(state);

      int       i   = 0;
      int       l_s = 200;
      uint8_t*  x_p = x;
      while(i < (l_x - (l_x %200))) {

          KeccakP1600_AddBytes(state, x_p, 0, l_s);

          KeccakP1600_Permute_24rounds(state);

          x_p += l_s;
          i   += l_s;
      }

      KeccakP1600_AddBytes(state, x_p, 0, l_x-i);
      KeccakP1600_Permute_24rounds(state);
      
}

void test_keccak_p1600( int n, int l_min, int l_max ) {
  
  tKeccak1600Lane state[25];

  for(int tid = 0; tid < n; tid ++) {

      test_id("test_keccakp1600", "keccakp1600", tid, n);
  
      uint8_t* x    = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );
      int      l_x  = test_rand_seq(x, l_min, l_max, sizeof(uint8_t));

      test_keccak_dump("x", x, l_x);
      printf("l_x = %d\n", l_x);

      MEASURE(
        test_keccak_p1600_absorb(
            x,
            l_x,
            state
        )
      )

      test_keccak_dump("s", (uint8_t*)state, 200);

  }

}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, hashlib" );

  test_keccak_p1600(opt_trials, opt_data_min, opt_data_max );

  test_fini();

  return 0;
}

// ============================================================================
