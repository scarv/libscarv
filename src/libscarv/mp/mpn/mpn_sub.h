#ifndef __LIBSCARV_MPN_SUB_H
#define __LIBSCARV_MPN_SUB_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mpn/mpn.h>

extern limb_t mpn_sub  ( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );

extern limb_t mpn_sub_1( limb_t* r, const limb_t* x, int l_x, const limb_t  y          );
extern limb_t mpn_sub_n( limb_t* r, const limb_t* x,          const limb_t* y, int l   );

#endif
