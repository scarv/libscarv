/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <stdint.h>

#include "scarv/block/sparx/sparx_common.h"

#ifndef __LIBSCARV_SPARX_128_256_H
#define __LIBSCARV_SPARX_128_256_H

extern const int sparx_128_256_STEPS;
extern const int sparx_128_256_ROUNDS;
extern const int sparx_128_256_BRANCHES;

void sparx_128_256_key_schedule(
    uint16_t subkeys[][2*sparx_128_256_ROUNDS],
    uint16_t * master_key
);

void sparx_128_256_encrypt(
    uint16_t * x,
    uint16_t k[][2*sparx_128_256_ROUNDS]
);

void sparx_128_256_decrypt(
    uint16_t * x,
    uint16_t k[][2*sparx_128_256_ROUNDS]
);

#endif

