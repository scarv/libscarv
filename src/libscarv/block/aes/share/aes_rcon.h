#ifndef __LIBSCARV_AES_RCON_H
#define __LIBSCARV_AES_RCON_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if ( LIBSCARV_CONF_AES_RCON_PRECOMP )
extern uint8_t AES_RCON[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_RCON_PRECOMP"
#endif

#endif
