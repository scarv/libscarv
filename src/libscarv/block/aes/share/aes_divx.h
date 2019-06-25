#ifndef __AES_DIVX_H
#define __AES_DIVX_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if defined( LIBSCARV_CONF_AES_PRECOMP_DIVX )
extern uint8_t AES_DIVX[];
#else
#error "no implementation for !defined( LIBSCARV_CONF_AES_PRECOMP_DIVX )"
#endif

#endif
