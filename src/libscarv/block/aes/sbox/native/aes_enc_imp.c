/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_enc_imp.h>

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_ENC_RND_KEY(s,rk) {             \
    AES_ENC_RND_KEY_STEP(  0,  1,  2,  3 ); \
    AES_ENC_RND_KEY_STEP(  4,  5,  6,  7 ); \
    AES_ENC_RND_KEY_STEP(  8,  9, 10, 11 ); \
    AES_ENC_RND_KEY_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_ENC_RND_KEY(s,rk) {             \
  for( int i = 0; i < 16; i++ ) {           \
    s[ i ] = s[ i ] ^ rk[ i ];              \
  }                                         \
}
#endif

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_ENC_RND_SUB(s   ) {             \
    AES_ENC_RND_SUB_STEP(  0,  1,  2,  3 ); \
    AES_ENC_RND_SUB_STEP(  4,  5,  6,  7 ); \
    AES_ENC_RND_SUB_STEP(  8,  9, 10, 11 ); \
    AES_ENC_RND_SUB_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_ENC_RND_SUB(s   ) {             \
  for( int i = 0; i < 16; i++ ) {           \
    s[ i ] = AES_ENC_SBOX[ s[ i ] ];        \
  }                                         \
}
#endif

#define AES_ENC_RND_ROW(s   ) {             \
    AES_ENC_RND_ROW_STEP(  1,  5,  9, 13,   \
                          13,  1,  5,  9 ); \
    AES_ENC_RND_ROW_STEP(  2,  6, 10, 14,   \
                          10, 14,  2,  6 ); \
    AES_ENC_RND_ROW_STEP(  3,  7, 11, 15,   \
                           7, 11, 15,  3 ); \
}

#if ( LIBSCARV_CONF_AES_RND_UNROLL )
#define AES_ENC_RND_MIX(s   ) {             \
    AES_ENC_RND_MIX_STEP(  0,  1,  2,  3 ); \
    AES_ENC_RND_MIX_STEP(  4,  5,  6,  7 ); \
    AES_ENC_RND_MIX_STEP(  8,  9, 10, 11 ); \
    AES_ENC_RND_MIX_STEP( 12, 13, 14, 15 ); \
}
#else
#define AES_ENC_RND_MIX(s   ) {             \
  for( int i = 0; i < 4; i++, s += 4 ) {    \
    AES_ENC_RND_MIX_STEP(  0,  1,  2,  3 ); \
  }                                         \
}
#endif 

#if ( LIBSCARV_CONF_AES_RND_INLINE )
#define aes_enc_rnd_key AES_ENC_RND_KEY
#define aes_enc_rnd_sub AES_ENC_RND_SUB
#define aes_enc_rnd_row AES_ENC_RND_ROW
#define aes_enc_rnd_mix AES_ENC_RND_MIX
#else
void aes_enc_rnd_key( uint8_t* s, const uint8_t* rk ) {
  AES_ENC_RND_KEY( s, rk );
}
void aes_enc_rnd_sub( uint8_t* s                    ) {
  AES_ENC_RND_SUB( s     );
}
void aes_enc_rnd_row( uint8_t* s                    ) {
  AES_ENC_RND_ROW( s     );
}
void aes_enc_rnd_mix( uint8_t* s                    ) {
  AES_ENC_RND_MIX( s     );
}
#endif

void aes_enc_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_key( s, rk );
}

void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_sub( s     );
  aes_enc_rnd_row( s     );
  aes_enc_rnd_mix( s     );
  aes_enc_rnd_key( s, rk );
}

void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_sub( s     );
  aes_enc_rnd_row( s     );
  aes_enc_rnd_key( s, rk );
}
