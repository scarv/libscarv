/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_dec_imp.h>

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_DEC_RND_KEY(s,rk) {             \
    AES_DEC_RND_KEY_STEP(  0,  1,  2,  3 ); \
    AES_DEC_RND_KEY_STEP(  4,  5,  6,  7 ); \
    AES_DEC_RND_KEY_STEP(  8,  9, 10, 11 ); \
    AES_DEC_RND_KEY_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_DEC_RND_KEY(s,rk) {             \
  for( int i = 0; i < 16; i++ ) {           \
    s[ i ] = s[ i ] ^ rk[ i ];              \
  }                                         \
}
#endif

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_DEC_RND_SUB(s   ) {             \
    AES_DEC_RND_SUB_STEP(  0,  1,  2,  3 ); \
    AES_DEC_RND_SUB_STEP(  4,  5,  6,  7 ); \
    AES_DEC_RND_SUB_STEP(  8,  9, 10, 11 ); \
    AES_DEC_RND_SUB_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_DEC_RND_SUB(s   ) {             \
  for( int i = 0; i < 16; i++ ) {           \
    s[ i ] = AES_DEC_SBOX[ s[ i ] ];        \
  }                                         \
}
#endif

#define AES_DEC_RND_ROW(s   ) {             \
    AES_DEC_RND_ROW_STEP(  1,  5,  9, 13,   \
                           5,  9, 13,  1 ); \
    AES_DEC_RND_ROW_STEP(  2,  6, 10, 14,   \
                          10, 14,  2,  6 ); \
    AES_DEC_RND_ROW_STEP(  3,  7, 11, 15,   \
                          15,  3,  7, 11 ); \
}

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_DEC_RND_MIX(s   ) {             \
    AES_DEC_RND_MIX_STEP(  0,  1,  2,  3 ); \
    AES_DEC_RND_MIX_STEP(  4,  5,  6,  7 ); \
    AES_DEC_RND_MIX_STEP(  8,  9, 10, 11 ); \
    AES_DEC_RND_MIX_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_DEC_RND_MIX(s   ) {             \
  for( int i = 0; i < 4; i++, s += 4 ) {    \
    AES_DEC_RND_MIX_STEP(  0,  1,  2,  3 ); \
  }                                         \
}
#endif

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
