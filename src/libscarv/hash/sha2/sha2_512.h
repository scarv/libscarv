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

extern void sha2_512_init();

extern void sha2_512_hash( const uint8_t* m, int n_m );
extern void sha2_512_fini(       uint8_t* d          );

extern void sha2_512( uint8_t* d, int l, ... );

#endif

