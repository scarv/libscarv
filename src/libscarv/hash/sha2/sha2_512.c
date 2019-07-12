/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/hash/sha2/sha2_512.h>

#define SHA2_512_S0(a) ( U64_RTR( a,  1 ) ^ U64_RTR( a,  8 ) ^ U64_SHR( a,  7 ) )
#define SHA2_512_S1(a) ( U64_RTR( a, 19 ) ^ U64_RTR( a, 61 ) ^ U64_SHR( a,  6 ) )
#define SHA2_512_S2(a) ( U64_RTR( a, 28 ) ^ U64_RTR( a, 34 ) ^ U64_RTR( a, 39 ) )
#define SHA2_512_S3(a) ( U64_RTR( a, 14 ) ^ U64_RTR( a, 18 ) ^ U64_RTR( a, 41 ) )

#define SHA2_512_F0(a,b,c) ( ( a & b ) | ( ( a | b ) & c ) )
#define SHA2_512_F1(a,b,c) ( c ^ ( a & ( b ^ c ) ) )

#define SHA2_512_R(a,b,c,d,e,f,g,h,w,k) {                               \
  uint64_t t_0 = SHA2_512_S3( e ) + SHA2_512_F1( e, f, g ) + h + w + k; \
  uint64_t t_1 = SHA2_512_S2( a ) + SHA2_512_F0( a, b, c );             \
                                                                        \
  d +=       t_0;                                                       \
  h  = t_1 + t_0;                                                       \
}

uint64_t SHA2_512_K[] = { 
  0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
  0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
  0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
  0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
  0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
  0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
  0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
  0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
  0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
  0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B,
  0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
  0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
  0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
  0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
  0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
  0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B,
  0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
  0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
  0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
  0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817 
};

#if ( LIBSCARV_CONF_SHA2_512_COMP_EXTERN )
extern void sha2_512_comp( sha2_512_ctx_t* ctx, const uint8_t* x );
#else
       void sha2_512_comp( sha2_512_ctx_t* ctx, const uint8_t* x ) {

  uint64_t a = ctx->H[ 0 ];
  uint64_t b = ctx->H[ 1 ];
  uint64_t c = ctx->H[ 2 ];
  uint64_t d = ctx->H[ 3 ];
  uint64_t e = ctx->H[ 4 ];
  uint64_t f = ctx->H[ 5 ];
  uint64_t g = ctx->H[ 6 ];
  uint64_t h = ctx->H[ 7 ];

  U8_TO_U64_BE( ctx->W[  0 ], x,   0 );
  U8_TO_U64_BE( ctx->W[  1 ], x,   8 );
  U8_TO_U64_BE( ctx->W[  2 ], x,  16 );
  U8_TO_U64_BE( ctx->W[  3 ], x,  24 );
  U8_TO_U64_BE( ctx->W[  4 ], x,  32 );
  U8_TO_U64_BE( ctx->W[  5 ], x,  40 );
  U8_TO_U64_BE( ctx->W[  6 ], x,  48 );
  U8_TO_U64_BE( ctx->W[  7 ], x,  56 );
  U8_TO_U64_BE( ctx->W[  8 ], x,  64 );
  U8_TO_U64_BE( ctx->W[  9 ], x,  72 );
  U8_TO_U64_BE( ctx->W[ 10 ], x,  80 );
  U8_TO_U64_BE( ctx->W[ 11 ], x,  88 );
  U8_TO_U64_BE( ctx->W[ 12 ], x,  96 );
  U8_TO_U64_BE( ctx->W[ 13 ], x, 104 );
  U8_TO_U64_BE( ctx->W[ 14 ], x, 112 );
  U8_TO_U64_BE( ctx->W[ 15 ], x, 120 );

  for( int i = 16; i < 80; i += 1 ) {
    ctx->W[ i ] = SHA2_512_S1( ctx->W[ i -  2 ] ) + ( ctx->W[ i -  7 ] ) +
                  SHA2_512_S0( ctx->W[ i - 15 ] ) + ( ctx->W[ i - 16 ] ) ;
  }

  for( int i =  0; i < 80; i += 8 ) {
    SHA2_512_R( a, b, c, d, e, f, g, h, ctx->W[ i + 0 ], SHA2_512_K[ i + 0 ] );
    SHA2_512_R( h, a, b, c, d, e, f, g, ctx->W[ i + 1 ], SHA2_512_K[ i + 1 ] );
    SHA2_512_R( g, h, a, b, c, d, e, f, ctx->W[ i + 2 ], SHA2_512_K[ i + 2 ] );
    SHA2_512_R( f, g, h, a, b, c, d, e, ctx->W[ i + 3 ], SHA2_512_K[ i + 3 ] );
    SHA2_512_R( e, f, g, h, a, b, c, d, ctx->W[ i + 4 ], SHA2_512_K[ i + 4 ] );
    SHA2_512_R( d, e, f, g, h, a, b, c, ctx->W[ i + 5 ], SHA2_512_K[ i + 5 ] );
    SHA2_512_R( c, d, e, f, g, h, a, b, ctx->W[ i + 6 ], SHA2_512_K[ i + 6 ] );
    SHA2_512_R( b, c, d, e, f, g, h, a, ctx->W[ i + 7 ], SHA2_512_K[ i + 7 ] );
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

void sha2_512_pad( sha2_512_ctx_t* ctx, uint8_t* x ) {
  int n_b = SHA2_512_SIZEOF_BLOCK;

  ctx->n_done = ( ctx->n_done + ctx->n_left ) * 8;

  x[ ctx->n_left++ ] = 0x80;

  if   ( ctx->n_left > ( n_b - ( 2 * SIZEOF( uint64_t ) ) ) ) {
    while( ctx->n_left < n_b ) {
      x[ ctx->n_left++ ] = 0x00;
    }

    sha2_512_comp( ctx, x );

    ctx->n_left = 0;
  }

  while( ctx->n_left < ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    x[ ctx->n_left++ ] = 0x00;
  }

  U64_TO_U8_BE( x, ctx->n_done, ctx->n_left );

  sha2_512_comp( ctx, x );
}

void sha2_512_init( sha2_512_ctx_t* ctx ) {
  ctx->H[ 0 ] = 0x6A09E667F3BCC908;
  ctx->H[ 1 ] = 0xBB67AE8584CAA73B;
  ctx->H[ 2 ] = 0x3C6EF372FE94F82B;
  ctx->H[ 3 ] = 0xA54FF53A5F1D36F1;
  ctx->H[ 4 ] = 0x510E527FADE682D1;
  ctx->H[ 5 ] = 0x9B05688C2B3E6C1F;
  ctx->H[ 6 ] = 0x1F83D9ABFB41BD6B;
  ctx->H[ 7 ] = 0x5BE0CD19137E2179;

  ctx->n_left = 0;
  ctx->n_done = 0;
}

void sha2_512_hash( sha2_512_ctx_t* ctx, const uint8_t* m, int n_m ) {
  int n_b = SHA2_512_SIZEOF_BLOCK;

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

      sha2_512_comp( ctx, ctx->B );
    }
  }

  while( n_m >= n_b ) {
    sha2_512_comp( ctx, m );

    ctx->n_done += n_b;
         m      += n_b;
         n_m    -= n_b;
  }

  if( n_m > 0 ) {
    memcpy( ctx->B, m, ctx->n_left = n_m );
  }
}

void sha2_512_fini( sha2_512_ctx_t* ctx, uint8_t* d ) {
  sha2_512_pad( ctx, ctx->B );

  U64_TO_U8_BE( d, ctx->H[ 0 ],  0 );
  U64_TO_U8_BE( d, ctx->H[ 1 ],  8 );
  U64_TO_U8_BE( d, ctx->H[ 2 ], 16 );
  U64_TO_U8_BE( d, ctx->H[ 3 ], 24 );
  U64_TO_U8_BE( d, ctx->H[ 4 ], 32 );
  U64_TO_U8_BE( d, ctx->H[ 5 ], 40 );
  U64_TO_U8_BE( d, ctx->H[ 6 ], 48 );
  U64_TO_U8_BE( d, ctx->H[ 7 ], 56 );
}

void sha2_512( uint8_t* d, int l, ... ) {
  va_list a; sha2_512_ctx_t ctx;

  sha2_512_init( &ctx );
  va_start( a, l );

  for( int i = 0; i < l; i++ ) {
    uint8_t* m   = va_arg( a, uint8_t* );
    int      n_m = va_arg( a,  int     );

    sha2_512_hash( &ctx, m, n_m );
  }

  va_end( a );
  sha2_512_fini( &ctx, d );
}
