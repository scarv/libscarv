#ifndef __LIBSCARV_MRZ_EXP_H
#define __LIBSCARV_MRZ_EXP_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mrz/mrz.h>

// r = x^y \pmod{N}
extern void mrz_exp( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const limb_t* y, int l_y );

#endif
