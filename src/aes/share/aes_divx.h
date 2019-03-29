#ifndef __AES_DIVX_H
#define __AES_DIVX_H

#include "scarv/util.h"

#if defined( CONF_AES_PRECOMP_DIVX )
extern uint8_t AES_DIVX[];
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_DIVX )"
#endif

#endif
