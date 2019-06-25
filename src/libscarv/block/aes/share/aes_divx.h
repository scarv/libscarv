#ifndef __LIBSCARV_AES_DIVX_H
#define __LIBSCARV_AES_DIVX_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if ( LIBSCARV_CONF_AES_DIVX_PRECOMP )
extern uint8_t AES_DIVX[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_DIVX_PRECOMP"
#endif

#endif
