/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/stream/chacha20/chacha20.h>

#if ( LIBSCARV_CONF_CHACHA20_BLOCK_EXTERN )
extern void chacha20_block( uint32_t* r, uint32_t* x );
#else 
       void chacha20_block( uint32_t* r, uint32_t* x ) {
  uint32_t t[ 16 ];

  for( int i = 0; i < 16; i++ ) {
    t[ i ] = x[ i ];
  }

  #undef  CHACHA20_QR
  #define CHACHA20_QR(a,b,c,d) {            \
      a += b; d ^= a; d = U32_RTL( d, 16 ); \
      c += d; b ^= c; b = U32_RTL( b, 12 ); \
      a += b; d ^= a; d = U32_RTL( d,  8 ); \
      c += d; b ^= c; b = U32_RTL( b,  7 ); \
  }

  for( int i = 0; i < 10; i++ ) {
    CHACHA20_QR( t[  0 ], t[  4 ], t[  8 ], t[ 12 ] );
    CHACHA20_QR( t[  1 ], t[  5 ], t[  9 ], t[ 13 ] );
    CHACHA20_QR( t[  2 ], t[  6 ], t[ 10 ], t[ 14 ] );
    CHACHA20_QR( t[  3 ], t[  7 ], t[ 11 ], t[ 15 ] );

    CHACHA20_QR( t[  0 ], t[  5 ], t[ 10 ], t[ 15 ] );
    CHACHA20_QR( t[  1 ], t[  6 ], t[ 11 ], t[ 12 ] );
    CHACHA20_QR( t[  2 ], t[  7 ], t[  8 ], t[ 13 ] );
    CHACHA20_QR( t[  3 ], t[  4 ], t[  9 ], t[ 14 ] );
  }

  for( int i = 0; i < 16; i++ ) {
    r[ i ] = x[ i ] + t[ i ];
  }
}
#endif

#if ( LIBSCARV_CONF_CHACHA20_PROCESS_EXTERN )
extern void chacha20_process( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* x, int l );
#else
void chacha20_process( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* x, int l ) {
  chacha20_ctx_t t;

  for( int i = 0; i < ( l / 64 ); i++ ) {
    chacha20_block( t.w, ctx->w );
    ctx->w[ 12 ]++; // inc. counter in word 12 of state

    for( int j = 0; j < (          64 ); j++ ) {
      r[ 64 * i + j ] = x[ 64 * i + j ] ^ t.b[ j ];
    }
  }

  if( ( l % 64 ) != 0 ) {
    int i = l / 64;

    chacha20_block( t.w, ctx->w );
    ctx->w[ 12 ]++; // inc. counter in word 12 of state

    for( int j = 0; j < ( l % 64 ); j++ ) {
      r[ 64 * i + j ] = x[ 64 * i + j ] ^ t.b[ j ];
    }
  }
}
#endif

void chacha20_init( chacha20_ctx_t* ctx, uint8_t* k, uint8_t* counter, uint8_t* nonce ) {
  uint8_t* b = ctx->b;

  ctx->w[ 0 ] = 0x61707865;                                          b += sizeof( uint32_t );
  ctx->w[ 1 ] = 0x3320646e;                                          b += sizeof( uint32_t );
  ctx->w[ 2 ] = 0x79622d32;                                          b += sizeof( uint32_t );
  ctx->w[ 3 ] = 0x6b206574;                                          b += sizeof( uint32_t );

  memcpy( b,       k, CHACHA20_SIZEOF_KEY     * sizeof( uint8_t ) ); b += CHACHA20_SIZEOF_KEY;
  memcpy( b, counter, CHACHA20_SIZEOF_COUNTER * sizeof( uint8_t ) ); b += CHACHA20_SIZEOF_COUNTER;
  memcpy( b,   nonce, CHACHA20_SIZEOF_NONCE   * sizeof( uint8_t ) ); b += CHACHA20_SIZEOF_NONCE;
}

void chacha20_enc( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* m, int l ) {
  chacha20_process( ctx, r, m, l );
}

void chacha20_dec( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* c, int l ) {
  chacha20_process( ctx, r, c, l );
}
