#ifndef __LIBSCARV_MPN_SQR_H
#define __LIBSCARV_MPN_SQR_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mpn/mpn.h>

extern void mpn_sqr  ( limb_t* r, const limb_t* x, int l_x );

extern void mpn_sqr_1( limb_t* r, const limb_t  x          );
extern void mpn_sqr_n( limb_t* r, const limb_t* x, int l   );

#endif
