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

#ifndef _KeccakP_400_SnP_h_
#define _KeccakP_400_SnP_h_

#define KeccakP400_implementation      "16-bit reference implementation"
#define KeccakP400_stateSizeInBytes    50
#define KeccakP400_stateAlignment      2

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef UINT16 tKeccak400Lane;

#define maxNrRounds 20
#define nrLanes 25
#define index(x, y) (((x)%5)+5*((y)%5))

#define ROL16(a, offset) ((offset != 0) ? \
    ((((tKeccak400Lane)a) << offset) ^ \
     (((tKeccak400Lane)a) >> (sizeof(tKeccak400Lane)*8-offset))) : a)


static const unsigned int KeccakP400RhoOffsets[nrLanes] =
{
     0,  1, 14, 12, 11,  4, 12,  6,  7,  4,  3, 10, 11,  9,  7,  9, 13, 15,
     5,  8,  2,  2, 13,  8, 14
};

static const tKeccak400Lane KeccakP400RoundConstants[maxNrRounds] =
{
    0x0001, 0x8082, 0x808a, 0x8000, 0x808b, 0x0001, 0x8081, 0x8009, 0x008a,
    0x0088, 0x8009, 0x000a, 0x808b, 0x008b, 0x8089, 0x8003, 0x8002, 0x0080,
    0x800a, 0x000a,
};


void KeccakP400_Initialize(void *state);
void KeccakP400_AddByte(void *state, unsigned char data, unsigned int offset);
void KeccakP400_AddBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP400_OverwriteBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP400_OverwriteWithZeroes(void *state, unsigned int byteCount);
void KeccakP400_Permute_Nrounds(void *state, unsigned int nrounds);
void KeccakP400_Permute_20rounds(void *state);
void KeccakP400RoundReference(tKeccak400Lane *state, unsigned int indexRound);
void KeccakP400Round(tKeccak400Lane *state, unsigned int indexRound);
void KeccakP400_ExtractBytes(const void *state, unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP400_ExtractAndAddBytes(const void *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length);

#endif
