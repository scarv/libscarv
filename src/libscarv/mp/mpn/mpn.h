#ifndef __MPN_H
#define __MPN_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/limb/limb.h>

extern int mpn_lop( const limb_t* x, int l_x );

#include <scarv/mp/mpn/mpn_cmp.h>

#include <scarv/mp/mpn/mpn_add.h>
#include <scarv/mp/mpn/mpn_sub.h>
#include <scarv/mp/mpn/mpn_sqr.h>
#include <scarv/mp/mpn/mpn_mul.h>

#endif
