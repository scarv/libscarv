
#include <stdint.h>

#include "scarv/scarv.h"

#ifndef __LIBSCARV_SPARX_COMMON_H
#define __LIBSCARV_SPARX_COMMON_H

#define SPARX_SWAP(x, y) tmp = x; x = y; y = tmp

#if ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV_XCRYPTO )

#include "scarv/share/xcrypto_intrinsics.h"

#define SPARX_ROTL(x, n) ((uint16_t)_xc_pror_h(x,16-n))

#define SPARX_A(l, r) __asm__(      \
    "xc.pror.i h, %0, %0, 16-9;"    \
    "xc.padd   h, %0, %0,   %1;"    \
    "xc.pror.i h, %1, %1, 16-2;"    \
    "xor          %1, %1,   %0;":   \
        "+r"(l), "+r"(r) );

#define SPARX_A_INV(l, r) __asm__(  \
    "xor          %1, %1, %0;"      \
    "xc.pror.i h, %1, %1, 16-14;"   \
    "xc.psub   h, %0, %0, %1;"      \
    "xc.pror.i h, %0, %0, 16- 7;":  \
        "+r"(l), "+r"(r) );

#else // LIBSCARV_CONF_ARCH != LIBSCARV_CONF_ARCH_RISCV_XCRYPTO

#define SPARX_ROTL(x, n) (((x) << n) | ((x) >> (16 - (n))))

#define SPARX_A(l, r)       \
    l = SPARX_ROTL(l, 9);   \
    l += r;                 \
    r = SPARX_ROTL(r, 2);   \
    r ^= l;                 \

#define SPARX_A_INV(l, r)   \
    r ^= l;                 \
    r = SPARX_ROTL(r, 14);  \
    l -= r;                 \
    l = SPARX_ROTL(l, 7);   \

#endif // LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV_XCRYPTO

void sparx_L_2(uint16_t * x);
void sparx_L_2_inv(uint16_t * x);

void sparx_L_4(uint16_t * x);
void sparx_L_4_inv(uint16_t * x);

#endif
