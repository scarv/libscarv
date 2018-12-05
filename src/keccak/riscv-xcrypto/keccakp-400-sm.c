
#include "KeccakP-400-SnP.h"

/*
void KeccakP400_theta(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane C[5], D[5];

    for(x=0; x<5; x++) {
        C[x] = 0;
        for(y=0; y<5; y++)
            C[x] ^= A[index(x, y)];
    }
    for(x=0; x<5; x++)
        D[x] = ROL16(C[(x+1)%5], 1) ^ C[(x+4)%5];
    for(x=0; x<5; x++)
        for(y=0; y<5; y++)
            A[index(x, y)] ^= D[x];
}
*/

/*
void KeccakP400_rho(tKeccakLane *A)
{
    unsigned int x, y;

    for(x=0; x<5; x++) {
        for(y=0; y<5; y++) {
            A[index(x, y)] =
                ROL16(A[index(x, y)], KeccakP400RhoOffsets[index(x, y)]);
        }
    }
}
*/

/*
void KeccakP400_pi(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane tempA[25];

    for(x=0; x<5; x++) for(y=0; y<5; y++)
        tempA[index(x, y)] = A[index(x, y)];
    for(x=0; x<5; x++) for(y=0; y<5; y++)
        A[index(0*x+1*y, 2*x+3*y)] = tempA[index(x, y)];
}
*/

/*
void KeccakP400_chi(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane C[5];

    for(y=0; y<5; y++) {
        for(x=0; x<5; x++)
            C[x] = A[index(x, y)] ^ ((~A[index(x+1, y)]) & A[index(x+2, y)]);
        for(x=0; x<5; x++)
            A[index(x, y)] = C[x];
    }
}
*/

void KeccakP400_iota(tKeccakLane *A, unsigned int indexRound)
{
    A[index(0, 0)] ^= KeccakP400RoundConstants[indexRound];
}
