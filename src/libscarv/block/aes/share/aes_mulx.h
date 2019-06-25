#ifndef __AES_MULX_H
#define __AES_MULX_H

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

#if defined( LIBSCARV_CONF_AES_PRECOMP_MULX )
extern uint8_t AES_MULX[];
#else
#error "no implementation for !defined( LIBSCARV_CONF_AES_PRECOMP_MULX )"
#endif

#endif
