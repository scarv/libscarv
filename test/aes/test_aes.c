#include "test_aes.h"

FILE* urandom = NULL;

// ============================================================================

void test_aes_rand( uint8_t* r, int l_r ) {
  fread( r, sizeof( uint8_t ), l_r, urandom );
}

void test_aes_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id );

  for( int i = 0; i < l_x; i++ ) {
    printf( "%02X", x[ i ] );
  }

  printf( "' )\n" );  
}

// ============================================================================

#if defined( CONF_AES_ENABLE_ENC )
void test_aes_enc( int n ) {
  for( int i = 0; i < n; i++ ) {    
    printf( "id = 'test_aes:enc[%d/%d]'\n", i, n );

    uint8_t c[ 16 ], m[ 16 ], k[ 16 ];

    #if defined( CONF_AES_PRECOMP_RK )  
    uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
    #endif

    test_aes_rand( m, 16 );
    test_aes_rand( k, 16 );

    test_aes_dump( "m", m, 16 );
    test_aes_dump( "k", k, 16 );

    #if defined( CONF_AES_PRECOMP_RK )  
    aes_enc_exp( rk, k ); MEASURE( aes_enc( c, m, rk, AES_ENC_SBOX, AES_MULX ) );
    #else  
                          MEASURE( aes_enc( c, m,  k, AES_ENC_SBOX, AES_MULX ) );
    #endif  

    test_aes_dump( "c", c, 16 );
  
    printf( "t = AES.new( k ).encrypt( m )                     " "\n"   );
  
    printf( "if( c != t ) :                                    " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'm == %%s' %% ( binascii.b2a_hex( m ) ) )" "\n"   );
    printf( "  print( 'k == %%s' %% ( binascii.b2a_hex( k ) ) )" "\n"   );
    printf( "  print( 'c == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}
#endif

#if defined( CONF_AES_ENABLE_DEC )
void test_aes_dec( int n ) {
  for( int i = 0; i < n; i++ ) {    
    printf( "id = 'test_aes:dec[%d/%d]'\n", i, n );

    uint8_t m[ 16 ], c[ 16 ], k[ 16 ];

    #if defined( CONF_AES_PRECOMP_RK )  
    uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
    #endif

    test_aes_rand( c, 16 );
    test_aes_rand( k, 16 );

    test_aes_dump( "c", c, 16 );
    test_aes_dump( "k", k, 16 );

    #if defined( CONF_AES_PRECOMP_RK )  
    aes_dec_exp( rk, k ); MEASURE( aes_dec( m, c, rk, AES_DEC_SBOX, AES_MULX ) );
    #else  
                          MEASURE( aes_dec( m, c,  k, AES_DEC_SBOX, AES_MULX ) );
    #endif  

    test_aes_dump( "m", m, 16 );
  
    printf( "t = AES.new( k ).decrypt( c )                     " "\n"   );
  
    printf( "if( m != t ) :                                    " "\n"   );
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
  opt_parse( argc, argv );

  if( NULL == ( urandom = fopen( "/dev/urandom", "rb" ) ) ) {
    abort();
  }

  printf( "import sys, binascii, Crypto.Cipher.AES as AES\n" );

  #if defined( CONF_AES_ENABLE_ENC )
  test_aes_enc( opt_trials );
  #endif
  #if defined( CONF_AES_ENABLE_DEC )
  test_aes_dec( opt_trials );
  #endif

  fclose( urandom );

  return 0;
}

// ============================================================================
