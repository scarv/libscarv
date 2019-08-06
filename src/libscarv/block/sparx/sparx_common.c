
#include "scarv/block/sparx/sparx_common.h"

#if ( LIBSCARV_CONF_SPARX_L_EXTERN == 1 )

// See architecture specific folders.

#else // ( LIBSCARV_CONF_SPARX_L_EXTERN == 0 )

void sparx_L_2(uint16_t * x)
{
    uint16_t tmp = SPARX_ROTL((x[0] ^ x[1]), 8);
    x[2] ^= x[0] ^ tmp;
    x[3] ^= x[1] ^ tmp;
    SPARX_SWAP(x[0], x[2]);
    SPARX_SWAP(x[1], x[3]);
}

void sparx_L_2_inv(uint16_t * x)
{
    uint16_t tmp;
    SPARX_SWAP(x[0], x[2]);
    SPARX_SWAP(x[1], x[3]);
    tmp = SPARX_ROTL(x[0] ^ x[1], 8);
    x[2] ^= x[0] ^ tmp;
    x[3] ^= x[1] ^ tmp;
}

void sparx_L_4(uint16_t * x)
{
    uint16_t tmp = x[0] ^ x[1] ^ x[2] ^ x[3];
    tmp = SPARX_ROTL(tmp, 8);

    x[4] ^= x[2] ^ tmp;
    x[5] ^= x[1] ^ tmp;
    x[6] ^= x[0] ^ tmp;
    x[7] ^= x[3] ^ tmp;

    SPARX_SWAP(x[0], x[4]);
    SPARX_SWAP(x[1], x[5]);
    SPARX_SWAP(x[2], x[6]);
    SPARX_SWAP(x[3], x[7]);
}

void sparx_L_4_inv(uint16_t * x)
{
    uint16_t tmp;
    SPARX_SWAP(x[0], x[4]);
    SPARX_SWAP(x[1], x[5]);
    SPARX_SWAP(x[2], x[6]);
    SPARX_SWAP(x[3], x[7]);

    tmp = x[0] ^ x[1] ^ x[2] ^ x[3];
    tmp = SPARX_ROTL(tmp, 8);
    x[4] ^= x[2] ^ tmp;
    x[5] ^= x[1] ^ tmp;
    x[6] ^= x[0] ^ tmp;
    x[7] ^= x[3] ^ tmp;
}
#endif // ( LIBSCARV_CONF_SPARX_L_EXTERN == 1 )
