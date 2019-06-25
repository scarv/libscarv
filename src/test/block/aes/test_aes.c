#include "test_aes.h"

// ============================================================================

void test_aes_dump( char* id, uint8_t* x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_lsb( x, 16 ); printf( "' )\n" );
}

int test_aes_rand( uint8_t* r ) {
  return test_rand_seq( r, 16, 16, sizeof( uint8_t ) );
}

// ============================================================================

#if ( LIBSCARV_CONF_AES_ENC_ENABLE )
void test_aes_enc( int n ) {
  uint8_t c[ 16 ], m[ 16 ], k[ 16 ];

  #if ( LIBSCARV_CONF_AES_PRECOMP_RK )  
  uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
  #endif

  for( int i = 1; i <= n; i++ ) {    
    test_id( "test_aes", "end", i, n );
    
    test_aes_rand(      m );
    test_aes_rand(      k );

    test_aes_dump( "m", m );
    test_aes_dump( "k", k );

    #if ( LIBSCARV_CONF_AES_PRECOMP_RK )  
    aes_enc_exp( rk, k ); TEST_MEASURE( aes_enc( c, m, rk, AES_ENC_SBOX, AES_MULX ) );
    #else  
                          TEST_MEASURE( aes_enc( c, m,  k, AES_ENC_SBOX, AES_MULX ) );
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
#endif

#if ( LIBSCARV_CONF_AES_DEC_ENABLE )
void test_aes_dec( int n ) {
  uint8_t m[ 16 ], c[ 16 ], k[ 16 ];

  #if ( LIBSCARV_CONF_AES_PRECOMP_RK )  
  uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
  #endif

  for( int i = 1; i <= n; i++ ) {    
    test_id( "test_aes", "dec", i, n );

    test_aes_rand(      c );
    test_aes_rand(      k );

    test_aes_dump( "c", c );
    test_aes_dump( "k", k );

    #if ( LIBSCARV_CONF_AES_PRECOMP_RK )  
    aes_dec_exp( rk, k ); TEST_MEASURE( aes_dec( m, c, rk, AES_DEC_SBOX, AES_MULX ) );
    #else  
                          TEST_MEASURE( aes_dec( m, c,  k, AES_DEC_SBOX, AES_MULX ) );
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
#endif

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Cipher.AES as AES" );

  printf( "%d\n", LIBSCARV_CONF_AES_ENC_ENABLE );
  printf( "%d\n", LIBSCARV_CONF_AES_DEC_ENABLE );

  #if ( LIBSCARV_CONF_AES_ENC_ENABLE )
  test_aes_enc( opt_trials );
  #endif
  #if ( LIBSCARV_CONF_AES_DEC_ENABLE )
  test_aes_dec( opt_trials );
  #endif

  test_fini();

  return 0;
}

// ============================================================================
