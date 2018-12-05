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
    memset(state, 0, nrLanes * sizeof(tKeccakLane));
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

static void fromBytesToWords(tKeccakLane *stateAsWords, const unsigned char *state);
static void fromWordsToBytes(unsigned char *state, const tKeccakLane *stateAsWords);
void KeccakP400OnWords(tKeccakLane *state, unsigned int nrRounds);
void KeccakP400Round(tKeccakLane *state, unsigned int indexRound);

//
// External round function definitions.
//  Definitions found in <arch>/keccakp-400-sm.c
//
extern void KeccakP400_theta(tKeccakLane *A);
extern void KeccakP400_rho(tKeccakLane *A);
extern void KeccakP400_pi(tKeccakLane *A);
extern void KeccakP400_chi(tKeccakLane *A);
extern void KeccakP400_iota(tKeccakLane *A, unsigned int indexRound);

void KeccakP400_Permute_Nrounds(void *state, unsigned int nrounds)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccakLane stateAsWords[nrLanes];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccakLane) * 8);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP400OnWords((tKeccakLane*)state, nrounds);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP400OnWords(stateAsWords, nrounds);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccakLane) * 8);
#endif
}

void KeccakP400_Permute_20rounds(void *state)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccakLane stateAsWords[nrLanes];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccakLane) * 8);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP400OnWords((tKeccakLane*)state, maxNrRounds);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP400OnWords(stateAsWords, maxNrRounds);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, nrLanes * sizeof(tKeccakLane) * 8);
#endif
}

static void fromBytesToWords(tKeccakLane *stateAsWords, const unsigned char *state)
{
    unsigned int i, j;

    for(i=0; i<nrLanes; i++) {
        stateAsWords[i] = 0;
        for(j=0; j<sizeof(tKeccakLane); j++)
            stateAsWords[i] |= (tKeccakLane)(state[i*sizeof(tKeccakLane)+j]) << (8*j);
    }
}

static void fromWordsToBytes(unsigned char *state, const tKeccakLane *stateAsWords)
{
    unsigned int i, j;

    for(i=0; i<nrLanes; i++)
        for(j=0; j<sizeof(tKeccakLane); j++)
            state[i*sizeof(tKeccakLane)+j] = (stateAsWords[i] >> (8*j)) & 0xFF;
}

void KeccakP400OnWords(tKeccakLane *state, unsigned int nrRounds)
{
    unsigned int i;

#ifdef KeccakReference
    displayStateAsLanes(3, "Same, with lanes as 16-bit words", state, 400);
#endif

    for(i=(maxNrRounds-nrRounds); i<maxNrRounds; i++)
        KeccakP400Round(state, i);
}

void KeccakP400Round(tKeccakLane *state, unsigned int indexRound)
{
#ifdef KeccakReference
    displayRoundNumber(3, indexRound);
#endif

    KeccakP400_theta(state);
#ifdef KeccakReference
    displayStateAsLanes(3, "After theta", state, 400);
#endif

    KeccakP400_rho(state);
#ifdef KeccakReference
    displayStateAsLanes(3, "After rho", state, 400);
#endif

    KeccakP400_pi(state);
#ifdef KeccakReference
    displayStateAsLanes(3, "After pi", state, 400);
#endif

    KeccakP400_chi(state);
#ifdef KeccakReference
    displayStateAsLanes(3, "After chi", state, 400);
#endif

    KeccakP400_iota(state, indexRound);
#ifdef KeccakReference
    displayStateAsLanes(3, "After iota", state, 400);
#endif
}

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

