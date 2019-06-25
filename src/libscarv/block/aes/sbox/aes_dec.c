#include <scarv/block/aes/aes_dec.h>

#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_DEC_INIT_EXTERN ) 
void aes_dec_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_key( s, rk );
}
#endif
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_DEC_ITER_EXTERN ) 
void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
  aes_dec_rnd_mix( s     );
}
#endif
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_DEC_FINI_EXTERN ) 
void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
}
#endif

void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon ) {
  #if !( LIBSCARV_CONF_AES_ROUND_PACK )
  r[ 15 ] =                      rk[ 11 ]   ^ rk[ 15 ];
  r[ 14 ] =                      rk[ 10 ]   ^ rk[ 14 ];
  r[ 13 ] =                      rk[  9 ]   ^ rk[ 13 ];
  r[ 12 ] =                      rk[  8 ]   ^ rk[ 12 ]; 

  r[ 11 ] =                      rk[  7 ]   ^ rk[ 11 ];
  r[ 10 ] =                      rk[  6 ]   ^ rk[ 10 ];
  r[  9 ] =                      rk[  5 ]   ^ rk[  9 ];
  r[  8 ] =                      rk[  4 ]   ^ rk[  8 ]; 

  r[  7 ] =                      rk[  3 ]   ^ rk[  7 ];
  r[  6 ] =                      rk[  2 ]   ^ rk[  6 ];
  r[  5 ] =                      rk[  1 ]   ^ rk[  5 ];
  r[  4 ] =                      rk[  0 ]   ^ rk[  4 ]; 

  r[  3 ] =        AES_ENC_SBOX[  r[ 12 ] ] ^ rk[  3 ];
  r[  2 ] =        AES_ENC_SBOX[  r[ 15 ] ] ^ rk[  2 ];
  r[  1 ] =        AES_ENC_SBOX[  r[ 14 ] ] ^ rk[  1 ];
  r[  0 ] = rcon ^ AES_ENC_SBOX[  r[ 13 ] ] ^ rk[  0 ];
  #else
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
  #endif
}

#if ( LIBSCARV_CONF_AES_RK_PRECOMP )
void aes_dec_exp( uint8_t* r, const uint8_t* k ) {
  #if   ( LIBSCARV_CONF_AES_KEY_FWD )
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

  //transposition KEY array for doing transpose sub-row-key-mix in iterative loop in the case of xcrypto AES instructions
  #if (( LIBSCARV_CONF_AES_DEC_ITER_EXTERN )||( LIBSCARV_CONF_AES_DEC_EXTERN )) && !( LIBSCARV_CONF_AES_ROUND_PACK )
  uint16_t* rph = ( uint16_t * )r; 
  uint16_t t;
  for( int i = 1; i < (Nr); i++ ) {
    rph += ( 2 * Nb );
    t = rph[1]; rph[1] = rph[5]; rph[5] = t;
    t = rph[3]; rph[3] = rph[7]; rph[7] = t;	
  }
  #endif
#elif ( LIBSCARV_CONF_AES_KEY_REV )
  uint8_t* rcp = Nr + AES_RC;
  uint8_t*  rp = ( 4 * Nb * Nr ) + r;

  #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   rp, k );
  #else
  U8_TO_U8_T(   rp, k );
  #endif

  for( int i = 1; i < ( Nr + 1 ); i++ ) {
    aes_dec_exp_step( rp - ( 4 * Nb ), rp, *(--rcp) ); rp -= ( 4 * Nb );
  }
  #endif
}
#endif

#if !( LIBSCARV_CONF_AES_DEC_EXTERN )
void aes_dec( uint8_t* r, uint8_t* c, uint8_t* k,  uint8_t* sbox,  uint8_t* mulx ) {  
  uint8_t  s[ 4 * Nb ];

  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK ) &&  ( LIBSCARV_CONF_AES_KEY_FWD )
  uint8_t rk[ 4 * Nb ];
  uint8_t* rcp =      AES_RC;
  uint8_t* rkp =                   rk;
  #elif !( LIBSCARV_CONF_AES_PRECOMP_RK ) &&  ( LIBSCARV_CONF_AES_KEY_REV )
  uint8_t rk[ 4 * Nb ];
  uint8_t* rcp = Nr + AES_RC;
  uint8_t* rkp =                   rk;
  #else
  uint8_t* rkp = ( 4 * Nb * Nr ) +  k; 
  #endif

  #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   s, c );
  #else
  U8_TO_U8_T(   s, c );
  #endif

  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK ) && !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N( rkp, k );
  #elif !( LIBSCARV_CONF_AES_PRECOMP_RK ) &&  ( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_T( rkp, k );
  #endif

  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK ) &&  ( LIBSCARV_CONF_AES_KEY_FWD )
  for( int i = 1; i < ( Nr + 1 ); i++ ) {
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
  }
 #endif

  //      1 initial   round
  aes_dec_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < Nr; i++ ) {
    #if   !( LIBSCARV_CONF_AES_PRECOMP_RK )
    aes_dec_exp_step( rkp, rkp, *(rcp--) );
    #else
    rkp -= ( 4 * Nb );
    #endif
	
	#if ( LIBSCARV_CONF_AES_DEC_ITER_EXTERN )
	aes_dec_rnd_iter( s, rkp,  sbox,  mulx  );
	#else
    aes_dec_rnd_iter( s, rkp );
	#endif
  }
  //      1 final     round
  #if   !( LIBSCARV_CONF_AES_PRECOMP_RK )
  aes_dec_exp_step( rkp, rkp, *(rcp--) );
  #else
  rkp -= ( 4 * Nb );
  #endif

  #if ( LIBSCARV_CONF_AES_DEC_FINI_EXTERN )
  aes_dec_rnd_fini( s, rkp,  sbox );
  #else
  aes_dec_rnd_fini( s, rkp );
  #endif

  #if                                      !( LIBSCARV_CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   r, s );
  #else
  U8_TO_U8_T(   r, s );
  #endif
}
#endif
