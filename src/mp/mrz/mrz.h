#ifndef __MRZ_H
#define __MRZ_H

#include "util.h"
#include "limb.h"
#include  "mpn.h"
#include  "mpz.h"

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

#include "mrz_red.h"

#include "mrz_add.h"
#include "mrz_sub.h"
#include "mrz_mul.h"

#include "mrz_exp.h"

#endif
