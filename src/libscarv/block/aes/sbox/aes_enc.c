/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_enc.h>

void aes_enc_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon ) {
  r[  0 ] = rcon ^ AES_ENC_SBOX[ rk[ 13 ] ] ^ rk[  0 ];
  r[  1 ] =        AES_ENC_SBOX[ rk[ 14 ] ] ^ rk[  1 ];
  r[  2 ] =        AES_ENC_SBOX[ rk[ 15 ] ] ^ rk[  2 ];
  r[  3 ] =        AES_ENC_SBOX[ rk[ 12 ] ] ^ rk[  3 ];

  r[  4 ] =                       r[  0 ]   ^ rk[  4 ]; 
  r[  5 ] =                       r[  1 ]   ^ rk[  5 ];
  r[  6 ] =                       r[  2 ]   ^ rk[  6 ];
  r[  7 ] =                       r[  3 ]   ^ rk[  7 ];

  r[  8 ] =                       r[  4 ]   ^ rk[  8 ]; 
  r[  9 ] =                       r[  5 ]   ^ rk[  9 ];
  r[ 10 ] =                       r[  6 ]   ^ rk[ 10 ];
  r[ 11 ] =                       r[  7 ]   ^ rk[ 11 ];

  r[ 12 ] =                       r[  8 ]   ^ rk[ 12 ]; 
  r[ 13 ] =                       r[  9 ]   ^ rk[ 13 ];
  r[ 14 ] =                       r[ 10 ]   ^ rk[ 14 ];
  r[ 15 ] =                       r[ 11 ]   ^ rk[ 15 ];
}

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP )
void aes_enc_exp( uint8_t* r, const uint8_t* k ) {
  uint8_t* rcp = AES_RCON;
  uint8_t*  rp = r;

  U8_TO_U8_N( rp, k );

  for( int i = 1; i < ( AES_128_NR + 1 ); i++ ) {
    aes_enc_exp_step( rp + ( 4 * AES_128_NB ), rp, *(++rcp) ); rp += ( 4 * AES_128_NB );
  }
}
#endif

#if ( !LIBSCARV_CONF_AES_ENC_EXTERN ) 
extern void aes_enc_rnd_init( uint8_t* s, uint8_t* rk );
extern void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk );
extern void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk );

void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k ) {  
    uint8_t  s[ 4 * AES_128_NB ];

    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    uint8_t rk[ 4 * AES_128_NB ]; 
    uint8_t* rcp =  AES_RCON; 
    uint8_t* rkp =  rk;
    #else
    uint8_t* rkp =  k; 
    #endif
  
    U8_TO_U8_N(   s, m );
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    U8_TO_U8_N( rkp, k );
    #endif

  //      1 initial   round
    aes_enc_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < AES_128_NR; i++ ) {
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
    #else
    rkp += ( 4 * AES_128_NB );
    #endif
    aes_enc_rnd_iter( s, rkp );
  }
  //      1 final     round
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
    #else
    rkp += ( 4 * AES_128_NB );
    #endif
    aes_enc_rnd_fini( s, rkp );

    U8_TO_U8_N(   r, s );
}
#endif
