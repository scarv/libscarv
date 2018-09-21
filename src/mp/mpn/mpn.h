#ifndef __MPN_H
#define __MPN_H

#include "util.h"
#include "limb.h"

extern int mpn_lop( const limb_t* x, int l_x );

#include "mpn_cmp.h"

#include "mpn_add.h"
#include "mpn_sub.h"
#include "mpn_sqr.h"
#include "mpn_mul.h"

#endif
