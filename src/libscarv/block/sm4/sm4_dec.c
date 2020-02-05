/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/sm4/sm4_dec.h>

#if ( !LIBSCARV_CONF_SM4_DEC_EXP_STEP_EXTERN ) 
uint32_t sm4_dec_exp_step( uint32_t* r, const uint32_t* k, uint32_t ck ) {
  uint32_t t_0 = k[ 0 ];
  uint32_t t_1 = k[ 1 ];
  uint32_t t_2 = k[ 2 ];
  uint32_t t_3 = k[ 3 ];

  uint32_t t_4  = t_0 ^ t_1 ^ t_2 ^ ck;

           t_4  = ( ( uint32_t )( SM4_SBOX[ ( t_4 >>  0 ) & 0xFF ] ) <<  0 ) |
                  ( ( uint32_t )( SM4_SBOX[ ( t_4 >>  8 ) & 0xFF ] ) <<  8 ) |
                  ( ( uint32_t )( SM4_SBOX[ ( t_4 >> 16 ) & 0xFF ] ) << 16 ) |
                  ( ( uint32_t )( SM4_SBOX[ ( t_4 >> 24 ) & 0xFF ] ) << 24 ) ;
         
           t_4 ^= U32_RTL( t_4, 13 ) ^ 
                  U32_RTL( t_4, 23 ) ;
       
           t_4 ^= t_3;

  r[ 0 ] = t_4;
  r[ 1 ] = t_0;
  r[ 2 ] = t_1;
  r[ 3 ] = t_2;

  return t_3;
}
#endif

#if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )
void sm4_dec_exp( uint32_t* r, const uint8_t* k ) {
  uint32_t t[ 4 ];

  U8_TO_U32_BE( t[ 0 ], k,  0 );
  U8_TO_U32_BE( t[ 1 ], k,  4 );
  U8_TO_U32_BE( t[ 2 ], k,  8 );
  U8_TO_U32_BE( t[ 3 ], k, 12 );

  #if ( LIBSCARV_CONF_SM4_KEY_EVOLVE_FWD )
  t[ 0 ] ^= SM4_FK[ 0 ];
  t[ 1 ] ^= SM4_FK[ 1 ];
  t[ 2 ] ^= SM4_FK[ 2 ];
  t[ 3 ] ^= SM4_FK[ 3 ];

  for( int i = 0; i < 32; i++ ) {
    r[      i     ] = sm4_enc_exp_step( t, t, SM4_CK[      i     ] );
  }
  #endif

  #if ( LIBSCARV_CONF_SM4_KEY_EVOLVE_REV )
  for( int i = 0; i < 32; i++ ) {
    r[ 32 - i - 1 ] = sm4_dec_exp_step( t, t, SM4_CK[ 32 - i - 1 ] );
  }
  #endif
}
#endif

#if ( !LIBSCARV_CONF_SM4_DEC_EXTERN ) 
void sm4_dec( uint8_t* r, uint8_t* c, uint8_t* k ) {
    #if ( !LIBSCARV_CONF_SM4_KEY_PRECOMP )
    uint32_t rk[ 4 ];
  
    U8_TO_U32_BE( rk[ 0 ], k,  0 );
    U8_TO_U32_BE( rk[ 1 ], k,  4 );
    U8_TO_U32_BE( rk[ 2 ], k,  8 );
    U8_TO_U32_BE( rk[ 3 ], k, 12 );
    #else
    uint32_t* rk = ( uint32_t* )( k );
    #endif
  
    uint32_t t_0, t_1, t_2, t_3, t_4;
  
    U8_TO_U32_BE( t_0, c,  0 );
    U8_TO_U32_BE( t_1, c,  4 );
    U8_TO_U32_BE( t_2, c,  8 );
    U8_TO_U32_BE( t_3, c, 12 );

    #if ( !LIBSCARV_CONF_SM4_KEY_PRECOMP ) && ( LIBSCARV_CONF_SM4_KEY_EVOLVE_FWD )
    rk[ 0 ] ^= SM4_FK[ 0 ];
    rk[ 1 ] ^= SM4_FK[ 1 ];
    rk[ 2 ] ^= SM4_FK[ 2 ];
    rk[ 3 ] ^= SM4_FK[ 3 ];

    for( int i = 0; i < 32; i++ ) {
           sm4_enc_exp_step( rk, rk, SM4_CK[      i     ] );
    }
    #endif

  for( int i = 0; i < 32; i++ ) {
    t_4  = t_1 ^ t_2 ^ t_3;
    #if ( !LIBSCARV_CONF_SM4_KEY_PRECOMP )
    t_4 ^= sm4_dec_exp_step( rk, rk, SM4_CK[ 32 - i - 1 ] );
    #else
    t_4 ^= rk[ 32 - i - 1 ];
    #endif

    t_4  = ( ( uint32_t )( SM4_SBOX[ ( t_4 >>  0 ) & 0xFF ] ) <<  0 ) |
           ( ( uint32_t )( SM4_SBOX[ ( t_4 >>  8 ) & 0xFF ] ) <<  8 ) |
           ( ( uint32_t )( SM4_SBOX[ ( t_4 >> 16 ) & 0xFF ] ) << 16 ) |
           ( ( uint32_t )( SM4_SBOX[ ( t_4 >> 24 ) & 0xFF ] ) << 24 ) ;
  
    t_4 ^= U32_RTL( t_4,  2 ) ^ 
           U32_RTL( t_4, 10 ) ^ 
           U32_RTL( t_4, 18 ) ^ 
           U32_RTL( t_4, 24 ) ;

    t_4 ^= t_0;

    t_0  = t_1;
    t_1  = t_2;
    t_2  = t_3;
    t_3  = t_4;
  }
  
    U32_TO_U8_BE( r, t_3,  0 );
    U32_TO_U8_BE( r, t_2,  4 );
    U32_TO_U8_BE( r, t_1,  8 );
    U32_TO_U8_BE( r, t_0, 12 );
}
#endif
