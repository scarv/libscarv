/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_AES_MULX_H
#define __LIBSCARV_AES_MULX_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define AES_MULX_PACKED(r,x) {          \
  uint32_t __t_0 =   (x) &  0x7F7F7F7F; \
  uint32_t __t_1 =   (x) &  0x80808080; \
  uint32_t __t_2 = __t_0 <<     1;      \
  uint32_t __t_3 = __t_1 >>     7;      \
  uint32_t __t_4 = __t_3 *  0x0000001B; \
             (r) = __t_2 ^  __t_4;      \
}

#if ( LIBSCARV_CONF_AES_MULX_PRECOMP )
extern uint8_t AES_MULX[];
#else
#error "no implementation for !LIBSCARV_CONF_AES_MULX_PRECOMP"
#endif

#endif
