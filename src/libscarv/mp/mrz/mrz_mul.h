#ifndef __MRZ_MUL_H
#define __MRZ_MUL_H

#include  "scarv/mp/mrz.h"

// r = x * y * \rho^{-1} \pmod{N}
extern void mrz_mul( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const mrz_t y );

#endif
