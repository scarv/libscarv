
#include <stdint.h>

#include "scarv/util.h"

#ifndef CHACHA20_H
#define CHACHA20_H

/*!
@brief Implements the ChaCha20 block transformation
*/
void chacha20_block(
    uint32_t output[16], //!< Output array
    uint32_t input [16]  //!< Input array
);

#endif
