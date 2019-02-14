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

Please refer to SnP-documentation.h for more details.
*/

#ifndef _KeccakP_1600_SnP_h_
#define _KeccakP_1600_SnP_h_

#define KeccakP1600_implementation      "64-bit reference implementation"
#define KeccakP1600_stateSizeInBytes    200
#define KeccakP1600_stateAlignment      8


typedef unsigned char UINT8;
typedef unsigned long long UINT64;
typedef UINT64 tKeccak1600Lane;

#define maxNrRounds1600 24
#define nrLanes 25
#define index(x, y) (((x)%5)+5*((y)%5))

#define ROL64(a, offset) ((offset != 0) ? \
    ((((tKeccak1600Lane)a) << offset) ^ \
     (((tKeccak1600Lane)a) >> (64-offset))) : a)

static const tKeccak1600Lane KeccakP1600RoundConstants[maxNrRounds1600] =
{
    0x0000000000000001,
    0x0000000000008082,
    0x800000000000808a,
    0x8000000080008000,
    0x000000000000808b,
    0x0000000080000001,
    0x8000000080008081,
    0x8000000000008009,
    0x000000000000008a,
    0x0000000000000088,
    0x0000000080008009,
    0x000000008000000a,
    0x000000008000808b,
    0x800000000000008b,
    0x8000000000008089,
    0x8000000000008003,
    0x8000000000008002,
    0x8000000000000080,
    0x000000000000800a,
    0x800000008000000a,
    0x8000000080008081,
    0x8000000000008080,
    0x0000000080000001,
    0x8000000080008008,
};

static const unsigned int KeccakP1600RhoOffsets[nrLanes] =
{
  0,  // 0   *
  1,  // 1   
 62,  // 2   
 28,  // 3   
 27,  // 4   
 36,  // 5   *
 44,  // 6   
  6,  // 7   
 55,  // 8   
 20,  // 9   
  3,  // 10  *
 10,  // 11  
 43,  // 12  
 25,  // 13  
 39,  // 14  
 41,  // 15  *
 45,  // 16  
 15,  // 17  
 21,  // 18  
  8,  // 19  
 18,  // 20  *
  2,  // 21  
 61,  // 22  
 56,  // 23  
 14   // 24  
};

void KeccakP1600_Initialize(void *state);
void KeccakP1600_AddByte(void *state, unsigned char data, unsigned int offset);
void KeccakP1600_AddBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600_OverwriteBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600_OverwriteWithZeroes(void *state, unsigned int byteCount);
void KeccakP1600_Permute_Nrounds(void *state, unsigned int nrounds);
void KeccakP1600_Permute_12rounds(void *state);
void KeccakP1600_Permute_24rounds(void *state);
void KeccakP1600_ExtractBytes(const void *state, unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600_ExtractAndAddBytes(const void *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length);

#endif
