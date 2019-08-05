/*
 * SPARX source code package
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

#include "scarv/block/sparx/sparx_128_128.h"

const int sparx_128_128_STEPS    = 8;
const int sparx_128_128_ROUNDS   = 4;
const int sparx_128_128_BRANCHES = 4;

/* Key schedule  */
/* ============= */

/* The permutation of the key state */
static void sparx_K_perm_128_128(uint16_t * k, uint16_t c)
{
    uint16_t tmp_0, tmp_1, i;
    /* Misty-like transformation */
    SPARX_A(k[0], k[1]);
    k[2] += k[0];
    k[3] += k[1];
    SPARX_A(k[4], k[5]);
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


/* Takes a 128 bit master key and turns it into 2*(sparx_128_128_STEPS+1) subkeys
 * of 96 bits */
void sparx_128_128_key_schedule(
    uint16_t subkeys[][2*sparx_128_128_ROUNDS],
    uint16_t * master_key)
{
    uint8_t c, i;
    for (c=0 ; c<(sparx_128_128_BRANCHES*sparx_128_128_STEPS+1) ; c++)
    {
        for (i=0 ; i<2*sparx_128_128_ROUNDS; i++)
        {
            subkeys[c][i] = master_key[i];
        }
        sparx_K_perm_128_128(master_key, c+1);
    }
}


/* Encryption and decryption */
/* ========================= */

void sparx_128_128_encrypt(
    uint16_t * x,
    uint16_t k[][2*sparx_128_128_ROUNDS]
) {
    uint8_t s, r, b;

    s=0; b=0; r=0;
    for (s=0 ; s<sparx_128_128_STEPS ; s++)
    {
        for (b=0 ; b<sparx_128_128_BRANCHES ; b++)
        {
            for (r=0 ; r<sparx_128_128_ROUNDS ; r++)
            {
                x[2*b  ] ^= k[sparx_128_128_BRANCHES*s + b][2*r    ];
                x[2*b+1] ^= k[sparx_128_128_BRANCHES*s + b][2*r + 1];
                SPARX_A(x[2*b], x[2*b+1]);
            }
        }
        sparx_L_4(x);
    }
    for (b=0 ; b<sparx_128_128_BRANCHES ; b++)
    {
        x[2*b  ] ^= k[sparx_128_128_BRANCHES*sparx_128_128_STEPS][2*b  ];
        x[2*b+1] ^= k[sparx_128_128_BRANCHES*sparx_128_128_STEPS][2*b+1];
    }
}


void sparx_128_128_decrypt(uint16_t * x, uint16_t k[][2*sparx_128_128_ROUNDS])
{
    int8_t s, r, b;

    for (b=0 ; b<sparx_128_128_BRANCHES ; b++)
    {
        x[2*b  ] ^= k[sparx_128_128_BRANCHES*sparx_128_128_STEPS][2*b  ];
        x[2*b+1] ^= k[sparx_128_128_BRANCHES*sparx_128_128_STEPS][2*b+1];
    }
    for (s=sparx_128_128_STEPS-1 ; s >= 0 ; s--)
    {
        sparx_L_4_inv(x);
        for (b=0 ; b<sparx_128_128_BRANCHES ; b++)
            for (r=sparx_128_128_ROUNDS-1 ; r >= 0 ; r--)
            {
                SPARX_A_INV(x[2*b], x[2*b+1]);
                x[2*b  ] ^= k[sparx_128_128_BRANCHES*s + b][2*r    ];
                x[2*b+1] ^= k[sparx_128_128_BRANCHES*s + b][2*r + 1];
            }
    }
}
