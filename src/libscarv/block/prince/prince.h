/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/share/conf.h>

#ifndef _PRINCE_H
#define _PRINCE_H


/*!
@brief perform a single encryption of a prince block.
@param k0 - upper 64 bits of key
@param k1 - lower 64 bits of key
*/
uint64_t prince_enc(uint64_t in, uint64_t k0, uint64_t k1);


/*!
@brief perform a single decryption of a prince block.
@param k0 - upper 64 bits of key
@param k1 - lower 64 bits of key
*/
uint64_t prince_dec(uint64_t in, uint64_t k0, uint64_t k1);

#endif
