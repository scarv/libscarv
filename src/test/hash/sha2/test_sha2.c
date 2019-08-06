/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_sha2.h"

// ============================================================================

void test_sha2_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}

// ============================================================================

void test_sha2_256( int trials, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) ), r[ SHA2_256_SIZEOF_DIGEST ];

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_sha2", "sha2_256", i, trials );

    int l_r = SHA2_256_SIZEOF_DIGEST, l_x = test_rand_seq( x, l_min, l_max, sizeof( uint8_t ) );

    test_sha2_dump( "x", x, l_x );

    MEASURE( sha2_256( r, 1, x, l_x ) );

    test_sha2_dump( "r", r, l_r );

    printf("l_x = %d\n", l_x);
    printf("l_r = %d\n", l_r);

    printf( "t = SHA2_256.new( x ).digest()                    " "\n"   );
  
    printf( "if ( r != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( x ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }

  free( x );
}

void test_sha2_512( int trials, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) ), r[ SHA2_512_SIZEOF_DIGEST ];

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_sha2", "sha2_512", i, trials );

    int l_r = SHA2_512_SIZEOF_DIGEST, l_x = test_rand_seq( x, l_min, l_max, sizeof( uint8_t ) );

    test_sha2_dump( "x", x, l_x );

    MEASURE( sha2_512( r, 1, x, l_x ) );

    test_sha2_dump( "r", r, l_r );

    printf( "t = SHA2_512.new( x ).digest()                    " "\n"   );
  
    printf( "if ( r != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( x ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }

  free( x );
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Hash.SHA256 as SHA2_256, Crypto.Hash.SHA512 as SHA2_512" );

  test_sha2_256( opt_trials, opt_data_min, opt_data_max );
  test_sha2_512( opt_trials, opt_data_min, opt_data_max );

  test_fini();

  return 0;
}

// ============================================================================
