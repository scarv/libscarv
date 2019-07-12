/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/hash/sha2/sha2_256.h>

#define SHA2_256_S0(a) ( U32_RTR( a,  7 ) ^ U32_RTR( a, 18 ) ^ U32_SHR( a,  3 ) )
#define SHA2_256_S1(a) ( U32_RTR( a, 17 ) ^ U32_RTR( a, 19 ) ^ U32_SHR( a, 10 ) )
#define SHA2_256_S2(a) ( U32_RTR( a,  2 ) ^ U32_RTR( a, 13 ) ^ U32_RTR( a, 22 ) )
#define SHA2_256_S3(a) ( U32_RTR( a,  6 ) ^ U32_RTR( a, 11 ) ^ U32_RTR( a, 25 ) )

#define SHA2_256_F0(a,b,c) ( ( a & b ) | ( ( a | b ) & c ) )
#define SHA2_256_F1(a,b,c) ( c ^ ( a & ( b ^ c ) ) )

#define SHA2_256_R(a,b,c,d,e,f,g,h,w,k) {                               \
  uint32_t t_0 = SHA2_256_S3( e ) + SHA2_256_F1( e, f, g ) + h + w + k; \
  uint32_t t_1 = SHA2_256_S2( a ) + SHA2_256_F0( a, b, c );             \
                                                                        \
  d +=       t_0;                                                       \
  h  = t_1 + t_0;                                                       \
}
  
uint32_t SHA2_256_K[] = { 
  0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 
  0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 
  0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 
  0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 
  0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
  0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, 
  0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 
  0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, 
  0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 
  0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
  0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 
  0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, 
  0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 
  0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,  
  0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
  0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2 
};
        
#if ( LIBSCARV_CONF_SHA2_256_COMP_EXTERN )
extern void sha2_256_comp( sha2_256_ctx_t* ctx, const uint8_t* x );
#else
       void sha2_256_comp( sha2_256_ctx_t* ctx, const uint8_t* x ) {

  uint32_t a = ctx->H[ 0 ];
  uint32_t b = ctx->H[ 1 ];
  uint32_t c = ctx->H[ 2 ];
  uint32_t d = ctx->H[ 3 ];
  uint32_t e = ctx->H[ 4 ];
  uint32_t f = ctx->H[ 5 ];
  uint32_t g = ctx->H[ 6 ];
  uint32_t h = ctx->H[ 7 ];

  U8_TO_U32_BE( ctx->W[  0 ], x,  0 );
  U8_TO_U32_BE( ctx->W[  1 ], x,  4 );
  U8_TO_U32_BE( ctx->W[  2 ], x,  8 );
  U8_TO_U32_BE( ctx->W[  3 ], x, 12 );
  U8_TO_U32_BE( ctx->W[  4 ], x, 16 );
  U8_TO_U32_BE( ctx->W[  5 ], x, 20 );
  U8_TO_U32_BE( ctx->W[  6 ], x, 24 );
  U8_TO_U32_BE( ctx->W[  7 ], x, 28 );
  U8_TO_U32_BE( ctx->W[  8 ], x, 32 );
  U8_TO_U32_BE( ctx->W[  9 ], x, 36 );
  U8_TO_U32_BE( ctx->W[ 10 ], x, 40 );
  U8_TO_U32_BE( ctx->W[ 11 ], x, 44 );
  U8_TO_U32_BE( ctx->W[ 12 ], x, 48 );
  U8_TO_U32_BE( ctx->W[ 13 ], x, 52 );
  U8_TO_U32_BE( ctx->W[ 14 ], x, 56 );
  U8_TO_U32_BE( ctx->W[ 15 ], x, 60 );

  for( int i = 16; i < 64; i += 1 ) {
    ctx->W[ i ] = SHA2_256_S1( ctx->W[ i -  2 ] ) + ( ctx->W[ i -  7 ] ) +
                  SHA2_256_S0( ctx->W[ i - 15 ] ) + ( ctx->W[ i - 16 ] ) ;
  }

  for( int i =  0; i < 64; i += 8 ) {
    SHA2_256_R( a, b, c, d, e, f, g, h, ctx->W[ i + 0 ], SHA2_256_K[ i + 0 ] );
    SHA2_256_R( h, a, b, c, d, e, f, g, ctx->W[ i + 1 ], SHA2_256_K[ i + 1 ] );
    SHA2_256_R( g, h, a, b, c, d, e, f, ctx->W[ i + 2 ], SHA2_256_K[ i + 2 ] );
    SHA2_256_R( f, g, h, a, b, c, d, e, ctx->W[ i + 3 ], SHA2_256_K[ i + 3 ] );
    SHA2_256_R( e, f, g, h, a, b, c, d, ctx->W[ i + 4 ], SHA2_256_K[ i + 4 ] );
    SHA2_256_R( d, e, f, g, h, a, b, c, ctx->W[ i + 5 ], SHA2_256_K[ i + 5 ] );
    SHA2_256_R( c, d, e, f, g, h, a, b, ctx->W[ i + 6 ], SHA2_256_K[ i + 6 ] );
    SHA2_256_R( b, c, d, e, f, g, h, a, ctx->W[ i + 7 ], SHA2_256_K[ i + 7 ] );
  }

  ctx->H[ 0 ] += a;
  ctx->H[ 1 ] += b;
  ctx->H[ 2 ] += c;
  ctx->H[ 3 ] += d;
  ctx->H[ 4 ] += e;
  ctx->H[ 5 ] += f;
  ctx->H[ 6 ] += g;
  ctx->H[ 7 ] += h;
}
#endif

void sha2_256_pad( sha2_256_ctx_t* ctx, uint8_t* x ) {
  int n_b = SHA2_256_SIZEOF_BLOCK;

  ctx->n_done = ( ctx->n_done + ctx->n_left ) * 8;

  x[ ctx->n_left++ ] = 0x80;

  if   ( ctx->n_left > ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    while( ctx->n_left < n_b ) {
      x[ ctx->n_left++ ] = 0x00;
    }

    sha2_256_comp( ctx, x );

    ctx->n_left = 0;
  }

  while( ctx->n_left < ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    x[ ctx->n_left++ ] = 0x00;
  }

  U64_TO_U8_BE( x, ctx->n_done, ctx->n_left );

  sha2_256_comp( ctx, x );
}

void sha2_256_init( sha2_256_ctx_t* ctx ) {
  ctx->H[ 0 ] = 0x6A09E667;
  ctx->H[ 1 ] = 0xBB67AE85;
  ctx->H[ 2 ] = 0x3C6EF372;
  ctx->H[ 3 ] = 0xA54FF53A;
  ctx->H[ 4 ] = 0x510E527F;
  ctx->H[ 5 ] = 0x9B05688C;
  ctx->H[ 6 ] = 0x1F83D9AB;
  ctx->H[ 7 ] = 0x5BE0CD19;

  ctx->n_left = 0;
  ctx->n_done = 0;
}

void sha2_256_hash( sha2_256_ctx_t* ctx, const uint8_t* m, int n_m ) {
  int n_b = SHA2_256_SIZEOF_BLOCK;

  if( ctx->n_left != 0 ) {
    int n_t = n_b - ctx->n_left;
 
    if( n_t > n_m ) {
      memcpy( ctx->B + ctx->n_left, m, n_m );

      ctx->n_left += n_m;
           n_m     =   0;
    }
    else {
      memcpy( ctx->B + ctx->n_left, m, n_t );

      ctx->n_done += n_b;
      ctx->n_left  =   0;
           n_m    -= n_t;

      sha2_256_comp( ctx, ctx->B );
    }
  }

  while( n_m >= n_b ) {
    sha2_256_comp( ctx, m );

    ctx->n_done += n_b;
         m      += n_b;
         n_m    -= n_b;
  }

  if( n_m > 0 ) {
    memcpy( ctx->B, m, ctx->n_left = n_m );
  }
}

void sha2_256_fini( sha2_256_ctx_t* ctx, uint8_t* d ) {
  sha2_256_pad( ctx, ctx->B );

  U32_TO_U8_BE( d, ctx->H[ 0 ],  0 );
  U32_TO_U8_BE( d, ctx->H[ 1 ],  4 );
  U32_TO_U8_BE( d, ctx->H[ 2 ],  8 );
  U32_TO_U8_BE( d, ctx->H[ 3 ], 12 );
  U32_TO_U8_BE( d, ctx->H[ 4 ], 16 );
  U32_TO_U8_BE( d, ctx->H[ 5 ], 20 );
  U32_TO_U8_BE( d, ctx->H[ 6 ], 24 );
  U32_TO_U8_BE( d, ctx->H[ 7 ], 28 );
}

void sha2_256( uint8_t* d, int l, ... ) {
  va_list a; sha2_256_ctx_t ctx;

  sha2_256_init( &ctx );
  va_start( a, l );

  for( int i = 0; i < l; i++ ) {
    uint8_t* m   = va_arg( a, uint8_t* );
    int      n_m = va_arg( a,  int     );

    sha2_256_hash( &ctx, m, n_m );
  }

  va_end( a );
  sha2_256_fini( &ctx, d );
}
