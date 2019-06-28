/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_sha1.h"

// ============================================================================

void test_sha1_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_lsb( x, l_x ); printf( "' )\n" );
}

int test_sha1_rand( uint8_t* r, int l_r_min, int l_r_max ) {
  return test_rand_seq( r, l_r_min, l_r_max, sizeof( uint8_t ) );
}

// ============================================================================

void test_sha1( int n, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) ), r[ SHA1_SIZEOF_DIGEST ];

  for( int i = 1; i <= n; i++ ) {
    test_id( "test_sha1", "sha1", i, n );

    int l_r = SHA1_SIZEOF_DIGEST, l_x = test_sha1_rand( x, l_min, l_max );

    test_sha1_dump( "x", x, l_x );

    TEST_MEASURE( sha1( r, 1, x, l_x ) );

    test_sha1_dump( "r", r, l_r );

    printf( "t = SHA1.new( x ).digest()                        " "\n"   );
  
    printf( "if ( r != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }

  free( x );
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Hash.SHA as SHA1" );

  test_sha1( opt_trials, opt_sha1_min_data, opt_sha1_max_data );

  test_fini();

  return 0;
}

// ============================================================================
