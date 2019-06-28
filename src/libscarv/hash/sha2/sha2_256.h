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

#define SHA2_256_SIZEOF_BLOCK  ( 64 )
#define SHA2_256_SIZEOF_DIGEST ( 32 )

extern void sha2_256_init();

extern void sha2_256_hash( const uint8_t* m, int n_m );
extern void sha2_256_fini(       uint8_t* d          );

extern void sha2_256( uint8_t* d, int l, ... );

#endif

