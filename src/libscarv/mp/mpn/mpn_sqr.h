#ifndef __MPN_SQR_H
#define __MPN_SQR_H

#include  "mpn.h"

extern void mpn_sqr  ( limb_t* r, const limb_t* x, int l_x );

extern void mpn_sqr_1( limb_t* r, const limb_t  x          );
extern void mpn_sqr_n( limb_t* r, const limb_t* x, int l   );

#endif
