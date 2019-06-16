/*
 * Based on the SPARX source code package
 * Adapted for the SCARV Project
 *
 * Copyright (C) 2016, 2017 CryptoLUX (https://www.cryptolux.org)
 *
 * Written by Leo Perrin <leo.perrin@uni.lu> and 
              Daniel Dinu <dumitru-daniel.dinu@uni.lu>
   Adapted by Ben Marshall <ben.marshall@bristol.ac.uk>
 *
 * You may use this work under the terms of a Creative Commons CC0 1.0 
 * License/Waiver or the Apache Public License 2.0, at your option. The terms of
 * these licenses can be found at:
 *
 * - CC0 1.0 Universal : http://creativecommons.org/publicdomain/zero/1.0
 * - Apache 2.0        : http://www.apache.org/licenses/LICENSE-2.0
 *
 * You should have received a copy of both of these licenses along with this
 * software. If not, they may be obtained at the above URLs.
 */



/* SPARX instances */
#define SPARX_64_128  0
#define SPARX_128_128 1
#define SPARX_128_256 2


/*
 * Select SPARX instance from:
 *  - SPARX_64_128
 *  - SPARX_128_128
 *  - SPARX_128_256
 */
#ifndef SPARX_INSTANCE
#define SPARX_INSTANCE SPARX_64_128
#endif


#define ROTL(x, n) (((x) << n) | ((x) >> (16 - (n))))
#define SWAP(x, y) tmp = x; x = y; y = tmp


#if (SPARX_INSTANCE == SPARX_64_128)

#define N_STEPS 8
#define ROUNDS_PER_STEPS 3
#define N_BRANCHES 2
#define K_SIZE 4
#define L L_2
#define L_inv L_2_inv
#define K_perm K_perm_64_128

#elif (SPARX_INSTANCE == SPARX_128_128)

#define N_STEPS 8
#define ROUNDS_PER_STEPS 4
#define N_BRANCHES 4
#define K_SIZE 4
#define L L_4
#define L_inv L_4_inv
#define K_perm K_perm_128_128

#elif (SPARX_INSTANCE == SPARX_128_256)

#define N_STEPS 10
#define ROUNDS_PER_STEPS 4
#define N_BRANCHES 4
#define K_SIZE 8
#define L L_4
#define L_inv L_4_inv
#define K_perm K_perm_128_256

#endif

/*!
@brief SPARX Encryption function.
*/
void sparx_encrypt(uint16_t * x, uint16_t k[][2*ROUNDS_PER_STEPS]);

/*!
@brief SPARX Decryption function.
*/
void sparx_decrypt(uint16_t * x, uint16_t k[][2*ROUNDS_PER_STEPS]);

/*!
@brief SPARX Key Schedule function.
*/
void sparx_key_schedule(uint16_t subkeys[][2*ROUNDS_PER_STEPS], uint16_t * master_key);
