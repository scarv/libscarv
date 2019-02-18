#include "test_aes.h"

void test_aes_rand( uint8_t* r, int l_r ) {
  FILE* fd = fopen( "/dev/urandom", "rb" ); fread( r, sizeof( uint8_t ), l_r, fd ); fclose( fd );
}

void test_aes_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id );

  for( int i = 0; i < l_x; i++ ) {
    printf( "%02X", x[ i ] );
  }

  printf( "' )\n" );  
}

void test_aes( int n ) {

  printf( "import sys, binascii, Crypto.Cipher.AES as AES\n" );

  #if defined( CONF_AES_ENABLE_ENC )
  for( int i = 0; i < n; i++ ) {
    uint8_t c[ 16 ], m[ 16 ], k[ 16 ];
    
    printf("# aes enc %d / %d\n", i,n);

    test_aes_rand( m, 16 );
    test_aes_rand( k, 16 );

    #if defined( CONF_AES_PRECOMP_RK )  
    uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
    aes_enc_exp( rk, k );
    aes_enc( c, m, rk, AES_ENC_SBOX, AES_MULX);
    #else  
    aes_enc( c, m,  k, AES_ENC_SBOX, AES_MULX);
    #endif  

    test_aes_dump( "m", m, 16 );
    test_aes_dump( "k", k, 16 );
    test_aes_dump( "c", c, 16 );
  
    printf( "t = AES.new( k ).encrypt( m )                  " "\n" );
  
    printf( "if( c != t ) :                                 " "\n" );
    printf( "  print 'failed test_aes: enc'                 " "\n" );
    printf( "  print 'm == %%s' %% ( binascii.b2a_hex( m ) )" "\n" );
    printf( "  print 'k == %%s' %% ( binascii.b2a_hex( k ) )" "\n" );
    printf( "  print 'c == %%s' %% ( binascii.b2a_hex( c ) )" "\n" );
    printf( "  print '  != %%s' %% ( binascii.b2a_hex( t ) )" "\n" );
    printf( "  sys.exit(1)\n");
  }
  #endif

  #if defined( CONF_AES_ENABLE_DEC )
  for( int i = 0; i < n; i++ ) {
    uint8_t m[ 16 ], c[ 16 ], k[ 16 ];

    printf("# aes dec %d / %d\n", i,n);

    test_aes_rand( c, 16 );
    test_aes_rand( k, 16 );


    #if defined( CONF_AES_PRECOMP_RK )  
    printf("# var 1\n");
    uint8_t rk[ ( Nr + 1 ) * ( 4 * Nb ) ];
    aes_dec_exp( rk, k );
    aes_dec( m, c, rk, AES_DEC_SBOX, AES_MULX);
    #else
    printf("# var 2\n");
    aes_dec( m, c,  k, AES_DEC_SBOX, AES_MULX);
    #endif
  
    printf("# done 1\n");
    test_aes_dump( "c", c, 16 );
    test_aes_dump( "k", k, 16 );
    test_aes_dump( "m", m, 16 );
    printf("# done 2\n");
  
    printf( "t = AES.new( k ).decrypt( c )                  " "\n" );
  
    printf( "if( m != t ) :                                 " "\n" );
    printf( "  print 'failed test_aes: dec'                 " "\n" );
    printf( "  print 'c == %%s' %% ( binascii.b2a_hex( c ) )" "\n" );
    printf( "  print 'k == %%s' %% ( binascii.b2a_hex( k ) )" "\n" );
    printf( "  print 'm == %%s' %% ( binascii.b2a_hex( m ) )" "\n" );
    printf( "  print '  != %%s' %% ( binascii.b2a_hex( t ) )" "\n" );
    printf( "  sys.exit(1)\n");
  }
  #endif
}

int main(int argc, char ** argv) {
    test_aes(30);
    return 0;
}


