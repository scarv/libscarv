/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_SHA1_H
#define __LIBSCARV_SHA1_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define SHA1_SIZEOF_BLOCK  ( 64 )
#define SHA1_SIZEOF_DIGEST ( 20 )

typedef struct {
  uint32_t W[  80 ]; // working array
  uint32_t H[   5 ]; // current hash digest
  uint8_t  B[  64 ]; // current hash block

  uint64_t n_left;   // bytes remaining
  uint64_t n_done;   // bytes processed so far
} sha1_ctx_t;

extern void sha1_init( sha1_ctx_t* ctx                            );
extern void sha1_hash( sha1_ctx_t* ctx, const uint8_t* m, int n_m );
extern void sha1_fini( sha1_ctx_t* ctx,       uint8_t* d          );

extern void sha1( uint8_t* d, int l, ... );

#endif
