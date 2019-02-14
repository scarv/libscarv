#include "scarv/aes/aes_dec.h"

#if defined( CONF_AES_PRECOMP_SBOX )
uint8_t AES_DEC_SBOX[] = { 
  0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 
  0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
  0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 
  0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
  0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 
  0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
  0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 
  0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
  0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 
  0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
  0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 
  0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
  0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 
  0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
  0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 
  0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
  0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 
  0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
  0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 
  0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
  0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 
  0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
  0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 
  0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
  0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 
  0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
  0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 
  0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
  0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 
  0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 
  0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};
#endif

#if defined( CONF_AES_ROUND_SPLIT )

#if !defined( CONF_AES_DEC_INIT_EXTERN ) 
void aes_dec_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_key( s, rk );
}
#endif

#if !defined( CONF_AES_DEC_ITER_EXTERN ) 
void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
  aes_dec_rnd_mix( s     );
}
#endif

#if !defined( CONF_AES_DEC_FINI_EXTERN )
void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk ) {
  aes_dec_rnd_sub( s     );
  aes_dec_rnd_row( s     );
  aes_dec_rnd_key( s, rk );
}
#endif

#endif

void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rc ) {
  #if !defined( CONF_AES_ROUND_PACK )
  r[ 15 ] =                    rk[ 11 ]   ^ rk[ 15 ];
  r[ 14 ] =                    rk[ 10 ]   ^ rk[ 14 ];
  r[ 13 ] =                    rk[  9 ]   ^ rk[ 13 ];
  r[ 12 ] =                    rk[  8 ]   ^ rk[ 12 ]; 

  r[ 11 ] =                    rk[  7 ]   ^ rk[ 11 ];
  r[ 10 ] =                    rk[  6 ]   ^ rk[ 10 ];
  r[  9 ] =                    rk[  5 ]   ^ rk[  9 ];
  r[  8 ] =                    rk[  4 ]   ^ rk[  8 ]; 

  r[  7 ] =                    rk[  3 ]   ^ rk[  7 ];
  r[  6 ] =                    rk[  2 ]   ^ rk[  6 ];
  r[  5 ] =                    rk[  1 ]   ^ rk[  5 ];
  r[  4 ] =                    rk[  0 ]   ^ rk[  4 ]; 

  r[  3 ] =      AES_ENC_SBOX[  r[ 12 ] ] ^ rk[  3 ];
  r[  2 ] =      AES_ENC_SBOX[  r[ 15 ] ] ^ rk[  2 ];
  r[  1 ] =      AES_ENC_SBOX[  r[ 14 ] ] ^ rk[  1 ];
  r[  0 ] = rc ^ AES_ENC_SBOX[  r[ 13 ] ] ^ rk[  0 ];
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
  uint32_t  t_7 =                      t_3 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_0 >> 24 ) & 0xFF ] );
  uint32_t  t_6 =                      t_2 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_3 >> 24 ) & 0xFF ] );
  uint32_t  t_5 =                      t_1 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_2 >> 24 ) & 0xFF ] );
  uint32_t  t_4 = ( uint32_t )( rc ) ^ t_0 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_1 >> 24 ) & 0xFF ] );

             rp[ 3 ] = t_7;
             rp[ 2 ] = t_6;
             rp[ 1 ] = t_5;
             rp[ 0 ] = t_4;
  #endif
}

#if defined( CONF_AES_PRECOMP_RK )
void aes_dec_exp( uint8_t* r, const uint8_t* k ) {
  #if   defined( CONF_AES_KEY_FWD )
  uint8_t* rcp =      AES_RC;
  uint8_t*  rp =                   r;

  #if                                      !defined( CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   r, k );
  #else
  U8_TO_U8_T(   r, k );
  #endif
		
  for( int i = 1; i < ( Nr + 1 ); i++ ) {
    aes_enc_exp_step( rp + ( 4 * Nb ), rp, *(++rcp) ); rp += ( 4 * Nb );
  }

  //transposition KEY array for doing transpose sub-row-key-mix in iterative loop in the case of xcrypto AES instructions
  #if (defined( CONF_AES_DEC_ITER_EXTERN )||defined( CONF_AES_DEC_EXTERN )) && !defined( CONF_AES_ROUND_PACK )
  uint16_t* rph = ( uint16_t * )r; 
  uint16_t t;
  for( int i = 1; i < (Nr); i++ ) {
    rph += ( 2 * Nb );
    t = rph[1]; rph[1] = rph[5]; rph[5] = t;
    t = rph[3]; rph[3] = rph[7]; rph[7] = t;	
  }
  #endif
#elif defined( CONF_AES_KEY_REV )
  uint8_t* rcp = Nr + AES_RC;
  uint8_t*  rp = ( 4 * Nb * Nr ) + r;

  #if                                      !defined( CONF_AES_ROUND_PACK )
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

#if !defined( CONF_AES_DEC_EXTERN )
void aes_dec( uint8_t* r, uint8_t* c, uint8_t* k,  uint8_t* sbox,  uint8_t* mulx ) {  
  uint8_t  s[ 4 * Nb ];

  #if   !defined( CONF_AES_PRECOMP_RK ) &&  defined( CONF_AES_KEY_FWD )
  uint8_t rk[ 4 * Nb ];
  uint8_t* rcp =      AES_RC;
  uint8_t* rkp =                   rk;
  #elif !defined( CONF_AES_PRECOMP_RK ) &&  defined( CONF_AES_KEY_REV )
  uint8_t rk[ 4 * Nb ];
  uint8_t* rcp = Nr + AES_RC;
  uint8_t* rkp =                   rk;
  #else
  uint8_t* rkp = ( 4 * Nb * Nr ) +  k; 
  #endif

  #if                                      !defined( CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   s, c );
  #else
  U8_TO_U8_T(   s, c );
  #endif

  #if   !defined( CONF_AES_PRECOMP_RK ) && !defined( CONF_AES_ROUND_PACK )
  U8_TO_U8_N( rkp, k );
  #elif !defined( CONF_AES_PRECOMP_RK ) &&  defined( CONF_AES_ROUND_PACK )
  U8_TO_U8_T( rkp, k );
  #endif

  #if   !defined( CONF_AES_PRECOMP_RK ) &&  defined( CONF_AES_KEY_FWD )
  for( int i = 1; i < ( Nr + 1 ); i++ ) {
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
  }
 #endif

  //      1 initial   round
  aes_dec_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < Nr; i++ ) {
    #if   !defined( CONF_AES_PRECOMP_RK )
    aes_dec_exp_step( rkp, rkp, *(rcp--) );
    #else
    rkp -= ( 4 * Nb );
    #endif
	
	#if defined( CONF_AES_DEC_ITER_EXTERN )
	aes_dec_rnd_iter( s, rkp,  sbox,  mulx  );
	#else
    aes_dec_rnd_iter( s, rkp );
	#endif
  }
  //      1 final     round
  #if   !defined( CONF_AES_PRECOMP_RK )
  aes_dec_exp_step( rkp, rkp, *(rcp--) );
  #else
  rkp -= ( 4 * Nb );
  #endif

  #if defined( CONF_AES_DEC_FINI_EXTERN )
  aes_dec_rnd_fini( s, rkp,  sbox );
  #else
  aes_dec_rnd_fini( s, rkp );
  #endif

  #if                                      !defined( CONF_AES_ROUND_PACK )
  U8_TO_U8_N(   r, s );
  #else
  U8_TO_U8_T(   r, s );
  #endif
}
#endif
