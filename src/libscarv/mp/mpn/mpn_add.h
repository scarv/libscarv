#ifndef __MPN_ADD_H
#define __MPN_ADD_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mpn/mpn.h>

extern limb_t mpn_add  ( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );

extern limb_t mpn_add_1( limb_t* r, const limb_t* x, int l_x, const limb_t  y          );
extern limb_t mpn_add_n( limb_t* r, const limb_t* x,          const limb_t* y, int l   );

#endif
