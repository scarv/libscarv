/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_dec_imp.h>

#define AES_DEC_RND_KEY(s,rk) {             \
    uint32_t*  sp = ( uint32_t* )(  s );    \
    uint32_t* rkp = ( uint32_t* )( rk );    \
                                            \
    sp[ 0 ] = sp[ 0 ] ^ rkp[ 0 ];           \
    sp[ 1 ] = sp[ 1 ] ^ rkp[ 1 ];           \
    sp[ 2 ] = sp[ 2 ] ^ rkp[ 2 ];           \
    sp[ 3 ] = sp[ 3 ] ^ rkp[ 3 ];           \
}

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_DEC_RND_SUB(s   ) {             \
    AES_DEC_RND_SUB_STEP(  0,  1,  2,  3 ); \
    AES_DEC_RND_SUB_STEP(  4,  5,  6,  7 ); \
    AES_DEC_RND_SUB_STEP(  8,  9, 10, 11 ); \
    AES_DEC_RND_SUB_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_DEC_RND_SUB(s   ) {             \
    uint32_t*  sp = ( uint32_t* )(  s );    \
                                            \
  for( int i = 0; i < 16; i++ ) {           \
    s[ i ] = AES_DEC_SBOX[ s[ i ] ];        \
  }                                         \
}
#endif

#define AES_DEC_RND_ROW(s   ) {             \
    uint32_t*  sp = ( uint32_t* )(  s );    \
                                            \
  sp[ 1 ] = U32_RTL( sp[ 1 ],  8 );         \
  sp[ 2 ] = U32_RTL( sp[ 2 ], 16 );         \
  sp[ 3 ] = U32_RTL( sp[ 3 ], 24 );         \
}

#define AES_DEC_RND_MIX(s   ) {                           \
  uint32_t* sp = ( uint32_t* )(  s );                     \
                                                          \
  uint32_t  t_0 = sp[ 0 ], t_1 = sp[ 1 ];                 \
  uint32_t  t_2 = sp[ 2 ], t_3 = sp[ 3 ];                 \
                                                          \
  uint32_t  t_4 = t_1 ^ t_2 ^ t_3, t_5 = t_0 ^ t_2 ^ t_3; \
  uint32_t  t_6 = t_0 ^ t_1 ^ t_3, t_7 = t_0 ^ t_1 ^ t_2; \
                                                          \
            AES_MULX_PACKED( t_0, t_0       );            \
            AES_MULX_PACKED( t_1, t_1       );            \
            AES_MULX_PACKED( t_2, t_2       );            \
            AES_MULX_PACKED( t_3, t_3       );            \
                                                          \
            t_4 = t_4 ^ t_0 ^ t_1; t_5 = t_5 ^ t_1 ^ t_2; \
            t_6 = t_6 ^ t_2 ^ t_3; t_7 = t_7 ^ t_0 ^ t_3; \
                                                          \
            AES_MULX_PACKED( t_0, t_0 ^ t_2 );            \
            AES_MULX_PACKED( t_1, t_1 ^ t_3 );            \
                                                          \
            t_4 = t_4 ^ t_0;       t_5 = t_5 ^ t_1;       \
            t_6 = t_6 ^ t_0;       t_7 = t_7 ^ t_1;       \
                                                          \
            AES_MULX_PACKED( t_0, t_0 ^ t_1 );            \
                                                          \
            t_4 = t_4 ^ t_0;       t_5 = t_5 ^ t_0;       \
            t_6 = t_6 ^ t_0;       t_7 = t_7 ^ t_0;       \
                                                          \
            sp[ 0 ] = t_4; sp[ 1 ] = t_5;                 \
            sp[ 2 ] = t_6; sp[ 3 ] = t_7;                 \
}



#if ( LIBSCARV_CONF_AES_RND_INLINE )
#define aes_dec_rnd_key AES_DEC_RND_KEY
#define aes_dec_rnd_sub AES_DEC_RND_SUB
#define aes_dec_rnd_row AES_DEC_RND_ROW
#define aes_dec_rnd_mix AES_DEC_RND_MIX
#else
void aes_dec_rnd_key( uint8_t* s, const uint8_t* rk ) {
  AES_DEC_RND_KEY( s, rk );
}
void aes_dec_rnd_sub( uint8_t* s                    ) {
  AES_DEC_RND_SUB( s     );
}
void aes_dec_rnd_row( uint8_t* s                    ) {
  AES_DEC_RND_ROW( s     );
}
void aes_dec_rnd_mix( uint8_t* s                    ) {
  AES_DEC_RND_MIX( s     );
}
#endif

void aes_dec_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_key( s, rk );
}

void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
  aes_dec_rnd_mix( s     );
}

void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
}
