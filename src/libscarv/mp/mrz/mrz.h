#ifndef __MRZ_H
#define __MRZ_H

#include "scarv/util.h"
#include "scarv/mp/limb.h"
#include "scarv/mp/mpn.h"
#include "scarv/mp/mpz.h"

typedef limb_t mrz_t[ CONF_MP_MRZ_MAX_LIMBS ];

typedef struct{
   mrz_t     N; // modulus
   int     l_N; // modulus size, in limbs

   mrz_t rho_0; // \rho^0  \pmod{N}
   mrz_t rho_1; // \rho^1  \pmod{N}
   mrz_t rho_2; // \rho^2  \pmod{N}

  limb_t omega; // -N^{-1} \pmod{\rho}
} mrz_ctx_t;

extern void mrz_precomp( mrz_ctx_t* ctx, const limb_t* N, int l_N );

#include "scarv/mp/mrz_red.h"

#include "scarv/mp/mrz_add.h"
#include "scarv/mp/mrz_sub.h"
#include "scarv/mp/mrz_mul.h"

#include "scarv/mp/mrz_exp.h"

#endif
