#ifndef __MRZ_RED_H
#define __MRZ_RED_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mrz/mrz.h>

// r = x * \rho^{-1} \pmod{N}
extern void mrz_red( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x );

#endif
