#ifndef __AES_RC_H
#define __AES_RC_H

#include "scarv/util.h"

#if defined( CONF_AES_PRECOMP_RC )
extern uint8_t AES_RC[];
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_RC )"
#endif

#endif
