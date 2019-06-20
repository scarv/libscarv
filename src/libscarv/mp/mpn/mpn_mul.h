#ifndef __MPN_MUL_H
#define __MPN_MUL_H

#include  "mpn.h"

extern void mpn_mul  ( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );

extern void mpn_mul_1( limb_t* r, const limb_t* x, int l_x, const limb_t  y          );
extern void mpn_mul_n( limb_t* r, const limb_t* x,          const limb_t* y, int l   );

#endif
