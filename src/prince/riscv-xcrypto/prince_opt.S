
.data 
.align 4
sbox:               # Forward SBOX for prince
    .word 0x19ca23fb        # 7..0
    .word 0x4d5e0876        # 15..8

inv_sbox:           # Inverse SBOX for prince
    .word 0x98df237b        # 7..0
    .word 0x1ce5046a        # 15..8

.text

.func   prince_sbox
.global prince_sbox
prince_sbox:
    # 
    # a0/a1 - uint64_t s_in
    #

    la t0, sbox

    xc.gpr2xcr c0, a0
    xc.gpr2xcr c1, a1

    xc.ld.w c3, 0(t0)
    xc.ld.w c4, 4(t0)
    
    xc.lut  c0, c0, c3, c4
    xc.lut  c1, c1, c3, c4
    
    xc.xcr2gpr a0, c0
    xc.xcr2gpr a1, c1

    ret
.endfunc


.func   prince_inv_sbox
.global prince_inv_sbox
prince_inv_sbox:
    # 
    # a0/a1 - uint64_t s_in
    #

    la t0, inv_sbox

    xc.gpr2xcr c0, a0
    xc.gpr2xcr c1, a1

    xc.ld.w c3, 0(t0)
    xc.ld.w c4, 4(t0)
    
    xc.lut    c0, c0, c3, c4
    xc.lut    c1, c1, c3, c4
    
    xc.xcr2gpr a0, c0
    xc.xcr2gpr a1, c1

    ret
.endfunc


.func   prince_gf_mul
.global prince_gf_mul
prince_gf_mul:
    #
    # a1,a0 = in
    # a2    = uint16_t mat [16]
    #
    
    li t0, 0
    li t1, 16
    li t3, 0                # result

    .prince_fg_mul_l0:

        lhu  a3, 0(a2)      # a3 =  mat[i]

        srl  t4, a0, t0     # t4 = in >> t1
        andi t4, t4, 0x1    # t4 = (in >> t1) & 0x1

        slli t4, t4, 31     #
        srai t4, t4, 31     # Create 32-bit mask from result in t4

        and  a3, a3, t4     # And with loaded element of matrix to
        xor  t3, t3, a3     # remove branch on hash value.

        addi t0, t0, 1
        addi a2, a2, 2      # Step through mat, 1 halfword an interation
        bltu t0, t1, .prince_fg_mul_l0

    mv a0, t3
    mv a1, zero

    ret
.endfunc


.func prince_shift_rows
.global prince_shift_rows
prince_shift_rowsa:

    li t0, 0
    li t1, 4

    xc.ld.liu  c0, 0xF000
    xc.pperm.w c0, c0, 0, 1, 0, 1
    xc.ld.liu  c6,  0
    xc.ld.liu  c7, 16
    xc.ld.liu  c8, 64
    xc.ld.hiu  c6,  0
    xc.ld.hiu  c7,  0
    xc.ld.hiu  c8,  0
    
    xc.gpr2xcr c10, zero
    xc.gpr2xcr c11, zero
        
    xc.gpr2xcr c12, a0
    xc.gpr2xcr c13, a1

    bnez a2, .psr_1

    .psr_0:

        xc.bop     c3, c13, c0, 0x88     # c2,c3 - in & (rowmask >> 4*i)
        xc.bop     c2, c12, c0, 0x88

        xc.msrl (c4,c5), c2, c3, c8     # row >> shift
        xc.msll (c2,c3), c2, c3, c6     # row << (64-shift)

        xc.bop  c2, c2, c4, 0xEE        # OR
        xc.bop  c3, c3, c5, 0xEE        # OR
        
        xc.bop  c10, c10, c2, 0xEE      # OR
        xc.bop  c11, c11, c3, 0xEE      # OR

        xc.psub  w, c8, c8, c7
        xc.padd  w, c6, c6, c7

        xc.psrl.i w, c0, c0, 4          

        addi t0, t0, 1
        bltu t0, t1, .psr_0
    
    xc.xcr2gpr a1, c11
    xc.xcr2gpr a0, c10

    ret

    .psr_1:

        xc.bop     c3, c13, c0, 0x88     # c2,c3 - in & (rowmask >> 4*i)
        xc.bop     c2, c12, c0, 0x88

        xc.msrl (c4,c5), c2, c3, c6     # row >> shift
        xc.msll (c2,c3), c2, c3, c8     # row << (64-shift)

        xc.bop  c2, c2, c4, 0xEE        # OR
        xc.bop  c3, c3, c5, 0xEE        # OR
        
        xc.bop  c10, c10, c2, 0xEE      # OR
        xc.bop  c11, c11, c3, 0xEE      # OR

        xc.psub  w, c8, c8, c7
        xc.padd  w, c6, c6, c7

        xc.psrl.i w, c0, c0, 4          

        addi t0, t0, 1
        bltu t0, t1, .psr_1
    
    xc.xcr2gpr a1, c11
    xc.xcr2gpr a0, c10

    ret

.endfunc

