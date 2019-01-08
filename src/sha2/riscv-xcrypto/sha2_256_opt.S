
.data

.extern W   # 512 bit scratch array
.extern K   # Round constants
.extern H   # Current hash digest

.macro  U8_TO_U32_BE TMP, S_ADDR, D_ADDR I
    xc.ld.w     \TMP, (\I*4)(\S_ADDR)           # Load x[i], i = 0
    xc.pperm.w  \TMP, \TMP, 3, 2, 1, 0          # Big endian re-arrange
    xc.st.w     \TMP, (\I*4)(\D_ADDR)           # Store W[i] i = 0;
.endm

.macro SHA2_256_S0  R, T0, T1
    xc.prot.i w, \T0, \R, 18                    # T0 = R >>> 18
    xc.psrl.i w, \T1, \R, 3                     # T1 = R >>> 3
    xc.prot.i w, \R , \R, 7                     # R  = R >>> 7
    xc.bop   \R, \T0, \T1, 0b10010110           # R = R ^ T0 ^ T1
.endm

.macro SHA2_256_S1  R, T0, T1
    xc.prot.i w, \T0, \R, 17                    # T0 = R >>> 17
    xc.prot.i w, \T1, \R, 19                    # T1 = R >>> 19
    xc.psrl.i w, \R , \R, 10                    # R  = R >>> 10
    xc.bop   \R, \T0, \T1, 0b10010110           # R = R ^ T0 ^ T1
.endm

.macro SHA2_256_S2 T2, R, T0, T1
    xc.prot.i w, \T0, \R, 2                     # T0 = R >>> 2 
    xc.prot.i w, \T1, \R, 13                    # T1 = R >>> 13
    xc.prot.i w, \T2, \R, 22                    # T2 = R >>> 22
    xc.bop   \T2,\T0, \T1, 0b10010110           # T2 = T2 ^ T0 ^ T1
.endm

.macro SHA2_256_S3 T2, R, T0, T1
    xc.prot.i w, \T0, \R, 6                     # T0 = R >>> 6 
    xc.prot.i w, \T1, \R, 11                    # T1 = R >>> 11
    xc.prot.i w, \T2, \R, 25                    # T2 = R >>> 25
    xc.bop   \T2, \T0, \T1, 0b10010110          # T2 = T2 ^ T0 ^ T1
.endm

.macro SHA2_256_F0 R, A, B, C, T 
    xc.bop   \R, \A, \B, 0b11101110             # R = A | B
    xc.bop   \T, \A, \B, 0b10001000             # T = A & B
    xc.bop   \R, \T, \C, 0b11101100             # R = T | (R & C)
.endm

.macro SHA2_256_F1  R, A, B, C    
    xc.bop   \R, \B, \C, 0b01100110             # R = B ^ C
    xc.bop   \R, \A, \C, 0b01101010             # R = C ^ (A & R)
.endm

.macro SHA2_256_R A, B, C, D, E, F, G, H, W, K, T0, T1, T2, T3
    SHA2_256_S3 \T2, \E, \T0, \T1           # T2 = S3
    SHA2_256_F1 \T1, \E, \F , \G            # T1 = F1
    xc.padd     w , \T0, \T1, \T2           # T0 = S3 + F1
    xc.padd     w , \T0, \T0, \H            # T0 = S3 + F1 + H
    xc.padd     w , \T0, \T0, \W            # T0 = S3 + F1 + H + W
    xc.padd     w , \T0, \T0, \K            # T0 = S3 + F1 + H + K
    SHA2_256_S2 \T3, \A, \T1, \T2           # T3 = S2
    SHA2_256_F0 \T1, \A, \B , \C , \T2      # T1 = F0
    xc.padd     w , \T1, \T1, \T3           # T1 = S2 + F0
    xc.padd     w , \D , \D , \T0           # D += T0
    xc.padd     w , \H , \T1, \T0           # H  = T1 + T0
.endm

.text
.global sha2_256_comp
.func sha2_256_comp
sha2_256_comp:
    # a0 = x = 32-byte array to hash.
    
    la a1, W    # Scratch array base
    la a2, K    # Round constant addresses

    U8_TO_U32_BE c0, a0, a1, 0          #
    U8_TO_U32_BE c0, a0, a1, 1          #
    U8_TO_U32_BE c0, a0, a1, 2          # for i =0..15:
    U8_TO_U32_BE c0, a0, a1, 3          #   W[i] <- BE(x[i])
    U8_TO_U32_BE c0, a0, a1, 4          #
    U8_TO_U32_BE c0, a0, a1, 5          #
    U8_TO_U32_BE c0, a0, a1, 6          #
    U8_TO_U32_BE c0, a0, a1, 7          #
    U8_TO_U32_BE c0, a0, a1, 8          #
    U8_TO_U32_BE c0, a0, a1, 9          #
    U8_TO_U32_BE c0, a0, a1, 10         #
    U8_TO_U32_BE c0, a0, a1, 11         #
    U8_TO_U32_BE c0, a0, a1, 12         #
    U8_TO_U32_BE c0, a0, a1, 13         #
    U8_TO_U32_BE c0, a0, a1, 14         #
    U8_TO_U32_BE c0, a0, a1, 15         #
    
    li  t0, 64
    li  t1, 256

    .L0:
        
        add     a3, a1, t0              # a3 = &W[i]

        xc.ld.w c2, -8 (a3)             # c2 = W[i- 2]
        SHA2_256_S1 c2, c3, c5          # c2 = SHA2_256_S1(W[i-2])
        
        xc.ld.w c4, -60(a3)             # c4 = W[i-15]
        SHA2_256_S0 c4, c3, c5          # c4 = SHA2_256_S0(W[i-15])

        xc.ld.w c3, -28(a3)             # c3 = W[i- 7]
        xc.ld.w c5, -64(a3)             # c5 = W[i-16]
       

        xc.padd w, c2, c2, c3           #
        xc.padd w, c2, c2, c4           #
        xc.padd w, c2, c2, c5           # c2 = sum(t2,t3,t4,t5)

        xc.st.w c2, 0(a3)               # W[i] = c2
        
        addi    t0, t0, 4
        bltu    t0, t1, .L0


    la  a3, H                           # a3 = &H

    xc.ld.w c0, 0 (a3)                  # c0 = a = H[0]
    xc.ld.w c1, 4 (a3)                  # c1 = b = H[1]
    xc.ld.w c2, 8 (a3)                  # c2 = c = H[2]
    xc.ld.w c3, 12(a3)                  # c3 = d = H[3]
    xc.ld.w c4, 16(a3)                  # c4 = e = H[4]
    xc.ld.w c5, 20(a3)                  # c5 = f = H[5]
    xc.ld.w c6, 24(a3)                  # c6 = g = H[6]
    xc.ld.w c7, 28(a3)                  # c7 = h = H[7]
    
    li  t0, 0                           # t0 = i
    li  t1, 256
    
    .L1:
    
        xc.ld.w c8,  0(a1)                  # c8 = W[i+0]
        xc.ld.w c9,  0(a2)                  # c9 = K[i+0]
        
        #          a   b   c   d   e   f   g   h   W   K   t0   t1   t2   t3
        SHA2_256_R c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8,  4(a1)                  # c8 = W[i+1]
        xc.ld.w c9,  4(a2)                  # c9 = K[i+1]
        SHA2_256_R c7, c0, c1, c2, c3, c4, c5, c6, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8,  8(a1)                  # c8 = W[i+2]
        xc.ld.w c9,  8(a2)                  # c9 = K[i+2]
        SHA2_256_R c6, c7, c0, c1, c2, c3, c4, c5, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8, 12(a1)                  # c8 = W[i+3]
        xc.ld.w c9, 12(a2)                  # c9 = K[i+3]
        SHA2_256_R c5, c6, c7, c0, c1, c2, c3, c4, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8, 16(a1)                  # c8 = W[i+4]
        xc.ld.w c9, 16(a2)                  # c9 = K[i+4]
        SHA2_256_R c4, c5, c6, c7, c0, c1, c2, c3, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8, 20(a1)                  # c8 = W[i+5]
        xc.ld.w c9, 20(a2)                  # c9 = K[i+5]
        SHA2_256_R c3, c4, c5, c6, c7, c0, c1, c2, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8, 24(a1)                  # c8 = W[i+6]
        xc.ld.w c9, 24(a2)                  # c9 = K[i+6]
        SHA2_256_R c2, c3, c4, c5, c6, c7, c0, c1, c8, c9, c10, c11, c12, c13
        
        xc.ld.w c8, 28(a1)                  # c8 = W[i+7]
        xc.ld.w c9, 28(a2)                  # c9 = K[i+7]
        SHA2_256_R c1, c2, c3, c4, c5, c6, c7, c0, c8, c9, c10, c11, c12, c13
        
        addi a1, a1, 32                     # a1 = &W[i+8]
        addi a2, a2, 32                     # a2 = &K[i+8]
        
        addi t0, t0, 32
        bltu t0, t1, .L1
    
    xc.ld.w c8 , 0 (a3)                 # c0 = H[0]
    xc.ld.w c9 , 4 (a3)                 # c1 = H[1]
    xc.ld.w c10, 8 (a3)                 # c2 = H[2]
    xc.ld.w c11, 12(a3)                 # c3 = H[3]
    xc.ld.w c12, 16(a3)                 # c4 = H[4]
    xc.ld.w c13, 20(a3)                 # c5 = H[5]
    xc.ld.w c14, 24(a3)                 # c6 = H[6]
    xc.ld.w c15, 28(a3)                 # c7 = H[7]

    xc.padd w, c8 , c8 , c0             # c8 = H[0] + a
    xc.padd w, c9 , c9 , c1             # c9 = H[1] + b
    xc.padd w, c10, c10, c2             # c10= H[2] + c
    xc.padd w, c11, c11, c3             # c11= H[3] + d
    xc.padd w, c12, c12, c4             # c12= H[4] + e
    xc.padd w, c13, c13, c5             # c13= H[5] + f
    xc.padd w, c14, c14, c6             # c14= H[6] + g
    xc.padd w, c15, c15, c7             # c15= H[7] + h
    
    xc.st.w c8 , 0 (a3)                 # H[0] = c0
    xc.st.w c9 , 4 (a3)                 # H[1] = c1
    xc.st.w c10, 8 (a3)                 # H[2] = c2
    xc.st.w c11, 12(a3)                 # H[3] = c3
    xc.st.w c12, 16(a3)                 # H[4] = c4
    xc.st.w c13, 20(a3)                 # H[5] = c5
    xc.st.w c14, 24(a3)                 # H[6] = c6
    xc.st.w c15, 28(a3)                 # H[7] = c7
    
    ret

.endfunc

