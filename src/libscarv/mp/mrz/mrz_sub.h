#ifndef __MRZ_SUB_H
#define __MRZ_SUB_H

#include  "scarv/mp/mrz.h"

// r = x - y \pmod{N}
extern void mrz_sub( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const mrz_t y );

#endif

