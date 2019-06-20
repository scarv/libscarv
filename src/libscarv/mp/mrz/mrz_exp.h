#ifndef __MRZ_EXP_H
#define __MRZ_EXP_H

#include  "scarv/mp/mrz.h"

// r = x^y \pmod{N}
extern void mrz_exp( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const limb_t* y, int l_y );

#endif
