#include <scarv/block/aes/aes_enc.h>

#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_ENC_INIT_EXTERN )
void aes_enc_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_key( s, rk );
}
#endif
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_ENC_ITER_EXTERN )
void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_sub( s     );
  aes_enc_rnd_row( s     );
  aes_enc_rnd_mix( s     );
  aes_enc_rnd_key( s, rk );
}
#endif
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_ENC_FINI_EXTERN ) 
void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_sub( s     );
  aes_enc_rnd_row( s     );
  aes_enc_rnd_key( s, rk );
}
#endif

#if ( !LIBSCARV_CONF_AES_ENC_EXP_STEP_EXTERN )
void aes_enc_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon ) {
  #if !( LIBSCARV_CONF_AES_ROUND_PACK )
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
  #else
  uint32_t*  rp = ( uint32_t* )(  r );
  uint32_t* rkp = ( uint32_t* )( rk );

  uint32_t  t_0 = rkp[ 0 ];
  uint32_t  t_1 = rkp[ 1 ];
  uint32_t  t_2 = rkp[ 2 ];
  uint32_t  t_3 = rkp[ 3 ];

  uint32_t  t_4 = ( uint32_t )( rcon ) ^ t_0 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_1 >> 24 ) & 0xFF ] );
  uint32_t  t_5 =                        t_1 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_2 >> 24 ) & 0xFF ] );
  uint32_t  t_6 =                        t_2 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_3 >> 24 ) & 0xFF ] );
  uint32_t  t_7 =                        t_3 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_0 >> 24 ) & 0xFF ] );

            t_0 = t_4 ^ ( t_4 << 8 ) ^ ( t_4 << 16 ) ^ ( t_4 << 24 ) ;
            t_1 = t_5 ^ ( t_5 << 8 ) ^ ( t_5 << 16 ) ^ ( t_5 << 24 ) ;
            t_2 = t_6 ^ ( t_6 << 8 ) ^ ( t_6 << 16 ) ^ ( t_6 << 24 ) ;
            t_3 = t_7 ^ ( t_7 << 8 ) ^ ( t_7 << 16 ) ^ ( t_7 << 24 ) ;

             rp[ 0 ] = t_0;
             rp[ 1 ] = t_1;
             rp[ 2 ] = t_2;
             rp[ 3 ] = t_3;
  #endif
}
#endif

#if ( LIBSCARV_CONF_AES_PRECOMP_RK )
void aes_enc_exp( uint8_t* r, const uint8_t* k ) {
  uint8_t* rcp =      AES_RC;
  uint8_t*  rp =                   r;

    #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
    U8_TO_U8_N(   r, k );
    #else
    U8_TO_U8_T(   r, k );
    #endif

  for( int i = 1; i < ( Nr + 1 ); i++ ) {
    aes_enc_exp_step( rp + ( 4 * Nb ), rp, *(++rcp) ); rp += ( 4 * Nb );
  }
}
#endif

#if !( LIBSCARV_CONF_AES_ENC_EXTERN ) 
void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k,  uint8_t* sbox,  uint8_t* mulx ) {  
  uint8_t  s[ 4 * Nb ];

  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK )
  uint8_t rk[ 4 * Nb ]; 
  uint8_t* rcp =  AES_RC; 
  uint8_t* rkp =  rk;
  #else
  uint8_t* rkp =  k; 
  #endif

  #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   s, m );
  #else
  U8_TO_U8_T(   s, m );
  #endif
  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK ) && !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N( rkp, k );
  #elif !( LIBSCARV_CONF_AES_PRECOMP_RK ) &&  ( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_T( rkp, k );
  #endif

  //      1 initial   round
    aes_enc_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < Nr; i++ ) {
    #if   !( LIBSCARV_CONF_AES_PRECOMP_RK )
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
    #else
    rkp += ( 4 * Nb );
    #endif
		
    #if ( LIBSCARV_CONF_AES_ENC_ITER_EXTERN ) 
    aes_enc_rnd_iter( s, rkp,  sbox,  mulx );
    #else
    aes_enc_rnd_iter( s, rkp );
    #endif		
  }
  //      1 final     round
  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK )
  aes_enc_exp_step( rkp, rkp, *(++rcp) );
  #else
  rkp += ( 4 * Nb );
  #endif
	
  #if ( LIBSCARV_CONF_AES_ENC_FINI_EXTERN )
  aes_enc_rnd_fini( s, rkp,  sbox);
  #else
  aes_enc_rnd_fini( s, rkp );
  #endif

  #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   r, s );
  #else
  U8_TO_U8_T(   r, s );
  #endif
}
#endif
