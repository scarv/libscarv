#include "aes_enc.h"

#if defined( CONF_AES_PRECOMP_SBOX )
uint8_t AES_ENC_SBOX[]= { 
  0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
  0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
  0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
  0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
  0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
  0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
  0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
  0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
  0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
  0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
  0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
  0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
  0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
  0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
  0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
  0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
  0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
  0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
  0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
  0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
  0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
  0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
  0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
  0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
  0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
  0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
  0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
  0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
  0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
  0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
  0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
  0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 
};
#endif

#if defined( CONF_AES_ROUND_SPLIT )

#if !defined( CONF_AES_ENC_INIT_EXTERN )
void aes_enc_rnd_init( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_key( s, rk );
}
#endif

#if !defined( CONF_AES_ENC_ITER_EXTERN )
void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk ) {
  aes_enc_rnd_sub( s     );
  aes_enc_rnd_row( s     );
  aes_enc_rnd_mix( s     );
  aes_enc_rnd_key( s, rk );
}
#endif

#if !defined( CONF_AES_ENC_FINI_EXTERN ) 
void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk ) {
#if defined( CONF_AES_ENC_SUB_EXTERN ) && defined( CONF_AES_ROUND_PACK )
  aes_enc_rnd_sub( s, AES_ENC_SBOX);
#else
  aes_enc_rnd_sub( s     );
#endif
  aes_enc_rnd_row( s     );
  aes_enc_rnd_key( s, rk );
}
#endif

#endif

#if !defined( CONF_AES_ENC_EXP_STEP_EXTERN ) || defined( CONF_AES_ROUND_PACK )
void aes_enc_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rc ) {
  #if !defined( CONF_AES_ROUND_PACK )
  r[  0 ] = rc ^ AES_ENC_SBOX[ rk[ 13 ] ] ^ rk[  0 ];
  r[  1 ] =      AES_ENC_SBOX[ rk[ 14 ] ] ^ rk[  1 ];
  r[  2 ] =      AES_ENC_SBOX[ rk[ 15 ] ] ^ rk[  2 ];
  r[  3 ] =      AES_ENC_SBOX[ rk[ 12 ] ] ^ rk[  3 ];

  r[  4 ] =                     r[  0 ]   ^ rk[  4 ]; 
  r[  5 ] =                     r[  1 ]   ^ rk[  5 ];
  r[  6 ] =                     r[  2 ]   ^ rk[  6 ];
  r[  7 ] =                     r[  3 ]   ^ rk[  7 ];

  r[  8 ] =                     r[  4 ]   ^ rk[  8 ]; 
  r[  9 ] =                     r[  5 ]   ^ rk[  9 ];
  r[ 10 ] =                     r[  6 ]   ^ rk[ 10 ];
  r[ 11 ] =                     r[  7 ]   ^ rk[ 11 ];

  r[ 12 ] =                     r[  8 ]   ^ rk[ 12 ]; 
  r[ 13 ] =                     r[  9 ]   ^ rk[ 13 ];
  r[ 14 ] =                     r[ 10 ]   ^ rk[ 14 ];
  r[ 15 ] =                     r[ 11 ]   ^ rk[ 15 ];
  #else
  uint32_t*  rp = ( uint32_t* )(  r );
  uint32_t* rkp = ( uint32_t* )( rk );

  uint32_t  t_0 = rkp[ 0 ];
  uint32_t  t_1 = rkp[ 1 ];
  uint32_t  t_2 = rkp[ 2 ];
  uint32_t  t_3 = rkp[ 3 ];

  uint32_t  t_4 = ( uint32_t )( rc ) ^ t_0 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_1 >> 24 ) & 0xFF ] );
  uint32_t  t_5 =                      t_1 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_2 >> 24 ) & 0xFF ] );
  uint32_t  t_6 =                      t_2 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_3 >> 24 ) & 0xFF ] );
  uint32_t  t_7 =                      t_3 ^ ( uint32_t )( AES_ENC_SBOX[ ( t_0 >> 24 ) & 0xFF ] );
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

#if defined( CONF_AES_PRECOMP_RK )
void aes_enc_exp( uint8_t* r, const uint8_t* k ) {
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
}
#endif

#if !defined( CONF_AES_ENC_EXTERN ) || !defined( CONF_AES_PRECOMP_RK )
void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k ) {  
    uint8_t  s[ 4 * Nb ];

    #if   !defined( CONF_AES_PRECOMP_RK )
    uint8_t rk[ 4 * Nb ]; 
    uint8_t* rcp =      AES_RC; 
    uint8_t* rkp =                   rk;
    #else
    uint8_t* rkp =                    k; 
    #endif

    #if                                      !defined( CONF_AES_ROUND_PACK )
    U8_TO_U8_N(   s, m );
    #else
    U8_TO_U8_T(   s, m );
    #endif
    #if   !defined( CONF_AES_PRECOMP_RK ) && !defined( CONF_AES_ROUND_PACK )
    U8_TO_U8_N( rkp, k );
    #elif !defined( CONF_AES_PRECOMP_RK ) &&  defined( CONF_AES_ROUND_PACK )
    U8_TO_U8_T( rkp, k );
    #endif

  //      1 initial   round
    aes_enc_rnd_init( s, rkp );
  // Nr - 1 interated rounds
  for( int i = 1; i < Nr; i++ ) {
    #if   !defined( CONF_AES_PRECOMP_RK )
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
    #else
    rkp += ( 4 * Nb );
    #endif
		
	#if defined( CONF_AES_ENC_ITER_EXTERN ) && defined( CONF_AES_ROUND_PACK )
		#if !defined ( CONF_AES_ENC_XCRYPT )
		aes_enc_rnd_iter( s, rkp,  AES_ENC_SBOX );
		#else
		aes_enc_rnd_iter( s, rkp,  AES_ENC_SBOX,  AES_MULX );
		#endif			
	#else
	aes_enc_rnd_iter( s, rkp );
	#endif		
  }
  //      1 final     round
    #if   !defined( CONF_AES_PRECOMP_RK )
    aes_enc_exp_step( rkp, rkp, *(++rcp) );
    #else
    rkp += ( 4 * Nb );
    #endif
	
	#if defined( CONF_AES_ENC_FINI_EXTERN ) && defined( CONF_AES_ROUND_PACK )
    aes_enc_rnd_fini( s, rkp,  AES_ENC_SBOX);
	#else
		aes_enc_rnd_fini( s, rkp );
	#endif

    #if                                      !defined( CONF_AES_ROUND_PACK )
    U8_TO_U8_N(   r, s );
    #else
    U8_TO_U8_T(   r, s );
    #endif
}
#endif
