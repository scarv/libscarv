/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_dec.h>

void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon ) {
  uint32_t*  rp = ( uint32_t* )(  r );
  uint32_t* rkp = ( uint32_t* )( rk );

  uint32_t  t_3 = rkp[ 3 ];
  uint32_t  t_2 = rkp[ 2 ];
  uint32_t  t_1 = rkp[ 1 ];
  uint32_t  t_0 = rkp[ 0 ];

            t_3 = t_3 ^ ( t_3 << 8 );
            t_2 = t_2 ^ ( t_2 << 8 );
            t_1 = t_1 ^ ( t_1 << 8 );
            t_0 = t_0 ^ ( t_0 << 8 );

  uint32_t  t_7 =                        t_3 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_0 >> 24 ) & 0xFF ] );
  uint32_t  t_6 =                        t_2 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_3 >> 24 ) & 0xFF ] );
  uint32_t  t_5 =                        t_1 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_2 >> 24 ) & 0xFF ] );
  uint32_t  t_4 = ( uint32_t )( rcon ) ^ t_0 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_1 >> 24 ) & 0xFF ] );

             rp[ 3 ] = t_7;
             rp[ 2 ] = t_6;
             rp[ 1 ] = t_5;
             rp[ 0 ] = t_4;
}

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP ) 
void aes_dec_exp( uint8_t* r, const uint8_t* k ) {
  #if ( LIBSCARV_CONF_AES_KEY_EVOLVE_FWD )
  uint8_t* rcp = AES_RCON;
  uint8_t*  rp = r;

  U8_TO_U8_T( rp, k );
		
  for( int i = 1; i < ( AES_128_NR + 1 ); i++ ) {
    aes_enc_exp_step( rp + ( 4 * AES_128_NB ), rp, *(++rcp) ); rp += ( 4 * AES_128_NB );
  }
  #endif

  #if ( LIBSCARV_CONF_AES_KEY_EVOLVE_REV )
  uint8_t* rcp = AES_RCON + AES_128_NR;
  uint8_t*  rp = r + ( 4 * AES_128_NB * AES_128_NR );

  U8_TO_U8_T( rp, k );

  for( int i = 1; i < ( AES_128_NR + 1 ); i++ ) {
    aes_dec_exp_step( rp - ( 4 * AES_128_NB ), rp, *(--rcp) ); rp -= ( 4 * AES_128_NB );
  }
  #endif
}
#endif

#if ( !LIBSCARV_CONF_AES_DEC_EXTERN )
extern void aes_dec_rnd_init( uint8_t* s, uint8_t* rk );
extern void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk );
extern void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk );

void aes_dec( uint8_t* r, uint8_t* c, uint8_t* k ) {  
    uint8_t  s[ 4 * AES_128_NB ];

    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP ) &&  ( LIBSCARV_CONF_AES_KEY_EVOLVE_FWD )
    uint8_t rk[ 4 * AES_128_NB ];
    uint8_t* rcp = AES_RCON;
    uint8_t* rkp = rk;
    #elif ( !LIBSCARV_CONF_AES_KEY_PRECOMP ) &&  ( LIBSCARV_CONF_AES_KEY_EVOLVE_REV )
    uint8_t rk[ 4 * AES_128_NB ];
    uint8_t* rcp = AES_RCON + AES_128_NR;
    uint8_t* rkp = rk;
    #else
    uint8_t* rkp = k + ( 4 * AES_128_NB * AES_128_NR ); 
    #endif

    U8_TO_U8_T(   s, c );
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    U8_TO_U8_T( rkp, k );
    #endif

    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP ) && ( LIBSCARV_CONF_AES_KEY_EVOLVE_FWD )
    for( int i = 1; i < ( AES_128_NR + 1 ); i++ ) {
      aes_enc_exp_step( rkp, rkp, *(++rcp) );
    }
    #endif

  //      1 initial   round
    aes_dec_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < AES_128_NR; i++ ) {
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    aes_dec_exp_step( rkp, rkp, *(rcp--) );
    #else
    rkp -= ( 4 * AES_128_NB );
    #endif
    aes_dec_rnd_iter( s, rkp );
  }
  //      1 final     round
    #if   ( !LIBSCARV_CONF_AES_KEY_PRECOMP )
    aes_dec_exp_step( rkp, rkp, *(rcp--) );
    #else
    rkp -= ( 4 * AES_128_NB );
    #endif
    aes_dec_rnd_fini( s, rkp );

    U8_TO_U8_T(   r, s );
}
#endif
