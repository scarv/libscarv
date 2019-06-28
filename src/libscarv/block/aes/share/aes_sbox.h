/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_AES_SBOX_H
#define __LIBSCARV_AES_SBOX_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if ( LIBSCARV_CONF_AES_SBOX_PRECOMP )
extern uint8_t AES_ENC_SBOX[];
extern uint8_t AES_DEC_SBOX[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_PRECOMP_SBOX"
#endif

#endif
