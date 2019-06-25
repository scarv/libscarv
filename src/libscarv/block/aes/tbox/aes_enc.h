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

#if ( LIBSCARV_CONF_AES_TBOX_PRECOMP )
extern uint32_t AES_ENC_TBOX_0[];
extern uint32_t AES_ENC_TBOX_1[];
extern uint32_t AES_ENC_TBOX_2[];
extern uint32_t AES_ENC_TBOX_3[];
extern uint32_t AES_ENC_TBOX_4[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_TBOX_PRECOMP"
#endif

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP )
extern void aes_enc_exp( uint8_t* r, const uint8_t* k );
#else
#error "no implementation for !LIBSCARV_CONF_AES_KEY_PRECOMP"
#endif

extern void aes_enc( uint8_t* r, uint8_t* m, uint8_t* rk );

#endif
