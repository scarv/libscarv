/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/hash/sha1/sha1.h>

#define SHA1_R(a,b,c,d,e,w,k) {   \
  e += U32_RTL( a,  5 );          \
  e += SHA1_F( b, c, d ) + w + k; \
  b  = U32_RTL( b, 30 );          \
}

#if ( LIBSCARV_CONF_SHA1_COMP_EXTERN )
extern void sha1_comp( sha1_ctx_t* ctx, const uint8_t* x );
#else
       void sha1_comp( sha1_ctx_t* ctx, const uint8_t* x ) {

  uint32_t a = ctx->H[ 0 ];
  uint32_t b = ctx->H[ 1 ];
  uint32_t c = ctx->H[ 2 ];
  uint32_t d = ctx->H[ 3 ];
  uint32_t e = ctx->H[ 4 ];

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

  for( int i = 16; i < 80; i += 1 ) { 
    ctx->W[ i ] = U32_RTL( ctx->W[ i -  3 ] ^ ctx->W[ i -  8 ] ^ ctx->W[ i - 14 ] ^ ctx->W[ i - 16 ], 1 );
  }

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( c ^ ( a & ( b ^ c ) ) )

  SHA1_R( a, b, c, d, e, ctx->W[  0 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, ctx->W[  1 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, ctx->W[  2 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, ctx->W[  3 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, ctx->W[  4 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, ctx->W[  5 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, ctx->W[  6 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, ctx->W[  7 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, ctx->W[  8 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, ctx->W[  9 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, ctx->W[ 10 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, ctx->W[ 11 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, ctx->W[ 12 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, ctx->W[ 13 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, ctx->W[ 14 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, ctx->W[ 15 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, ctx->W[ 16 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, ctx->W[ 17 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, ctx->W[ 18 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, ctx->W[ 19 ], 0x5A827999 );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( a ^ b ^ c )

  SHA1_R( a, b, c, d, e, ctx->W[ 20 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, ctx->W[ 21 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, ctx->W[ 22 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, ctx->W[ 23 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, ctx->W[ 24 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, ctx->W[ 25 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, ctx->W[ 26 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, ctx->W[ 27 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, ctx->W[ 28 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, ctx->W[ 29 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, ctx->W[ 30 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, ctx->W[ 31 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, ctx->W[ 32 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, ctx->W[ 33 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, ctx->W[ 34 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, ctx->W[ 35 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, ctx->W[ 36 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, ctx->W[ 37 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, ctx->W[ 38 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, ctx->W[ 39 ], 0x6ED9EBA1 );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( ( a & b ) | ( ( a | b ) & c ) )

  SHA1_R( a, b, c, d, e, ctx->W[ 40 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, ctx->W[ 41 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, ctx->W[ 42 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, ctx->W[ 43 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, ctx->W[ 44 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, ctx->W[ 45 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, ctx->W[ 46 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, ctx->W[ 47 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, ctx->W[ 48 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, ctx->W[ 49 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, ctx->W[ 50 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, ctx->W[ 51 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, ctx->W[ 52 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, ctx->W[ 53 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, ctx->W[ 54 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, ctx->W[ 55 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, ctx->W[ 56 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, ctx->W[ 57 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, ctx->W[ 58 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, ctx->W[ 59 ], 0x8F1BBCDC );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( a ^ b ^ c )

  SHA1_R( a, b, c, d, e, ctx->W[ 60 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, ctx->W[ 61 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, ctx->W[ 62 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, ctx->W[ 63 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, ctx->W[ 64 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, ctx->W[ 65 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, ctx->W[ 66 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, ctx->W[ 67 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, ctx->W[ 68 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, ctx->W[ 69 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, ctx->W[ 70 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, ctx->W[ 71 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, ctx->W[ 72 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, ctx->W[ 73 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, ctx->W[ 74 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, ctx->W[ 75 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, ctx->W[ 76 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, ctx->W[ 77 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, ctx->W[ 78 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, ctx->W[ 79 ], 0xCA62C1D6 );

  ctx->H[ 0 ] += a;
  ctx->H[ 1 ] += b;
  ctx->H[ 2 ] += c;
  ctx->H[ 3 ] += d;
  ctx->H[ 4 ] += e;
}
#endif

void sha1_pad( sha1_ctx_t* ctx, uint8_t* x ) {
  int n_b = SHA1_SIZEOF_BLOCK;

  ctx->n_done = ( ctx->n_done + ctx->n_left ) * 8;

  x[ ctx->n_left++ ] = 0x80;

  if   ( ctx->n_left > ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    while( ctx->n_left < n_b ) {
      x[ ctx->n_left++ ] = 0x00;
    }

    sha1_comp( ctx, x );

    ctx->n_left = 0;
  }

  while( ctx->n_left < ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    x[ ctx->n_left++ ] = 0x00;
  }

  U64_TO_U8_BE( x, ctx->n_done, ctx->n_left );

  sha1_comp( ctx, x );
}

void sha1_init( sha1_ctx_t* ctx ) {
  ctx->H[ 0 ] = 0x67452301;
  ctx->H[ 1 ] = 0xEFCDAB89;
  ctx->H[ 2 ] = 0x98BADCFE;
  ctx->H[ 3 ] = 0x10325476;
  ctx->H[ 4 ] = 0xC3D2E1F0;

  ctx->n_left = 0;
  ctx->n_done = 0;
}

void sha1_hash( sha1_ctx_t* ctx, const uint8_t* m, int n_m ) {
  int n_b = SHA1_SIZEOF_BLOCK;

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

      sha1_comp( ctx, ctx->B );
    }
  }

  while( n_m >= n_b ) {
    sha1_comp( ctx, m );

    ctx->n_done += n_b;
         m      += n_b;
         n_m    -= n_b;
  }

  if( n_m > 0 ) {
    memcpy( ctx->B, m, ctx->n_left = n_m );
  }
}

void sha1_fini( sha1_ctx_t* ctx, uint8_t* d ) {
  sha1_pad( ctx, ctx->B );

  U32_TO_U8_BE( d, ctx->H[ 0 ],  0 );
  U32_TO_U8_BE( d, ctx->H[ 1 ],  4 );
  U32_TO_U8_BE( d, ctx->H[ 2 ],  8 );
  U32_TO_U8_BE( d, ctx->H[ 3 ], 12 );
  U32_TO_U8_BE( d, ctx->H[ 4 ], 16 );
}

void sha1( uint8_t* d, int l, ... ) {
  va_list a; sha1_ctx_t ctx;

  sha1_init( &ctx );
  va_start( a, l );

  for( int i = 0; i < l; i++ ) {
    uint8_t* m   = va_arg( a, uint8_t* );
    int      n_m = va_arg( a,  int     );

    sha1_hash( &ctx, m, n_m );
  }

  va_end( a );
  sha1_fini( &ctx, d );
}
