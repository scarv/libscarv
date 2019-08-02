/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_sha3.h"

// ============================================================================

void test_sha3_dump ( char * id, uint8_t * x, int l_x) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}

void test_sha3( int n, int l_min, int l_max ) {
  
  for(int tid = 0; tid < n; tid ++) {

      test_id("test_sha3", "sha3", tid, n);
      
      int      l_r  = 64;
      uint8_t* r    = ( uint8_t* )( malloc( l_r   * sizeof( uint8_t ) ) );
      
      uint8_t* x    = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );
      int      l_x  = test_rand_seq(x, l_min, l_max, sizeof(uint8_t));


      MEASURE(
        SHA3_512(r, x, l_x);
      )
      
      test_sha3_dump("x", x, l_x);
      printf("l_x = %d\n", l_x);

      test_sha3_dump("r", (uint8_t*)r, l_r);
    
      printf( "s3 = hashlib.sha3_512()                           " "\n"   );
      printf( "s3.update( x )                                    " "\n"   );
      printf( "t = s3.digest()                                   " "\n"   );
  
      printf( "if ( r != t ) :                                   " "\n"   );
      printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
      printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( x ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                                   " "\n\n" );

  }

}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, hashlib" );

  test_sha3(opt_trials, opt_data_min, opt_data_max );

  test_fini();

  return 0;
}

// ============================================================================
