#ifndef __MPN_SUB_H
#define __MPN_SUB_H

#include  "mpn.h"

extern limb_t mpn_sub  ( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );

extern limb_t mpn_sub_1( limb_t* r, const limb_t* x, int l_x, const limb_t  y          );
extern limb_t mpn_sub_n( limb_t* r, const limb_t* x,          const limb_t* y, int l   );

#endif
