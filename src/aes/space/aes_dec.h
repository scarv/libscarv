#ifndef __AES_DEC_H
#define __AES_DEC_H

#include "util.h"

#include "aes_conf.h"
#include "aes_rc.h"

#include "aes_enc.h"
#include "aes_dec_imp.h"

#if defined( CONF_AES_PRECOMP_SBOX )
extern uint8_t AES_DEC_SBOX[];
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_SBOX )"
#endif

#if defined( CONF_AES_ROUND_SPLIT )
extern void aes_dec_rnd_init( uint8_t* s, uint8_t* rk );
extern void aes_dec_rnd_iter( uint8_t* s, uint8_t* rk );
extern void aes_dec_rnd_fini( uint8_t* s, uint8_t* rk );
#endif

#if defined( CONF_AES_PRECOMP_RK )
extern void aes_dec_exp     ( uint8_t* r, const uint8_t*  k             );
#endif
extern void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rc );

extern void aes_dec( uint8_t* r, uint8_t* c, uint8_t* k );

#endif
