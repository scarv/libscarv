#include "test_sha2.h"

// ============================================================================

int test_sha2_rand( uint8_t* r, int l_r_min, int l_r_max ) {
  return test_rand_byte( r, sizeof( uint8_t ), l_r_min, l_r_max );
}

void test_sha2_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_lsb( x, l_x ); printf( "' )\n" );
}

// ============================================================================

void test_sha2_256( int n, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( opt_sha2_max_data ) ), r[ SHA2_256_SIZEOF_DIGEST ];

  for( int i = 0; i < n; i++ ) {
    test_id( "test_sha2", "sha2_256", i, n );

    int l_r = SHA2_256_SIZEOF_DIGEST, l_x = test_sha2_rand( x, l_min, l_max );

    test_sha2_dump( "x", x, l_x );

    TEST_MEASURE( sha2_256( r, 1, x, l_x ) );

    test_sha2_dump( "r", r, l_r );

    printf( "t = SHA2_256.new( x ).digest()                    " "\n"   );
  
    printf( "if ( r != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}

void test_sha2_512( int n, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( opt_sha2_max_data ) ), r[ SHA2_512_SIZEOF_DIGEST ];

  for( int i = 0; i < n; i++ ) {
    test_id( "test_sha2", "sha2_512", i, n );

    int l_r = SHA2_512_SIZEOF_DIGEST, l_x = test_sha2_rand( x, l_min, l_max );

    test_sha2_dump( "x", x, l_x );

    TEST_MEASURE( sha2_512( r, 1, x, l_x ) );

    test_sha2_dump( "r", r, l_r );

    printf( "t = SHA2_512.new( x ).digest()                    " "\n"   );
  
    printf( "if ( r != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( binascii.b2a_hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Hash.SHA256 as SHA2_256, Crypto.Hash.SHA512 as SHA2_512" );

  test_sha2_256( opt_trials, opt_sha2_min_data, opt_sha2_max_data );
  test_sha2_512( opt_trials, opt_sha2_min_data, opt_sha2_max_data );

  test_fini();

  return 0;
}

// ============================================================================
