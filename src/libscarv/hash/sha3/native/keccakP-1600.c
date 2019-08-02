
#include <scarv/hash/sha3/KeccakP-1600-SnP.h>

/*!
@brief A reference implementation used to test the accelerated
KeccakP1600Round function.
*/
void KeccakP1600Round(tKeccak1600Lane *A, unsigned int indexRound)
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
