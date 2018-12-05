#include "aes_dec_imp.h"

#define AES_DEC_RND_KEY_STEP(a,b,c,d        ) {   \
  s[ a ] = s[ a ] ^ rk[ a ];                      \
  s[ b ] = s[ b ] ^ rk[ b ];                      \
  s[ c ] = s[ c ] ^ rk[ c ];                      \
  s[ d ] = s[ d ] ^ rk[ d ];                      \
}
#define AES_DEC_RND_SUB_STEP(a,b,c,d        ) {   \
  s[ a ] = AES_DEC_SBOX[ s[ a ] ];                \
  s[ b ] = AES_DEC_SBOX[ s[ b ] ];                \
  s[ c ] = AES_DEC_SBOX[ s[ c ] ];                \
  s[ d ] = AES_DEC_SBOX[ s[ d ] ];                \
}
#define AES_DEC_RND_ROW_STEP(a,b,c,d,e,f,g,h) {   \
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
#define AES_DEC_RND_MIX_STEP(a,b,c,d        ) {   \
  uint8_t __a1 = s[ a ], __a2 = AES_MULX[ __a1 ]; \
  uint8_t __b1 = s[ b ], __b2 = AES_MULX[ __b1 ]; \
  uint8_t __c1 = s[ c ], __c2 = AES_MULX[ __c1 ]; \
  uint8_t __d1 = s[ d ], __d2 = AES_MULX[ __d1 ]; \
                                                  \
  uint8_t                __a4 = AES_MULX[ __a2 ]; \
  uint8_t                __b4 = AES_MULX[ __b2 ]; \
  uint8_t                __c4 = AES_MULX[ __c2 ]; \
  uint8_t                __d4 = AES_MULX[ __d2 ]; \
                                                  \
  uint8_t                __a8 = AES_MULX[ __a4 ]; \
  uint8_t                __b8 = AES_MULX[ __b4 ]; \
  uint8_t                __c8 = AES_MULX[ __c4 ]; \
  uint8_t                __d8 = AES_MULX[ __d4 ]; \
                                                  \
  uint8_t __aA = __a2 ^ __a8;                     \
  uint8_t __bA = __b2 ^ __b8;                     \
  uint8_t __cA = __c2 ^ __c8;                     \
  uint8_t __dA = __d2 ^ __d8;                     \
                                                  \
  uint8_t __aC = __a4 ^ __a8;                     \
  uint8_t __bC = __b4 ^ __b8;                     \
  uint8_t __cC = __c4 ^ __c8;                     \
  uint8_t __dC = __d4 ^ __d8;                     \
                                                  \
  s[ a ] = __aC ^ __a2 ^ __bA ^ __b1 ^            \
           __cC ^ __c1 ^ __d8 ^ __d1 ;            \
  s[ b ] = __a8 ^ __a1 ^ __bC ^ __b2 ^            \
           __cA ^ __c1 ^ __dC ^ __d1 ;            \
  s[ c ] = __aC ^ __a1 ^ __b8 ^ __b1 ^            \
           __cC ^ __c2 ^ __dA ^ __d1 ;            \
  s[ d ] = __aA ^ __a1 ^ __bC ^ __b1 ^            \
           __c8 ^ __c1 ^ __dC ^ __d2 ;            \
}

void aes_dec_rnd_key( uint8_t* s, const uint8_t* rk ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 16; i++ ) {
    s[ i ] = s[ i ] ^ rk[ i ];
  }
  #else
  AES_DEC_RND_KEY_STEP(  0,  1,  2,  3 );
  AES_DEC_RND_KEY_STEP(  4,  5,  6,  7 );
  AES_DEC_RND_KEY_STEP(  8,  9, 10, 11 );
  AES_DEC_RND_KEY_STEP( 12, 13, 14, 15 );
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

#if !defined( CONF_AES_DEC_SUB_EXTERN ) && !defined( CONF_AES_ROUND_PACK )
void aes_dec_rnd_sub( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 16; i++ ) {
    s[ i ] = AES_DEC_SBOX[ s[ i ] ];
  }
  #else
  AES_DEC_RND_SUB_STEP(  0,  1,  2,  3 );
  AES_DEC_RND_SUB_STEP(  4,  5,  6,  7 );
  AES_DEC_RND_SUB_STEP(  8,  9, 10, 11 );
  AES_DEC_RND_SUB_STEP( 12, 13, 14, 15 );
  #endif
}
#endif

void aes_dec_rnd_row( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  AES_DEC_RND_ROW_STEP(  1,  5,  9, 13,
                         5,  9, 13,  1 );
  AES_DEC_RND_ROW_STEP(  2,  6, 10, 14,
                        10, 14,  2,  6 );
  AES_DEC_RND_ROW_STEP(  3,  7, 11, 15,
                        15,  3,  7, 11 );
  #else
  uint32_t* sp = ( uint32_t* )(  s );

  sp[ 1 ] = U32_RTL( sp[ 1 ],  8 );
  sp[ 2 ] = U32_RTL( sp[ 2 ], 16 );
  sp[ 3 ] = U32_RTL( sp[ 3 ], 24 );
  #endif
}

#if !defined( CONF_AES_DEC_MIX_EXTERN ) && !defined( CONF_AES_ROUND_PACK )
void aes_dec_rnd_mix( uint8_t* s ) {
  #if !defined( CONF_AES_ROUND_PACK   )
  #if !defined( CONF_AES_ROUND_UNROLL )
  for( int i = 0; i < 4; i++, s += 4 ) {
    AES_DEC_RND_MIX_STEP(  0,  1,  2,  3 );
  }
  #else
    AES_DEC_RND_MIX_STEP(  0,  1,  2,  3 );
    AES_DEC_RND_MIX_STEP(  4,  5,  6,  7 );
    AES_DEC_RND_MIX_STEP(  8,  9, 10, 11 );
    AES_DEC_RND_MIX_STEP( 12, 13, 14, 15 );
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
            AES_MULX_PACKED( t_0, t_0 ^ t_2 ); AES_MULX_PACKED( t_1, t_1 ^ t_3 );
            t_4 = t_4 ^ t_0;       t_5 = t_5 ^ t_1;
            t_6 = t_6 ^ t_0;       t_7 = t_7 ^ t_1;
            AES_MULX_PACKED( t_0, t_0 ^ t_1 ); 
            t_4 = t_4 ^ t_0;       t_5 = t_5 ^ t_0;
            t_6 = t_6 ^ t_0;       t_7 = t_7 ^ t_0;

            sp[ 0 ] = t_4; sp[ 1 ] = t_5;
            sp[ 2 ] = t_6; sp[ 3 ] = t_7;
  #endif
}
#endif
