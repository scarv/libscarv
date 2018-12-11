/*
Implementation by the Keccak Team, namely, Guido Bertoni, Joan Daemen,
Michaël Peeters, Gilles Van Assche and Ronny Van Keer,
hereby denoted as "the implementer".

For more information, feedback or questions, please refer to our website:
https://keccak.team/

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/

---

This file implements Keccak-p[400] in a SnP-compatible way.
Please refer to SnP-documentation.h for more details.

This implementation comes with KeccakP-400-SnP.h in the same folder.
Please refer to LowLevel.build for the exact list of other files it must be combined with.
*/

#include "KeccakP-400-SnP.h"

#ifndef assert
    #define assert(EXPR)
    //#define assert(EXPR) {if(!(EXPR)) {abort()};}
#endif

//
// We care about RISC-V, so little endian it is.
#define IS_LITTLE_ENDIAN    1234
#define PLATFORM_BYTE_ORDER IS_LITTLE_ENDIAN

/* ---------------------------------------------------------------- */

void KeccakP400_Initialize(void *state)
{
    memset(state, 0, nrLanes * sizeof(tKeccak400Lane));
}

/* ---------------------------------------------------------------- */

void KeccakP400_AddByte(void *state, unsigned char byte, unsigned int offset)
{
    assert(offset < 50);
    ((unsigned char *)state)[offset] ^= byte;
}

/* ---------------------------------------------------------------- */

void KeccakP400_AddBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 50);
    assert(offset+length <= 50);
    for(i=0; i<length; i++)
        ((unsigned char *)state)[offset+i] ^= data[i];
}

/* ---------------------------------------------------------------- */

void KeccakP400_OverwriteBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 50);
    assert(offset+length <= 50);
    memcpy((unsigned char*)state+offset, data, length);
}

/* ---------------------------------------------------------------- */

void KeccakP400_OverwriteWithZeroes(void *state, unsigned int byteCount)
{
    assert(byteCount <= 50);
    memset(state, 0, byteCount);
}

/* ---------------------------------------------------------------- */

static void fromBytesToWords(tKeccak400Lane *stateAsWords, const unsigned char *state);
static void fromWordsToBytes(unsigned char *state, const tKeccak400Lane *stateAsWords);
void KeccakP400OnWords(tKeccak400Lane *state, unsigned int nrRounds);
void KeccakP400Round(tKeccak400Lane *state, unsigned int indexRound);

//
// External round function definitions.
//  Definitions found in <arch>/keccakp-400-sm.c
//
extern void KeccakP400_theta(tKeccak400Lane *A);
extern void KeccakP400_rho(tKeccak400Lane *A);
extern void KeccakP400_pi(tKeccak400Lane *A);
extern void KeccakP400_chi(tKeccak400Lane *A);
extern void KeccakP400_iota(tKeccak400Lane *A, unsigned int indexRound);

void KeccakP400_Permute_Nrounds(void *state, unsigned int nrounds)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccak400Lane stateAsWords[nrLanes];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccak400Lane) * 8);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP400OnWords((tKeccak400Lane*)state, nrounds);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP400OnWords(stateAsWords, nrounds);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccak400Lane) * 8);
#endif
}

void KeccakP400_Permute_20rounds(void *state)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccak400Lane stateAsWords[nrLanes];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccak400Lane) * 8);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP400OnWords((tKeccak400Lane*)state, maxNrRounds);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP400OnWords(stateAsWords, maxNrRounds);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccak400Lane) * 8);
#endif
}

static void fromBytesToWords(tKeccak400Lane *stateAsWords, const unsigned char *state)
{
    unsigned int i, j;

    for(i=0; i<nrLanes; i++) {
        stateAsWords[i] = 0;
        for(j=0; j<sizeof(tKeccak400Lane); j++)
            stateAsWords[i] |= (tKeccak400Lane)(state[i*sizeof(tKeccak400Lane)+j]) << (8*j);
    }
}

static void fromWordsToBytes(unsigned char *state, const tKeccak400Lane *stateAsWords)
{
    unsigned int i, j;

    for(i=0; i<nrLanes; i++)
        for(j=0; j<sizeof(tKeccak400Lane); j++)
            state[i*sizeof(tKeccak400Lane)+j] = (stateAsWords[i] >> (8*j)) & 0xFF;
}

void KeccakP400OnWords(tKeccak400Lane *state, unsigned int nrRounds)
{
    unsigned int i;

#ifdef KeccakReference
    displayStateAsLanes(3, "Same, with lanes as 16-bit words", state, 400);
#endif

    for(i=(maxNrRounds-nrRounds); i<maxNrRounds; i++)
        KeccakP400Round(state, i);
}

/*!
@brief A reference implementation used to test the accelerated KeccakP400Round
function.
*/
void KeccakP400RoundReference(tKeccak400Lane *A, unsigned int indexRound)
{
    unsigned int x, y;
    tKeccak400Lane C[5];
    tKeccak400Lane tempA[25];
    tKeccak400Lane D;

    // Theta / Rho / Pi

    for(x=0; x<5; x++) {
        C[x] = A[index(x, 0)] ^
               A[index(x, 1)] ^
               A[index(x, 2)] ^
               A[index(x, 3)] ^
               A[index(x, 4)] ;
    }

    for(x=0; x<5; x++) {
        
        D = ROL16(C[(x+1)%5], 1) ^ C[(x+4)%5];

        for(y=0; y<5; y++) {

            tempA[index(0*x+1*y, 2*x+3*y)] = 
                ROL16 (
                    A[index(x, y)] ^ D,
                    KeccakP400RhoOffsets[index(x, y)]
                );
        }
    }

    // Chi

    for(y=0; y<5; y++) {
        for(x=0; x<5; x++) {
            A[index(x, y)] =
                tempA[index(x, y)] ^ 
                    ((~tempA[index(x+1, y)]) &
                       tempA[index(x+2, y)]);
        }
    }

    // Iota
    A[index(0, 0)] ^= KeccakP400RoundConstants[indexRound];
}

#ifndef CONF_KECCAKP400_ROUND_EXTERN
void KeccakP400Round(tKeccak400Lane *state, unsigned int indexRound)
{
    KeccakP400RoundReference(state,indexRound);
}
#endif

/* ---------------------------------------------------------------- */

//
// All round functions are externally defined under:
//  <arch>/keccakp-400-sm.[c|S]
//
//

/* ---------------------------------------------------------------- */

void KeccakP400_ExtractBytes(const void *state, unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 50);
    assert(offset+length <= 50);
    memcpy(data, (unsigned char*)state+offset, length);
}

/* ---------------------------------------------------------------- */

void KeccakP400_ExtractAndAddBytes(const void *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 50);
    assert(offset+length <= 50);
    for(i=0; i<length; i++)
        output[i] = input[i] ^ ((unsigned char *)state)[offset+i];
}

