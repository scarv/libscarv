#ifndef __AES_ENC_H
#define __AES_ENC_H

#include "util.h"

#include "aes_conf.h"
#include "aes_rc.h"

#include "aes_dec.h"
#include "aes_enc_imp.h"

#if defined( CONF_AES_PRECOMP_TBOX )
extern uint32_t AES_ENC_TBOX_0[];
extern uint32_t AES_ENC_TBOX_1[];
extern uint32_t AES_ENC_TBOX_2[];
extern uint32_t AES_ENC_TBOX_3[];
extern uint32_t AES_ENC_TBOX_4[];
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_TBOX )"
#endif

#if defined( CONF_AES_PRECOMP_RK )
extern void aes_enc_exp( uint8_t* r, const uint8_t* k );
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_RK )"
#endif

extern void aes_enc( uint8_t* r, uint8_t* m, uint8_t* rk );

#endif
