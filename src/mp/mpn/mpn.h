#ifndef __MPN_H
#define __MPN_H

#include "scarv/util.h"
#include "scarv/mp/limb.h"

extern int mpn_lop( const limb_t* x, int l_x );

#include "scarv/mp/mpn_cmp.h"

#include "scarv/mp/mpn_add.h"
#include "scarv/mp/mpn_sub.h"
#include "scarv/mp/mpn_sqr.h"
#include "scarv/mp/mpn_mul.h"

#endif
