/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_chacha20.h"

// ============================================================================

void test_chacha20_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}

// ============================================================================

void test_chacha20_enc( int trials, int l_min, int l_max ) {
  chacha20_ctx_t ctx;

  uint8_t* m = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );
  uint8_t* c = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );

  uint8_t k[ CHACHA20_SIZEOF_KEY ], nonce[ CHACHA20_SIZEOF_NONCE ]; uint32_t counter = 0;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_chacha20", "enc", i, trials );

    int l = test_rand_seq(     m, l_min,                 l_max,                 sizeof( uint8_t ) );
            test_rand_seq(     k, CHACHA20_SIZEOF_KEY,   CHACHA20_SIZEOF_KEY,   sizeof( uint8_t ) );
            test_rand_seq( nonce, CHACHA20_SIZEOF_NONCE, CHACHA20_SIZEOF_NONCE, sizeof( uint8_t ) );
        
    test_chacha20_dump(     "m",     m, l                     );
    test_chacha20_dump(     "k",     k, CHACHA20_SIZEOF_KEY   );
    test_chacha20_dump( "nonce", nonce, CHACHA20_SIZEOF_NONCE );
        
    MEASURE( chacha20_init( &ctx, k, ( uint8_t* )( &counter ), nonce ); chacha20_enc( &ctx, c, m, l ) );
        
    test_chacha20_dump(     "c",     c, l                     );
  
    printf( "t = ChaCha20.new( key = k, nonce = nonce ).encrypt( m )    " "\n"   );
  
    printf( "if ( c != t ) :                                            " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                            ) ) " "\n"   );
    printf( "  print( 'm     == %%s' %% ( binascii.b2a_hex( m     ) ) ) " "\n"   );
    printf( "  print( 'k     == %%s' %% ( binascii.b2a_hex( k     ) ) ) " "\n"   );
    printf( "  print( 'nonce == %%s' %% ( binascii.b2a_hex( nonce ) ) ) " "\n"   );
    printf( "  print( 'c     == %%s' %% ( binascii.b2a_hex( c     ) ) ) " "\n"   );
    printf( "  print( '      != %%s' %% ( binascii.b2a_hex( t     ) ) ) " "\n"   );

    printf( "  sys.exit( 1 )                                            " "\n\n" );
  }
}

void test_chacha20_dec( int trials, int l_min, int l_max ) {
  chacha20_ctx_t ctx;

  uint8_t* c = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );
  uint8_t* m = ( uint8_t* )( malloc( l_max * sizeof( uint8_t ) ) );

  uint8_t k[ CHACHA20_SIZEOF_KEY ], nonce[ CHACHA20_SIZEOF_NONCE ]; uint32_t counter = 0;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_chacha20", "dec", i, trials );

    int l = test_rand_seq(     c, l_min,                 l_max,                 sizeof( uint8_t ) );
            test_rand_seq(     k, CHACHA20_SIZEOF_KEY,   CHACHA20_SIZEOF_KEY,   sizeof( uint8_t ) );
            test_rand_seq( nonce, CHACHA20_SIZEOF_NONCE, CHACHA20_SIZEOF_NONCE, sizeof( uint8_t ) );

    test_chacha20_dump(     "c",     c, l                     );
    test_chacha20_dump(     "k",     k, CHACHA20_SIZEOF_KEY   );
    test_chacha20_dump( "nonce", nonce, CHACHA20_SIZEOF_NONCE );
        
    MEASURE( chacha20_init( &ctx, k, ( uint8_t* )( &counter ), nonce ); chacha20_dec( &ctx, m, c, l ) );
        
    test_chacha20_dump(     "m",     m, l                     );
  
    printf( "t = ChaCha20.new( key = k, nonce = nonce ).decrypt( c )    " "\n"   );
  
    printf( "if ( m != t ) :                                            " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                            ) ) " "\n"   );
    printf( "  print( 'c     == %%s' %% ( binascii.b2a_hex( c     ) ) ) " "\n"   );
    printf( "  print( 'k     == %%s' %% ( binascii.b2a_hex( k     ) ) ) " "\n"   );
    printf( "  print( 'nonce == %%s' %% ( binascii.b2a_hex( nonce ) ) ) " "\n"   );
    printf( "  print( 'm     == %%s' %% ( binascii.b2a_hex( m     ) ) ) " "\n"   );
    printf( "  print( '      != %%s' %% ( binascii.b2a_hex( t     ) ) ) " "\n"   );

    printf( "  sys.exit( 1 )                                            " "\n\n" );
  }    
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Cryptodome.Cipher.ChaCha20 as ChaCha20" );

  test_chacha20_enc( 1, opt_data_max, opt_data_max );
  test_chacha20_dec( 1, opt_data_max, opt_data_max );

  test_fini();

  return 0;
}

// ============================================================================
