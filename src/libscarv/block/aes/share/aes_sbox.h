#ifndef __LIBSCARV_AES_SBOX_H
#define __LIBSCARV_AES_SBOX_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if ( LIBSCARV_CONF_AES_SBOX_PRECOMP ) && ( LIBSCARV_CONF_AES_ENC_ENABLE )
extern uint8_t AES_ENC_SBOX[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_PRECOMP_SBOX"
#endif
#if ( LIBSCARV_CONF_AES_SBOX_PRECOMP ) && ( LIBSCARV_CONF_AES_DEC_ENABLE )
extern uint8_t AES_DEC_SBOX[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_PRECOMP_SBOX"
#endif

#endif
