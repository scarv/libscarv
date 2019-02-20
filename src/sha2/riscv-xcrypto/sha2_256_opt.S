
.data

.extern W   // 512 bit scratch array uint32_t[64]
.extern K   // Round constants       uint32_t[64]
.extern H   // Current hash digest   uint32_t[8]

//
// Convert array X to Big endian byte representation, and copy it to W.
//
//  T0 - Temp register 
//  W  - Register with base address of W (word aligned)
//  X  - Register with base address of X (word aligned)
//  O  - Offset into W/X - Multiple of 4.
//
.macro SHA2_U8_TO_U32_BE T0, W, X, O
    xc.ld.w     \T0, \O(\X)
    xc.pperm.w  \T0, \T0, 3,2,1,0
    xc.st.w     \T0, \O(\W)
.endm

//
// Perform S0 transformation
//
// R  - Result register address R != T0, R != T1
// T0 - Temp register address   T0 != T1
// T1 - Temp register address
// A  - Source register address A != {T0,T1}
//
.macro SHA2_S0 R, T0, T1, A
    xc.prot.i   w, \T0, \A, 7 
    xc.prot.i   w, \T1, \A, 18
    xc.psrl.i   w, \R , \A, 3
    xc.bop      \R , \T0, \T1, 0b10010110   // R = R ^ T0 ^ T1
.endm

//
// Perform S1 transformation
//
// R  - Result register address R != T0, R != T1
// T0 - Temp register address   T0 != T1
// T1 - Temp register address
// A  - Source register address A != {T0,T1}
//
.macro SHA2_S1 R, T0, T1, A
    xc.prot.i   w, \T0, \A, 17
    xc.prot.i   w, \T1, \A, 19
    xc.psrl.i   w, \R , \A, 10
    xc.bop      \R , \T0, \T1, 0b10010110   // R = R ^ T0 ^ T1
.endm

//
// Perform S2 transformation
//
// R  - Result register address R != T0, R != T1
// T0 - Temp register address   T0 != T1
// T1 - Temp register address
// A  - Source register address A != {T0,T1}
//
.macro SHA2_S2 R, T0, T1, A
    xc.prot.i   w, \T0, \A, 2 
    xc.prot.i   w, \T1, \A, 13
    xc.prot.i   w, \R , \A, 22
    xc.bop      \R , \T0, \T1, 0b10010110   // R = R ^ T0 ^ T1
.endm

//
// Perform S3 transformation
//
// R  - Result register address R != T0, R != T1
// T0 - Temp register address   T0 != T1
// T1 - Temp register address
// A  - Source register address A != {T0,T1}
//
.macro SHA2_S3 R, T0, T1, A
    xc.prot.i   w, \T0, \A, 11
    xc.prot.i   w, \T1, \A, 25
    xc.prot.i   w, \R , \A, 6
    xc.bop      \R , \T0, \T1, 0b10010110   // R = R ^ T0 ^ T1
.endm


//
// Compute the F0 transformation
//
// R - Destination register address R != {A,B,C}
// A - Source reg A != {B,C}
// B - Source reg B != {C}
// C - Source reg C
// T - Temp reg   T != {A,B,C,R}
//
.macro SHA2_F0 R, A, B, C, T
    xc.bop  \R, \A, \A, 0b10101010 # R = A
    xc.bop  \R, \B, \C, 0b11101000 # R = (A&B) | ((A|B) & C)
.endm


//
// Compute the F1 transformation
//
// R - Destination register address R != {A,B,C}
// A - Source reg A != {B,C}
// B - Source reg B != {C}
// C - Source reg C
//
.macro SHA2_F1  R, A, B, C
    xc.bop   \R, \B, \C, 0b01100110             # R = B ^ C
    xc.bop   \R, \A, \C, 0b01101010             # R = C ^ (A & R)
.endm


//
// Compute the R transformation
//
.macro SHA2_R A,B,C,D,E,F,G,H,W,K,T0,T1,T2,T3
    SHA2_S3     \T0, \T1, \T2, \E        # T0 = S3(E)
    SHA2_F1     \T1, \E , \F , \G        # T1 = F1(E,F,G)
    xc.padd     w  , \T0, \T0, \T1       # T0 = S3(E) + F1(E,F,G)
    xc.padd     w  , \T0, \T0, \H        # T0 = S3 + F1 + H
    xc.padd     w  , \T0, \T0, \W        # T0 = S3 + F1 + H + W
    xc.padd     w  , \T0, \T0, \K        # T0 = S3 + F1 + H + K
    SHA2_S2     \T1, \T2, \T3, \A        # T1 = S2(A)
    SHA2_F0     \T2, \A , \B , \C , \T3  # T2 = F0(A,B,C)
    xc.padd     w  , \T1, \T1, \T2       # T1 = S2(A) + F0(A,B,C)
    xc.padd     w  , \D , \D , \T0       # D += T0
    xc.padd     w  , \H , \T1, \T0       # H  = T1 + T0
.endm


.text
.global sha2_256_comp
.func sha2_256_comp
sha2_256_comp:
    // a0 = x = 32-byte array to hash.
    
    la      a1, W       // Scratch array base
    la      a2, K       // Round constant addresses
    la      a3, H       // Hash value array addresses

    xc.ld.w c0,  0(a3)  // c0 = a = H[0]
    xc.ld.w c1,  4(a3)  // c1 = b = H[1]
    xc.ld.w c2,  8(a3)  // c2 = c = H[2]
    xc.ld.w c3, 12(a3)  // c3 = d = H[3]
    xc.ld.w c4, 16(a3)  // c4 = e = H[4]
    xc.ld.w c5, 20(a3)  // c5 = f = H[5]
    xc.ld.w c6, 24(a3)  // c6 = g = H[6]
    xc.ld.w c7, 28(a3)  // c7 = h = H[7]

    SHA2_U8_TO_U32_BE   c15, a1, a0,  0
    SHA2_U8_TO_U32_BE   c15, a1, a0,  4
    SHA2_U8_TO_U32_BE   c15, a1, a0,  8
    SHA2_U8_TO_U32_BE   c15, a1, a0, 12
    SHA2_U8_TO_U32_BE   c15, a1, a0, 16
    SHA2_U8_TO_U32_BE   c15, a1, a0, 20
    SHA2_U8_TO_U32_BE   c15, a1, a0, 24
    SHA2_U8_TO_U32_BE   c15, a1, a0, 28
    SHA2_U8_TO_U32_BE   c15, a1, a0, 32
    SHA2_U8_TO_U32_BE   c15, a1, a0, 36
    SHA2_U8_TO_U32_BE   c15, a1, a0, 40
    SHA2_U8_TO_U32_BE   c15, a1, a0, 44
    SHA2_U8_TO_U32_BE   c15, a1, a0, 48
    SHA2_U8_TO_U32_BE   c15, a1, a0, 52
    SHA2_U8_TO_U32_BE   c15, a1, a0, 56
    SHA2_U8_TO_U32_BE   c15, a1, a0, 60

    addi t0, a1, 64     // t0 = &W[16]
    addi t1, a1, 256    // t1 = &W[64]

    .L0:
        
        xc.ld.w  c8 ,  -8(t0)       // c8  = W[i- 2]
        xc.ld.w  c9 , -28(t0)       // c9  = W[i- 7]
        xc.ld.w  c10, -60(t0)       // c10 = W[i-15]
        xc.ld.w  c11, -64(t0)       // c11 = W[i-16]

        SHA2_S0 c10, c12, c13, c10  // c10 = S0(c10)
        SHA2_S1 c8 , c12, c13, c8   // c8  = S1(c8 )

        xc.padd w, c8, c8, c9       // c8   = S1(W[i- 2]) + W[i- 7] +
        xc.padd w, c8, c8, c10      //        S0(W[i-15]) + W[i-16]
        xc.padd w, c8, c8, c11      //

        xc.st.w c8, 0(t0)           // W[i] = c8

        addi t0, t0, 4
        bltu t0, t1, .L0

    
    addi t0, a1, 0      // t0 = &W[0]
    addi t1, a2, 0      // t1 = &K[0]
    addi t2, a1, 256    // t2 = &W[64]

    .L1:
        
        xc.ld.w c8,  0(t0)  // c8 = W[i + 0]
        xc.ld.w c9,  0(t1)  // c9 = K[i + 0]

        //     a ,b ,c ,d ,e ,f ,g ,h ,W ,K ,Temps...
        SHA2_R c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13

        xc.ld.w c8,  4(t0)  // c8 = W[i + 1]
        xc.ld.w c9,  4(t1)  // c9 = K[i + 1]
        SHA2_R c7,c0,c1,c2,c3,c4,c5,c6,c8,c9,c10,c11,c12,c13

        xc.ld.w c8,  8(t0)  // c8 = W[i + 2]
        xc.ld.w c9,  8(t1)  // c9 = K[i + 2]
        SHA2_R c6,c7,c0,c1,c2,c3,c4,c5,c8,c9,c10,c11,c12,c13

        xc.ld.w c8, 12(t0)  // c8 = W[i + 3]
        xc.ld.w c9, 12(t1)  // c9 = K[i + 3]
        SHA2_R c5,c6,c7,c0,c1,c2,c3,c4,c8,c9,c10,c11,c12,c13

        xc.ld.w c8, 16(t0)  // c8 = W[i + 4]
        xc.ld.w c9, 16(t1)  // c9 = K[i + 4]
        SHA2_R c4,c5,c6,c7,c0,c1,c2,c3,c8,c9,c10,c11,c12,c13

        xc.ld.w c8, 20(t0)  // c8 = W[i + 5]
        xc.ld.w c9, 20(t1)  // c9 = K[i + 5]
        SHA2_R c3,c4,c5,c6,c7,c0,c1,c2,c8,c9,c10,c11,c12,c13

        xc.ld.w c8, 24(t0)  // c8 = W[i + 6]
        xc.ld.w c9, 24(t1)  // c9 = K[i + 6]
        SHA2_R c2,c3,c4,c5,c6,c7,c0,c1,c8,c9,c10,c11,c12,c13

        xc.ld.w c8, 28(t0)  // c8 = W[i + 7]
        xc.ld.w c9, 28(t1)  // c9 = K[i + 7]
        SHA2_R c1,c2,c3,c4,c5,c6,c7,c0,c8,c9,c10,c11,c12,c13

        addi t0, t0, 32
        addi t1, t1, 32
        bltu t0, t2, .L1


    xc.ld.w c8 ,  0(a3)      // c8  = H[0]
    xc.ld.w c9 ,  4(a3)      // c9  = H[1]
    xc.ld.w c10,  8(a3)      // c10 = H[2]
    xc.ld.w c11, 12(a3)      // c11 = H[3]
    xc.ld.w c12, 16(a3)      // c12 = H[4]
    xc.ld.w c13, 20(a3)      // c13 = H[5]
    xc.ld.w c14, 24(a3)      // c14 = H[6]
    xc.ld.w c15, 28(a3)      // c15 = H[7]

    xc.padd w, c8 , c8 , c0
    xc.padd w, c9 , c9 , c1
    xc.padd w, c10, c10, c2
    xc.padd w, c11, c11, c3
    xc.padd w, c12, c12, c4
    xc.padd w, c13, c13, c5
    xc.padd w, c14, c14, c6
    xc.padd w, c15, c15, c7
    
    xc.st.w c8 ,  0(a3)      // H[0] += c8 
    xc.st.w c9 ,  4(a3)      // H[1] += c9 
    xc.st.w c10,  8(a3)      // H[2] += c10
    xc.st.w c11, 12(a3)      // H[3] += c11
    xc.st.w c12, 16(a3)      // H[4] += c12
    xc.st.w c13, 20(a3)      // H[5] += c13
    xc.st.w c14, 24(a3)      // H[6] += c14
    xc.st.w c15, 28(a3)      // H[7] += c15

    ret

.endfunc

