/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_sm4.h"

// ============================================================================

void test_sm4_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}

// ============================================================================

test_sm4_kat_t test_sm4_kat[] = { { 
    .m     = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 },
    .c     = { 0x68, 0x1e, 0xdf, 0x34, 0xd2, 0x06, 0x96, 0x5e, 0x86, 0xb3, 0xe9, 0x4f, 0x53, 0x6e, 0x42, 0x46 },
    #if ( LIBSCARV_CONF_SM4_KEY_EVOLVE_FWD )
    .k_enc = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 },
    .k_dec = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 }
    #endif
    #if ( LIBSCARV_CONF_SM4_KEY_EVOLVE_REV )
    .k_enc = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 },
    .k_dec = { 0x42, 0x8D, 0x36, 0x54, 0x62, 0x29, 0x34, 0x96, 0x01, 0xCF, 0x72, 0xE5, 0x91, 0x24, 0xA0, 0x12 }
    #endif
  } 
};

void test_sm4_enc( int trials ) {
  uint8_t t[ 16 ], c[ 16 ], m[ 16 ], k[ 16 ];

  #if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )  
  uint32_t rk[ 32 ];
  #endif

  for( int i = 1; i <= trials; i++ ) { 
    test_id( "test_sm4", "enc", i, trials );

    memcpy( m, test_sm4_kat[ i - 1 ].m,     16 * SIZEOF( uint8_t ) );
    memcpy( c, test_sm4_kat[ i - 1 ].c,     16 * SIZEOF( uint8_t ) );
    memcpy( k, test_sm4_kat[ i - 1 ].k_enc, 16 * SIZEOF( uint8_t ) );

    test_sm4_dump( "m", m, 16 );
    test_sm4_dump( "k", k, 16 );

    #if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )  
    sm4_enc_exp( rk, k ); MEASURE( sm4_enc( t, m, ( uint8_t* )( rk ) ) );
    #else  
                          MEASURE( sm4_enc( t, m,                k   ) );
    #endif  

    test_sm4_dump( "t", t, 16 );
    test_sm4_dump( "c", c, 16 );

    printf( "if ( c != t ) :                                   " "\n"   );
    printf( "  print( 'fail %%s' %% ( id                    ) )" "\n"   );
    printf( "  print( 'm == %%s' %% ( binascii.b2a_hex( m ) ) )" "\n"   );
    printf( "  print( 'k == %%s' %% ( binascii.b2a_hex( k ) ) )" "\n"   );
    printf( "  print( 'c == %%s' %% ( binascii.b2a_hex( c ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( binascii.b2a_hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                                   " "\n\n" );
  }
}

void test_sm4_dec( int trials ) {
  uint8_t m[ 16 ], c[ 16 ], k[ 16 ], t[ 16 ];

  #if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )  
  uint32_t rk[ 32 ];
  #endif

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_sm4", "dec", i, trials );

    memcpy( m, test_sm4_kat[ i - 1 ].m,     16 * SIZEOF( uint8_t ) );
    memcpy( c, test_sm4_kat[ i - 1 ].c,     16 * SIZEOF( uint8_t ) );
    memcpy( k, test_sm4_kat[ i - 1 ].k_dec, 16 * SIZEOF( uint8_t ) );

    test_sm4_dump( "c", c, 16 );
    test_sm4_dump( "k", k, 16 );

    #if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )  
    sm4_dec_exp( rk, k ); MEASURE( sm4_dec( t, c, ( uint8_t* )( rk ) ) );
    #else  
                          MEASURE( sm4_dec( t, c,                k   ) );
    #endif  

    test_sm4_dump( "t", t, 16 );
    test_sm4_dump( "m", m, 16 );

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
  test_init( argc, argv, "sys, binascii" );

  test_sm4_enc( TEST_SM4_KAT_COUNT );
  test_sm4_dec( TEST_SM4_KAT_COUNT );

  test_fini();

  return 0;
}

// ============================================================================
