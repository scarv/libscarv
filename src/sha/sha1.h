#ifndef __SHA1_H
#define __SHA1_H

#include "util.h"

#define SHA1_SIZEOF_BLOCK  ( 64 )
#define SHA1_SIZEOF_DIGEST ( 20 )

extern void sha1_init();

extern void sha1_hash( const uint8_t* m, int n_m );
extern void sha1_fini(       uint8_t* d          );

extern void sha1( uint8_t* d, int l, ... );

#endif
