/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_aes.h"

// ============================================================================

void test_aes_dump( char* id, uint8_t* x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_lsb( x, 16 ); printf( "' )\n" );
}

int test_aes_rand( uint8_t* r ) {
  return test_rand_seq( r, 16, 16, sizeof( uint8_t ) );
}

// ============================================================================

void test_aes_enc( int n ) {
  uint8_t c[ 16 ], m[ 16 ], k[ 16 ];

  #if ( LIBSCARV_CONF_AES_KEY_PRECOMP )  
  uint8_t rk[ ( AES_128_NR + 1 ) * ( 4 * AES_128_NB ) ];
  #endif

  for( int i = 1; i <= n; i++ ) {    
    test_id( "test_aes", "enc", i, n );
    
    test_aes_rand(      m );
    test_aes_rand(      k );

    test_aes_dump( "m", m );
    test_aes_dump( "k", k );

    #if ( LIBSCARV_CONF_AES_KEY_PRECOMP )  
    aes_enc_exp( rk, k ); TEST_MEASURE( aes_enc( c, m, rk ) );
    #else  
                          TEST_MEASURE( aes_enc( c, m,  k ) );
    #endif  

    test_aes_dump( "c", c );
  
    printf( "t = AES.new( k ).encrypt( m )                     " "\n"   );
  
    printf( "if ( c != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'm == %%s' %% ( binascii.b2a_hex( m ) ) )" "\n"   );
    printf( "  print( 'k == %%s' %% ( binascii.b2a_hex( k ) ) )" "\n"   );
    printf( "  print( 'c == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}

void test_aes_dec( int n ) {
  uint8_t m[ 16 ], c[ 16 ], k[ 16 ];

  #if ( LIBSCARV_CONF_AES_KEY_PRECOMP )  
  uint8_t rk[ ( AES_128_NR + 1 ) * ( 4 * AES_128_NB ) ];
  #endif

  for( int i = 1; i <= n; i++ ) {    
    test_id( "test_aes", "dec", i, n );

    test_aes_rand(      c );
    test_aes_rand(      k );

    test_aes_dump( "c", c );
    test_aes_dump( "k", k );

    #if ( LIBSCARV_CONF_AES_KEY_PRECOMP )  
    aes_dec_exp( rk, k ); TEST_MEASURE( aes_dec( m, c, rk ) );
    #else  
                          TEST_MEASURE( aes_dec( m, c,  k ) );
    #endif  

    test_aes_dump( "m", m );
  
    printf( "t = AES.new( k ).decrypt( c )                     " "\n"   );
  
    printf( "if ( m != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'c == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( 'k == %%s' %% ( binascii.b2a_hex( k ) ) )" "\n"   );
    printf( "  print( 'm == %%s' %% ( binascii.b2a_hex( m ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Cipher.AES as AES" );

  test_aes_enc( opt_trials );
  test_aes_dec( opt_trials );

  test_fini();

  return 0;
}

// ============================================================================
