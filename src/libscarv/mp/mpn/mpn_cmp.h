#ifndef __MPN_CMP_H
#define __MPN_CMP_H

#include  "mpn.h"

extern int mpn_cmp  ( const limb_t* x, int l_x, const limb_t* y, int l_y );

extern int mpn_cmp_1( const limb_t* x, int l_x, const limb_t  y          );
extern int mpn_cmp_n( const limb_t* x,          const limb_t* y, int l   );

#endif

