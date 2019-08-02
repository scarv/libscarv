
#include <scarv/hash/keccakp400/KeccakP-400-SnP.h>
#include <scarv/share/xcrypto_intrinsics.h>

/*!
@brief Accelerated version of the Keccak400P round function using XCrypto.
*/
void KeccakP400Round(tKeccak400Lane *A, unsigned int indexRound)
{
    unsigned int x, y;
    uint16_t C[5];
    uint16_t tempA[25];
    uint16_t D;

    // Theta / Rho / Pi

    for(x=0; x<5; x++) {
        tKeccak400Lane t = 0;
        t ^= A[index(x, 0)];
        t ^= A[index(x, 1)];
        t ^= A[index(x, 2)];
        t ^= A[index(x, 3)];
        t ^= A[index(x, 4)];
        C[x] = t;
    }

    for(x=0; x<5; x++) {

        int      x1 = _xc_sha3_x1(x, 0, 0);
        int      x4 = _xc_sha3_x4(x, 0, 0);

        uint16_t l1 = _xc_ldr_hu(C,x1);
        uint16_t l2 = _xc_ldr_hu(C,x4);
        
        D = _xc_pror_h(l1, 16-1) ^ l2;

        for(y=0; y<5; y++) {
        
            int     xy = _xc_sha3_xy(x, y, 0);
            int     yx = _xc_sha3_yx(x, y, 0);

            int16_t ts = _xc_pror_h(
                _xc_ldr_hu(A,xy) ^ D,
                _xc_ldr_hu(KeccakP400RhoOffsets,xy)
            );

            _xc_str_h(tempA,yx, ts);
        }
    }

    // Chi

    for(y=0; y<5; y++) {
        for(x=0; x<5; x++) {
            
            int      xy      = _xc_sha3_xy(x, y, 0);
            int      x1      = _xc_sha3_x1(x, y, 0);
            int      x2      = _xc_sha3_x2(x, y, 0);

            int16_t tempA_xy = _xc_ldr_hu(tempA,xy);
            int16_t tempA_x1 = _xc_ldr_hu(tempA,x1);
            int16_t tempA_x2 = _xc_ldr_hu(tempA,x2);

            int16_t ts       = tempA_xy ^ ((~tempA_x1) & tempA_x2);

            _xc_str_h(A,xy,ts);
        }
    }

    // Iota
    A[0] ^= KeccakP400RoundConstants[indexRound];
}
