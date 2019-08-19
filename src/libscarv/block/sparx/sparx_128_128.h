/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <stdint.h>

#include "scarv/block/sparx/sparx_common.h"

#ifndef __LIBSCARV_SPARX_128_128_H
#define __LIBSCARV_SPARX_128_128_H

extern const int sparx_128_128_STEPS;
extern const int sparx_128_128_ROUNDS;
extern const int sparx_128_128_BRANCHES;

void sparx_128_128_key_schedule(
    uint16_t subkeys[][2*sparx_128_128_ROUNDS],
    uint16_t * master_key
);

void sparx_128_128_encrypt(
    uint16_t * x,
    uint16_t k[][2*sparx_128_128_ROUNDS]
);

void sparx_128_128_decrypt(
    uint16_t * x,
    uint16_t k[][2*sparx_128_128_ROUNDS]
);

#endif

