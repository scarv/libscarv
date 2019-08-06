/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/hash/sha2/sha2_256.h>
#include <scarv/share/xcrypto_intrinsics.h>

#define SHA2_256_S0(a) ( _xc_sha256_s0(a) )
#define SHA2_256_S1(a) ( _xc_sha256_s1(a) )
#define SHA2_256_S2(a) ( _xc_sha256_s2(a) )
#define SHA2_256_S3(a) ( _xc_sha256_s3(a) )

#define SHA2_256_F0(a,b,c) ( _xc_bop(a,b,c,0) ) //((a&b) | ( (a|b) & c ) )
#define SHA2_256_F1(a,b,c) ( _xc_bop(a,b,c,1) ) //(c ^ ( a & ( b ^ c ) ) )

#define SHA2_256_R(a,b,c,d,e,f,g,h,w,k) {                               \
  uint32_t t_0 = SHA2_256_S3( e ) + SHA2_256_F1( e, f, g ) + h + w + k; \
  uint32_t t_1 = SHA2_256_S2( a ) + SHA2_256_F0( a, b, c );             \
                                                                        \
  d +=       t_0;                                                       \
  h  = t_1 + t_0;                                                       \
}


void sha2_256_comp( sha2_256_ctx_t* ctx, const uint8_t* x ) {

  //
  // b0 = F0 = (a & b) | ((a|b)&c)
  // b1 = F1 = (c ^ (a & (b ^ c) ))
  //
  // A  B  C | b0  b1
  // --------|----------
  // 0  0  0 | 0   0
  // 0  0  1 | 0   1
  // 0  1  0 | 0   0
  // 0  1  1 | 1   1
  // 1  0  0 | 0   0
  // 1  0  1 | 1   0
  // 1  1  0 | 1   1
  // 1  1  1 | 1   1
  //
  // b0 = 11101000 - 0xE8
  // b1 = 11001010 - 0xCA
  _xc_bop_setup(0xCAE80000);

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
