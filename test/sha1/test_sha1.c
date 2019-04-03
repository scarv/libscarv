#include "test_sha1.h"

// ============================================================================

int test_sha1_rand( uint8_t* r, int l_r_min, int l_r_max ) {
  return test_rand_byte( r, sizeof( uint8_t ), l_r_min, l_r_max );
}

void test_sha1_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_lsb( x, l_x ); printf( "' )\n" );
}

// ============================================================================

void test_sha1( int n, int l_min, int l_max ) {
  uint8_t* x = ( uint8_t* )( malloc( opt_sha1_max_data ) ), r[ SHA1_SIZEOF_DIGEST ];

  for( int i = 0; i < n; i++ ) {
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
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Hash.SHA as SHA1" );

  test_sha1( opt_trials, opt_sha1_min_data, opt_sha1_max_data );

  test_fini();

  return 0;
}

// ============================================================================
