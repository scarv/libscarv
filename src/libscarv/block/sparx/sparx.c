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


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "sparx.h"

/* Basic functions and their inverses */
/* ================================== */

/* One keyless round of SPECK-32 */
void A(uint16_t * l, uint16_t * r)
{
    (*l) = ROTL((*l), 9);
    (*l) += (*r);
    (*r) = ROTL((*r), 2);
    (*r) ^= (*l);
}

/* One keyless inverse round of SPECK-32 */
void A_inv(uint16_t * l, uint16_t * r)
{
    (*r) ^= (*l);
    (*r) = ROTL((*r), 14);
    (*l) -= (*r);
    (*l) = ROTL((*l), 7);
}


/* The linear layers */

void L_2(uint16_t * x)
{
    uint16_t tmp = ROTL((x[0] ^ x[1]), 8);
    x[2] ^= x[0] ^ tmp;
    x[3] ^= x[1] ^ tmp;
    SWAP(x[0], x[2]);
    SWAP(x[1], x[3]);
}

void L_2_inv(uint16_t * x)
{
    uint16_t tmp;
    SWAP(x[0], x[2]);
    SWAP(x[1], x[3]);
    tmp = ROTL(x[0] ^ x[1], 8);
    x[2] ^= x[0] ^ tmp;
    x[3] ^= x[1] ^ tmp;
}


void L_4(uint16_t * x)
{
    uint16_t tmp = x[0] ^ x[1] ^ x[2] ^ x[3];
    tmp = ROTL(tmp, 8);

    x[4] ^= x[2] ^ tmp;
    x[5] ^= x[1] ^ tmp;
    x[6] ^= x[0] ^ tmp;
    x[7] ^= x[3] ^ tmp;

    SWAP(x[0], x[4]);
    SWAP(x[1], x[5]);
    SWAP(x[2], x[6]);
    SWAP(x[3], x[7]);
}

void L_4_inv(uint16_t * x)
{
    uint16_t tmp;
    SWAP(x[0], x[4]);
    SWAP(x[1], x[5]);
    SWAP(x[2], x[6]);
    SWAP(x[3], x[7]);

    tmp = x[0] ^ x[1] ^ x[2] ^ x[3];
    tmp = ROTL(tmp, 8);
    x[4] ^= x[2] ^ tmp;
    x[5] ^= x[1] ^ tmp;
    x[6] ^= x[0] ^ tmp;
    x[7] ^= x[3] ^ tmp;
}


/* Key schedule  */
/* ============= */

/* The permutation of the key state */
void K_perm_64_128(uint16_t * k, uint16_t c)
{
    uint16_t tmp_0, tmp_1, i;
    /* Misty-like transformation */
    A(k+0, k+1);
    k[2] += k[0];
    k[3] += k[1];
    k[7] += c;
    /* Branch rotation */
    tmp_0 = k[6];
    tmp_1 = k[7];
    for (i=7 ; i>=2 ; i--)
    {
        k[i] = k[i-2];
    }
    k[0] = tmp_0;
    k[1] = tmp_1;
}

/* The permutation of the key state */
void K_perm_128_128(uint16_t * k, uint16_t c)
{
    uint16_t tmp_0, tmp_1, i;
    /* Misty-like transformation */
    A(k+0, k+1);
    k[2] += k[0];
    k[3] += k[1];
    A(k+4, k+5);
    k[6] += k[4];
    k[7] += k[5] + c;
    /* Branch rotation */
    tmp_0 = k[6];
    tmp_1 = k[7];
    for (i=7 ; i>=2 ; i--)
    {
        k[i] = k[i-2];
    }
    k[0] = tmp_0;
    k[1] = tmp_1;
}

/* The permutation of the key state */
void K_perm_128_256(uint16_t * k, uint16_t c)
{
    uint16_t tmp[6], i;
    /* Misty-like transformation */
    A(k+0, k+1);
    k[2] += k[0];
    k[3] += k[1];
    A(k+8, k+9);
    k[10] += k[8];
    k[11] += k[9] + c;
    /* Branch rotation */
    for (i=0 ; i<6 ; i++)
    {
        tmp[i] = k[10+i];
    }
    for (i=15 ; i>=6 ; i--)
    {
        k[i] = k[i-6];
    }
    for (i=0 ; i<6 ; i++)
    {
        k[i] = tmp[i];
    }
}


/* Takes a 128 bit master key and turns it into 2*(N_STEPS+1) subkeys
 * of 96 bits */
void sparx_key_schedule(uint16_t subkeys[][2*ROUNDS_PER_STEPS], uint16_t * master_key)
{
    uint8_t c, i;
    for (c=0 ; c<(N_BRANCHES*N_STEPS+1) ; c++)
    {
        for (i=0 ; i<2*ROUNDS_PER_STEPS ; i++)
        {
            subkeys[c][i] = master_key[i];
        }
        K_perm(master_key, c+1);
    }
}


/* Encryption and decryption */
/* ========================= */

#ifdef LIBSCARV_CONF_SPARX_EXTERN

void sparx_encrypt(uint16_t * x, uint16_t k[][2*ROUNDS_PER_STEPS]) {
    sparx_encrypt_64_128(x,k);
}

#else 

void sparx_encrypt(uint16_t * x, uint16_t k[][2*ROUNDS_PER_STEPS])
{
    uint8_t s, r, b;

    s=0; b=0; r=0;
    for (s=0 ; s<N_STEPS ; s++)
    {
        for (b=0 ; b<N_BRANCHES ; b++)
        {
            uint16_t * koff = &k[N_BRANCHES*s+b][0];
            
            uint16_t   twob = x[2*b  ];
            uint16_t   twob1= x[2*b+1];

            for (r=0 ; r<ROUNDS_PER_STEPS ; r++)
            {
                twob  ^= koff[2*r    ];
                twob1 ^= koff[2*r + 1];

                twob   = ROTL(twob ,9);
                twob  +=      twob1   ;
                
                twob1  = ROTL(twob1,2);
                twob1 ^=      twob    ;
            }

            x[2*b  ] = twob ;
            x[2*b+1] = twob1;
        }

        uint16_t tmp = ROTL((x[0] ^ x[1]), 8);

        x[2] ^= x[0] ^ tmp;
        x[3] ^= x[1] ^ tmp;
        SWAP(x[0], x[2]);
        SWAP(x[1], x[3]);

    }

    for (b=0 ; b<N_BRANCHES ; b++)
    {
        x[2*b  ] ^= k[N_BRANCHES*N_STEPS][2*b  ];
        x[2*b+1] ^= k[N_BRANCHES*N_STEPS][2*b+1];
    }
}

#endif


void sparx_decrypt(uint16_t * x, uint16_t k[][2*ROUNDS_PER_STEPS])
{
    int8_t s, r, b;

    for (b=0 ; b<N_BRANCHES ; b++)
    {
        x[2*b  ] ^= k[N_BRANCHES*N_STEPS][2*b  ];
        x[2*b+1] ^= k[N_BRANCHES*N_STEPS][2*b+1];
    }
    for (s=N_STEPS-1 ; s >= 0 ; s--)
    {
        L_inv(x);
        for (b=0 ; b<N_BRANCHES ; b++)
            for (r=ROUNDS_PER_STEPS-1 ; r >= 0 ; r--)
            {
                A_inv(x + 2*b, x + 2*b+1);
                x[2*b  ] ^= k[N_BRANCHES*s + b][2*r    ];
                x[2*b+1] ^= k[N_BRANCHES*s + b][2*r + 1];
            }
    }
}


