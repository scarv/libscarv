/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

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
