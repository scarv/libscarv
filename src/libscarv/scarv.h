#ifndef __LIBSCARV_H
#define __LIBSCARV_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#if ( LIBSCARV_CONF_AES_ENABLE )
#include <scarv/block/aes/aes_enc.h>
#include <scarv/block/aes/aes_dec.h>
#endif

#if ( LIBSCARV_CONF_SHA1_ENABLE )
#include <scarv/hash/sha1/sha1.h>
#endif
#if ( LIBSCARV_CONF_SHA2_ENABLE )
#include <scarv/hash/sha2/sha2_256.h>
#include <scarv/hash/sha2/sha2_512.h>
#endif
#if ( LIBSCARV_CONF_SHA3_ENABLE )
#include <scarv/hash/sha3/sha3.h>
#endif
#if ( LIBSCARV_CONF_KECCAKP400_ENABLE )
#include <scarv/hash/keccakp400/KeccakP-400-SnP.h>
#include <scarv/hash/keccakp400/KeccakP-1600-SnP.h>
#endif

#if ( LIBSCARV_CONF_LIMB_ENABLE )
#include <scarv/mp/limb/limb.h>
#endif
#if ( LIBSCARV_CONF_MPN_ENABLE )
#include <scarv/mp/mpn/mpn.h>
#endif
#if ( LIBSCARV_CONF_MPZ_ENABLE )
#include <scarv/mp/mpz/mpz.h>
#endif
#if ( LIBSCARV_CONF_MRZ_ENABLE )
#include <scarv/mp/mrz/mrz.h>
#endif

#if ( LIBSCARV_CONF_CHACHA20_ENABLE )
#include <scarv/stream/chacha20/chacha20.h>
#endif

#if ( LIBSCARV_CONF_PRINCE_ENABLE )
#include <scarv/stream/prince/prince.h>
#endif

#endif
