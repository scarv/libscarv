/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_SHA2_256_H
#define __LIBSCARV_SHA2_256_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define SHA2_256_SIZEOF_BLOCK  (  64 )
#define SHA2_256_SIZEOF_DIGEST (  32 )

typedef struct {
  uint32_t W[  64 ]; // working array
  uint32_t H[   8 ]; // current hash digest
  uint8_t  B[  64 ]; // current hash block

  uint64_t n_left;   // bytes remaining
  uint64_t n_done;   // bytes processed so far
} sha2_256_ctx_t;

extern void sha2_256_init( sha2_256_ctx_t* ctx                            );
extern void sha2_256_hash( sha2_256_ctx_t* ctx, const uint8_t* m, int n_m );
extern void sha2_256_fini( sha2_256_ctx_t* ctx,       uint8_t* d          );

extern void sha2_256( uint8_t* d, int l, ... );

extern uint32_t SHA2_256_K[64];

#endif

