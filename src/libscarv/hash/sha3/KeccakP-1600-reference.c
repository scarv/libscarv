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

This file implements Keccak-p[1600] in a SnP-compatible way.
Please refer to SnP-documentation.h for more details.

This implementation comes with KeccakP-1600-SnP.h in the same folder.
Please refer to LowLevel.build for the exact list of other files it must be combined with.
*/

#include <scarv/hash/sha3/KeccakP-1600-SnP.h>

#ifndef assert
    #define assert(EXPR)
    //#define assert(EXPR) {if(!(EXPR)) {abort()};}
#endif

//
// We care about RISC-V, so little endian it is.
#define IS_LITTLE_ENDIAN    1234
#define PLATFORM_BYTE_ORDER IS_LITTLE_ENDIAN


/* ---------------------------------------------------------------- */

void KeccakP1600_Initialize(void *state)
{
    memset(state, 0, 1600/8);
}

/* ---------------------------------------------------------------- */

void KeccakP1600_AddByte(void *state, unsigned char byte, unsigned int offset)
{
    assert(offset < 200);
    ((unsigned char *)state)[offset] ^= byte;
}

/* ---------------------------------------------------------------- */

void KeccakP1600_AddBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 200);
    assert(offset+length <= 200);
    for(i=0; i<length; i++)
        ((unsigned char *)state)[offset+i] ^= data[i];
}

/* ---------------------------------------------------------------- */

void KeccakP1600_OverwriteBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 200);
    assert(offset+length <= 200);
    memcpy((unsigned char*)state+offset, data, length);
}

/* ---------------------------------------------------------------- */

void KeccakP1600_OverwriteWithZeroes(void *state, unsigned int byteCount)
{
    assert(byteCount <= 200);
    memset(state, 0, byteCount);
}

/* ---------------------------------------------------------------- */

static void fromBytesToWords(tKeccak1600Lane *stateAsWords, const unsigned char *state);
static void fromWordsToBytes(unsigned char *state, const tKeccak1600Lane *stateAsWords);
void KeccakP1600OnWords(tKeccak1600Lane *state, unsigned int nrRounds);
void KeccakP1600Round(tKeccak1600Lane *state, unsigned int indexRound);
void KeccakP1600_Permute_Nrounds(void *state, unsigned int nrounds)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccak1600Lane stateAsWords[1600/64];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, 1600);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP1600OnWords((tKeccak1600Lane*)state, nrounds);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP1600OnWords(stateAsWords, nrounds);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, 1600);
#endif
}

void KeccakP1600_Permute_12rounds(void *state)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccak1600Lane stateAsWords[1600/64];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, 1600);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP1600OnWords((tKeccak1600Lane*)state, 12);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP1600OnWords(stateAsWords, 12);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, 1600);
#endif
}

void KeccakP1600_Permute_24rounds(void *state)
{
#if (PLATFORM_BYTE_ORDER != IS_LITTLE_ENDIAN)
    tKeccak1600Lane stateAsWords[1600/64];
#endif

#ifdef KeccakReference
    displayStateAsBytes(1, "Input of permutation", (const unsigned char *)state, 1600);
#endif
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    KeccakP1600OnWords((tKeccak1600Lane*)state, 24);
#else
    fromBytesToWords(stateAsWords, (const unsigned char *)state);
    KeccakP1600OnWords(stateAsWords, 24);
    fromWordsToBytes((unsigned char *)state, stateAsWords);
#endif
#ifdef KeccakReference
    displayStateAsBytes(1, "State after permutation", (const unsigned char *)state, 1600);
#endif
}

static void fromBytesToWords(tKeccak1600Lane *stateAsWords, const unsigned char *state)
{
    unsigned int i, j;

    for(i=0; i<nrLanes1600; i++) {
        stateAsWords[i] = 0;
        for(j=0; j<(64/8); j++)
            stateAsWords[i] |= (tKeccak1600Lane)(state[i*(64/8)+j]) << (8*j);
    }
}

static void fromWordsToBytes(unsigned char *state, const tKeccak1600Lane *stateAsWords)
{
    unsigned int i, j;

    for(i=0; i<nrLanes1600; i++)
        for(j=0; j<(64/8); j++)
            state[i*(64/8)+j] = (unsigned char)((stateAsWords[i] >> (8*j)) & 0xFF);
}

void KeccakP1600OnWords(tKeccak1600Lane *state, unsigned int nrRounds)
{
    unsigned int i;

#ifdef KeccakReference
    displayStateAsLanes(3, "Same, with lanes as 64-bit words", state, 1600);
#endif

    for(i=(maxNrRounds1600-nrRounds); i<maxNrRounds1600; i++)
        KeccakP1600Round(state, i);
}


/*!
@brief A reference implementation used to test the accelerated
KeccakP1600Round function.
*/
void KeccakP1600RoundReference(tKeccak1600Lane *A, unsigned int indexRound)
{
    unsigned int x, y;
    tKeccak1600Lane C[5];
    tKeccak1600Lane tempA[25];
    tKeccak1600Lane D;

    // Theta / Rho / Pi

    for(x=0; x<5; x++) {
        C[x] = A[index(x, 0)] ^
               A[index(x, 1)] ^
               A[index(x, 2)] ^
               A[index(x, 3)] ^
               A[index(x, 4)] ;
    }

    for(x=0; x<5; x++) {
        
        D = ROL64(C[(x+1)%5], 1) ^ C[(x+4)%5];

        for(y=0; y<5; y++) {

            tempA[index(0*x+1*y, 2*x+3*y)] = 
                ROL64 (
                    A[index(x, y)] ^ D,
                    KeccakP1600RhoOffsets[index(x, y)]
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
    A[index(0, 0)] ^= KeccakP1600RoundConstants[indexRound];
}

#if ( LIBSCARV_CONF_KECCAK_P1600_ROUND_EXTERN )
extern void KeccakP1600Round(tKeccak1600Lane *state, unsigned int indexRound);
#else
void KeccakP1600Round(tKeccak1600Lane *state, unsigned int indexRound)
{
    KeccakP1600RoundReference(state,indexRound);
}
#endif

/* ---------------------------------------------------------------- */

void KeccakP1600_ExtractBytes(const void *state, unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 200);
    assert(offset+length <= 200);
    memcpy(data, (unsigned char*)state+offset, length);
}

/* ---------------------------------------------------------------- */

void KeccakP1600_ExtractAndAddBytes(const void *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 200);
    assert(offset+length <= 200);
    for(i=0; i<length; i++)
        output[i] = input[i] ^ ((unsigned char *)state)[offset+i];
}

