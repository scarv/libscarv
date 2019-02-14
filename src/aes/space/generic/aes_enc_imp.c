#include "scarv/aes/aes_enc_imp.h"

#define AES_ENC_RND_KEY_STEP(a,b,c,d        ) {   \
  s[ a ] = s[ a ] ^ rk[ a ];                      \
  s[ b ] = s[ b ] ^ rk[ b ];                      \
  s[ c ] = s[ c ] ^ rk[ c ];                      \
  s[ d ] = s[ d ] ^ rk[ d ];                      \
}
#define AES_ENC_RND_SUB_STEP(a,b,c,d        ) {   \
  s[ a ] = AES_ENC_SBOX[ s[ a ] ];                \
  s[ b ] = AES_ENC_SBOX[ s[ b ] ];                \
  s[ c ] = AES_ENC_SBOX[ s[ c ] ];                \
  s[ d ] = AES_ENC_SBOX[ s[ d ] ];                \
}
#define AES_ENC_RND_ROW_STEP(a,b,c,d,e,f,g,h) {   \
  uint8_t __a1 = s[ a ];                          \
  uint8_t __b1 = s[ b ];                          \
  uint8_t __c1 = s[ c ];                          \
  uint8_t __d1 = s[ d ];                          \
                                                  \
  s[ e ] = __a1;                                  \
  s[ f ] = __b1;                                  \
  s[ g ] = __c1;                                  \
  s[ h ] = __d1;                                  \
}
#define AES_ENC_RND_MIX_STEP(a,b,c,d        ) {   \
  uint8_t __a1 = s[ a ], __a2 = AES_MULX[ __a1 ]; \
  uint8_t __b1 = s[ b ], __b2 = AES_MULX[ __b1 ]; \
  uint8_t __c1 = s[ c ], __c2 = AES_MULX[ __c1 ]; \
  uint8_t __d1 = s[ d ], __d2 = AES_MULX[ __d1 ]; \
                                                  \
  uint8_t __a3 = __a1 ^ __a2;                     \
  uint8_t __b3 = __b1 ^ __b2;                     \
  uint8_t __c3 = __c1 ^ __c2;                     \
  uint8_t __d3 = __d1 ^ __d2;                     \
                                                  \
  s[ a ] = __a2 ^ __b3 ^ __c1 ^ __d1;             \
  s[ b ] = __a1 ^ __b2 ^ __c3 ^ __d1;             \
  s[ c ] = __a1 ^ __b1 ^ __c2 ^ __d3;             \
  s[ d ] = __a3 ^ __b1 ^ __c1 ^ __d2;             \
}

void aes_enc_rnd_key( uint8_t* s, const uint8_t* rk ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 16; i++ ) {
    s[ i ] = s[ i ] ^ rk[ i ];
  }
  #else
  AES_ENC_RND_KEY_STEP(  0,  1,  2,  3 );
  AES_ENC_RND_KEY_STEP(  4,  5,  6,  7 );
  AES_ENC_RND_KEY_STEP(  8,  9, 10, 11 );
  AES_ENC_RND_KEY_STEP( 12, 13, 14, 15 );
  #endif
  #else
  uint32_t*  sp = ( uint32_t* )(  s );
  uint32_t* rkp = ( uint32_t* )( rk );

  sp[ 0 ] = sp[ 0 ] ^ rkp[ 0 ];
  sp[ 1 ] = sp[ 1 ] ^ rkp[ 1 ];
  sp[ 2 ] = sp[ 2 ] ^ rkp[ 2 ];
  sp[ 3 ] = sp[ 3 ] ^ rkp[ 3 ];
  #endif
}

void aes_enc_rnd_sub( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 16; i++ ) {
    s[ i ] = AES_ENC_SBOX[ s[ i ] ];
  }
  #else
  AES_ENC_RND_SUB_STEP(  0,  1,  2,  3 );
  AES_ENC_RND_SUB_STEP(  4,  5,  6,  7 );
  AES_ENC_RND_SUB_STEP(  8,  9, 10, 11 );
  AES_ENC_RND_SUB_STEP( 12, 13, 14, 15 );
  #endif
}

void aes_enc_rnd_row( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  AES_ENC_RND_ROW_STEP(  1,  5,  9, 13, 
                        13,  1,  5,  9 );
  AES_ENC_RND_ROW_STEP(  2,  6, 10, 14, 
                        10, 14,  2,  6 );
  AES_ENC_RND_ROW_STEP(  3,  7, 11, 15, 
                         7, 11, 15,  3 );
  #else
  uint32_t* sp = ( uint32_t* )(  s );

  sp[ 1 ] = U32_RTR( sp[ 1 ],  8 );
  sp[ 2 ] = U32_RTR( sp[ 2 ], 16 );
  sp[ 3 ] = U32_RTR( sp[ 3 ], 24 );
  #endif
}

void aes_enc_rnd_mix( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 4; i++, s += 4 ) {
    AES_ENC_RND_MIX_STEP(  0,  1,  2,  3 );
  }
  #else
    AES_ENC_RND_MIX_STEP(  0,  1,  2,  3 );
    AES_ENC_RND_MIX_STEP(  4,  5,  6,  7 );
    AES_ENC_RND_MIX_STEP(  8,  9, 10, 11 );
    AES_ENC_RND_MIX_STEP( 12, 13, 14, 15 );
  #endif
  #else
  uint32_t* sp = ( uint32_t* )(  s );

  uint32_t  t_0 = sp[ 0 ], t_1 = sp[ 1 ];
  uint32_t  t_2 = sp[ 2 ], t_3 = sp[ 3 ];

  uint32_t  t_4 = t_1 ^ t_2 ^ t_3, t_5 = t_0 ^ t_2 ^ t_3;
  uint32_t  t_6 = t_0 ^ t_1 ^ t_3, t_7 = t_0 ^ t_1 ^ t_2;
            AES_MULX_PACKED( t_0, t_0       ); AES_MULX_PACKED( t_1, t_1       );
            AES_MULX_PACKED( t_2, t_2       ); AES_MULX_PACKED( t_3, t_3       );
            t_4 = t_4 ^ t_0 ^ t_1; t_5 = t_5 ^ t_1 ^ t_2;
            t_6 = t_6 ^ t_2 ^ t_3; t_7 = t_7 ^ t_0 ^ t_3;

            sp[ 0 ] = t_4; sp[ 1 ] = t_5;
            sp[ 2 ] = t_6; sp[ 3 ] = t_7;
  #endif
}
