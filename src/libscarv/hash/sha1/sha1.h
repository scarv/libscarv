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

extern void sha1_init();

extern void sha1_hash( const uint8_t* m, int n_m );
extern void sha1_fini(       uint8_t* d          );

extern void sha1( uint8_t* d, int l, ... );

#endif
