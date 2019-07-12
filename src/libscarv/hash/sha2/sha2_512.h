/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_SHA2_512_H
#define __LIBSCARV_SHA2_512_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define SHA2_512_SIZEOF_BLOCK  ( 128 )
#define SHA2_512_SIZEOF_DIGEST (  64 )

typedef struct {
  uint64_t W[  80 ]; // working array
  uint64_t H[   8 ]; // current hash digest
  uint8_t  B[ 128 ]; // current hash block

  uint64_t n_left;   // bytes remaining
  uint64_t n_done;   // bytes processed so far
} sha2_512_ctx_t;

extern void sha2_512_init( sha2_512_ctx_t* ctx                            );
extern void sha2_512_hash( sha2_512_ctx_t* ctx, const uint8_t* m, int n_m );
extern void sha2_512_fini( sha2_512_ctx_t* ctx,       uint8_t* d          );

extern void sha2_512( uint8_t* d, int l, ... );

#endif

