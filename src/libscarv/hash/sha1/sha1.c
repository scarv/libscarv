#include <scarv/hash/sha1/sha1.h>

#define SHA1_R(a,b,c,d,e,w,k) {   \
  e += U32_RTL( a,  5 );          \
  e += SHA1_F( b, c, d ) + w + k; \
  b  = U32_RTL( b, 30 );          \
}

static uint32_t H_0, H_1, H_2, H_3, H_4;

static uint8_t T[ 64 ];

static uint64_t n_left; // bytes remaining
static uint64_t n_done; // bytes processed so far

void sha1_comp( const uint8_t* x ) {
  uint32_t W[ 80 ];

  uint32_t a = H_0;
  uint32_t b = H_1;
  uint32_t c = H_2;
  uint32_t d = H_3;
  uint32_t e = H_4;

  U8_TO_U32_BE( W[  0 ], x,  0 );
  U8_TO_U32_BE( W[  1 ], x,  4 );
  U8_TO_U32_BE( W[  2 ], x,  8 );
  U8_TO_U32_BE( W[  3 ], x, 12 );
  U8_TO_U32_BE( W[  4 ], x, 16 );
  U8_TO_U32_BE( W[  5 ], x, 20 );
  U8_TO_U32_BE( W[  6 ], x, 24 );
  U8_TO_U32_BE( W[  7 ], x, 28 );
  U8_TO_U32_BE( W[  8 ], x, 32 );
  U8_TO_U32_BE( W[  9 ], x, 36 );
  U8_TO_U32_BE( W[ 10 ], x, 40 );
  U8_TO_U32_BE( W[ 11 ], x, 44 );
  U8_TO_U32_BE( W[ 12 ], x, 48 );
  U8_TO_U32_BE( W[ 13 ], x, 52 );
  U8_TO_U32_BE( W[ 14 ], x, 56 );
  U8_TO_U32_BE( W[ 15 ], x, 60 );

  for( int i = 16; i < 80; i += 1 ) { 
    W[ i ] = U32_RTL( W[ i -  3 ] ^ W[ i -  8 ] ^ W[ i - 14 ] ^ W[ i - 16 ], 1 );
  }

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( c ^ ( a & ( b ^ c ) ) )

  SHA1_R( a, b, c, d, e, W[  0 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, W[  1 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, W[  2 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, W[  3 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, W[  4 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, W[  5 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, W[  6 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, W[  7 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, W[  8 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, W[  9 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, W[ 10 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, W[ 11 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, W[ 12 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, W[ 13 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, W[ 14 ], 0x5A827999 );
  SHA1_R( a, b, c, d, e, W[ 15 ], 0x5A827999 );
  SHA1_R( e, a, b, c, d, W[ 16 ], 0x5A827999 );
  SHA1_R( d, e, a, b, c, W[ 17 ], 0x5A827999 );
  SHA1_R( c, d, e, a, b, W[ 18 ], 0x5A827999 );
  SHA1_R( b, c, d, e, a, W[ 19 ], 0x5A827999 );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( a ^ b ^ c )

  SHA1_R( a, b, c, d, e, W[ 20 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, W[ 21 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, W[ 22 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, W[ 23 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, W[ 24 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, W[ 25 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, W[ 26 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, W[ 27 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, W[ 28 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, W[ 29 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, W[ 30 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, W[ 31 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, W[ 32 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, W[ 33 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, W[ 34 ], 0x6ED9EBA1 );
  SHA1_R( a, b, c, d, e, W[ 35 ], 0x6ED9EBA1 );
  SHA1_R( e, a, b, c, d, W[ 36 ], 0x6ED9EBA1 );
  SHA1_R( d, e, a, b, c, W[ 37 ], 0x6ED9EBA1 );
  SHA1_R( c, d, e, a, b, W[ 38 ], 0x6ED9EBA1 );
  SHA1_R( b, c, d, e, a, W[ 39 ], 0x6ED9EBA1 );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( ( a & b ) | ( ( a | b ) & c ) )

  SHA1_R( a, b, c, d, e, W[ 40 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, W[ 41 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, W[ 42 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, W[ 43 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, W[ 44 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, W[ 45 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, W[ 46 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, W[ 47 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, W[ 48 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, W[ 49 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, W[ 50 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, W[ 51 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, W[ 52 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, W[ 53 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, W[ 54 ], 0x8F1BBCDC );
  SHA1_R( a, b, c, d, e, W[ 55 ], 0x8F1BBCDC );
  SHA1_R( e, a, b, c, d, W[ 56 ], 0x8F1BBCDC );
  SHA1_R( d, e, a, b, c, W[ 57 ], 0x8F1BBCDC );
  SHA1_R( c, d, e, a, b, W[ 58 ], 0x8F1BBCDC );
  SHA1_R( b, c, d, e, a, W[ 59 ], 0x8F1BBCDC );

  #undef  SHA1_F
  #define SHA1_F(a,b,c) ( a ^ b ^ c )

  SHA1_R( a, b, c, d, e, W[ 60 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, W[ 61 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, W[ 62 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, W[ 63 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, W[ 64 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, W[ 65 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, W[ 66 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, W[ 67 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, W[ 68 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, W[ 69 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, W[ 70 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, W[ 71 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, W[ 72 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, W[ 73 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, W[ 74 ], 0xCA62C1D6 );
  SHA1_R( a, b, c, d, e, W[ 75 ], 0xCA62C1D6 );
  SHA1_R( e, a, b, c, d, W[ 76 ], 0xCA62C1D6 );
  SHA1_R( d, e, a, b, c, W[ 77 ], 0xCA62C1D6 );
  SHA1_R( c, d, e, a, b, W[ 78 ], 0xCA62C1D6 );
  SHA1_R( b, c, d, e, a, W[ 79 ], 0xCA62C1D6 );

  H_0 += a;
  H_1 += b;
  H_2 += c;
  H_3 += d;
  H_4 += e;
}

void sha1_padd( uint8_t* x ) {
  int n_b = SHA1_SIZEOF_BLOCK;

  n_done = ( n_done + n_left ) * 8;

  x[ n_left++ ] = 0x80;

  if   ( n_left > ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    while( n_left < n_b ) {
      x[ n_left++ ] = 0x00;
    }

    sha1_comp( x );

    n_left = 0;
  }

  while( n_left < ( n_b - ( 1 * SIZEOF( uint64_t ) ) ) ) {
    x[ n_left++ ] = 0x00;
  }

  U64_TO_U8_BE( x, n_done, n_left );

  sha1_comp( x );
}

void sha1_init() {
  H_0 = 0x67452301;
  H_1 = 0xEFCDAB89;
  H_2 = 0x98BADCFE;
  H_3 = 0x10325476;
  H_4 = 0xC3D2E1F0;

  n_left = 0;
  n_done = 0;
}

void sha1_hash( const uint8_t* m, int n_m ) {
  int n_b = SHA1_SIZEOF_BLOCK;

  if( n_left != 0 ) {
    int n_t = n_b - n_left;
 
    if( n_t > n_m ) {
      memcpy( T + n_left, m, n_m );

      n_left += n_m;
      n_m     =   0;
    }
    else {
      memcpy( T + n_left, m, n_t );

      n_done += n_b;
      n_left  =   0;
      n_m    -= n_t;

      sha1_comp( T );
    }
  }

  while( n_m >= n_b ) {
    sha1_comp( m );

    n_done += n_b;
    m      += n_b;
    n_m    -= n_b;
  }

  if( n_m > 0 ) {
    memcpy( T, m, n_left = n_m );
  }
}

void sha1_fini( uint8_t* d ) {
  sha1_padd( T );

  U32_TO_U8_BE( d, H_0,  0 );
  U32_TO_U8_BE( d, H_1,  4 );
  U32_TO_U8_BE( d, H_2,  8 );
  U32_TO_U8_BE( d, H_3, 12 );
  U32_TO_U8_BE( d, H_4, 16 );
}

void sha1( uint8_t* d, int l, ... ) {
  va_list a;

  sha1_init();
  va_start( a, l );

  for( int i = 0; i < l; i++ ) {
    uint8_t* m   = va_arg( a, uint8_t* );
    int      n_m = va_arg( a,  int     );

    sha1_hash( m, n_m );
  }

  va_end( a );
  sha1_fini( d );
}
