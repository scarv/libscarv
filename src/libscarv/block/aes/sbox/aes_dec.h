#ifndef __AES_DEC_H
#define __AES_DEC_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/block/aes/aes_conf.h>
#include <scarv/block/aes/aes_divx.h>
#include <scarv/block/aes/aes_mulx.h>
#include <scarv/block/aes/aes_rcon.h>

#if ( LIBSCARV_CONF_AES_ROUND_SPLIT )
extern void aes_dec_rnd_init( uint8_t* s, uint8_t* rk );
#endif
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_DEC_ITER_EXTERN ) 
extern void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk );
#else
extern void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk, uint8_t* sbox, uint8_t* mulx );
#endif 
#if ( LIBSCARV_CONF_AES_ROUND_SPLIT ) && ( !LIBSCARV_CONF_AES_DEC_FINI_EXTERN )
extern void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk );
#else
extern void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk, uint8_t* sbox );
#endif

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP )
extern void aes_dec_exp     ( uint8_t* r, const uint8_t*  k             );
#endif
extern void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rc );

extern void aes_dec( uint8_t* r, uint8_t* m, uint8_t* k, uint8_t* sbox, uint8_t* mulx );

#endif
