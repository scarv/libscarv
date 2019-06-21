#ifndef __SHA2_512_H
#define __SHA2_512_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define SHA2_512_SIZEOF_BLOCK  ( 128 )
#define SHA2_512_SIZEOF_DIGEST (  64 )

extern void sha2_512_init();

extern void sha2_512_hash( const uint8_t* m, int n_m );
extern void sha2_512_fini(       uint8_t* d          );

extern void sha2_512( uint8_t* d, int l, ... );

#endif

