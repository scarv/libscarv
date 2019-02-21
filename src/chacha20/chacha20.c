
#include "scarv/chacha20/chacha20.h"


#define QRF(a,b,c,d) \
    a += b; d ^= a; d = U32_RTL(d, 16); \
    c += b; b ^= a; b = U32_RTL(b, 12); \
    a += b; d ^= a; d = U32_RTL(d,  8); \
    c += b; b ^= a; b = U32_RTL(b,  7); 

/*!
@brief Implements the ChaCha20 block transformation
*/
void chacha20_block(
    uint32_t output[16], //!< Output array
    uint32_t input [16]  //!< Input array
){

    uint32_t tmp[16];

    for(int i = 0; i < 16; i ++) {
        tmp[i] = input[i];
    }

    for(int i = 0; i < 20; i ++) {
        QRF(tmp[ 0], tmp[ 4], tmp[ 8], tmp[12]);
        QRF(tmp[ 1], tmp[ 5], tmp[ 9], tmp[13]);
        QRF(tmp[ 2], tmp[ 6], tmp[10], tmp[14]);
        QRF(tmp[ 3], tmp[ 7], tmp[11], tmp[15]);
        
        QRF(tmp[ 0], tmp[ 5], tmp[10], tmp[15]);
        QRF(tmp[ 1], tmp[ 6], tmp[11], tmp[12]);
        QRF(tmp[ 2], tmp[ 7], tmp[ 8], tmp[13]);
        QRF(tmp[ 3], tmp[ 4], tmp[ 9], tmp[14]);
    }

    for(int i = 0; i < 16; i ++) {
        output[i] = input[i] + tmp[i];
    }

    return;
}
