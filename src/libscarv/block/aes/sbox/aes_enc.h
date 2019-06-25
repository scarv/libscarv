#ifndef __LIBSCARV_AES_ENC_H
#define __LIBSCARV_AES_ENC_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/block/aes/aes_conf.h>
#include <scarv/block/aes/aes_divx.h>
#include <scarv/block/aes/aes_mulx.h>
#include <scarv/block/aes/aes_rcon.h>
#include <scarv/block/aes/aes_sbox.h>

#include <scarv/block/aes/aes_dec.h>

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP )
extern void aes_enc_exp     ( uint8_t* r, const uint8_t*  k               );
#endif
extern void aes_enc_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon );

extern void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k );

#endif
