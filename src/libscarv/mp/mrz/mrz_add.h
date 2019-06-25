#ifndef __LIBSCARV_MRZ_ADD_H
#define __LIBSCARV_MRZ_ADD_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/mp/mrz/mrz.h>

// r = x + y \pmod{N}
extern void mrz_add( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const mrz_t y );

#endif
