
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
    
    xc.gpr2xcr c0, zero         // Value to be returned.
    xc.gpr2xcr c1, zero
    xc.gpr2xcr c2, a0
    addi       t1, a2, 32

    // Loop through two iterations at a time.
    pgfmul_0:

        xc.ld.hu c3,(0), 0(a2)
        xc.ld.hu c6,(0), 2(a2)

        xc.ext    c4, c2, 0, 1  // Put 0'th bit of c2 in c4
        xc.ext    c7, c2, 1, 1  // Put 1'th bit of c2 in c7

        xc.cmov.t c5, c3, c4
        xc.cmov.f c5, c1, c4    // if c4, c5 = c3, else c5=0
        
        xc.cmov.t c8, c6, c7
        xc.cmov.f c8, c1, c7    // if c7, c8 = c6, else c8=0

        xc.bop    c0, c8, c5, 0x96 // XOR c0, c8 and c5. Result in c0.

        xc.psrl.i w, c2, c2, 2  // Shift down c0

        addi a2, a2, 4
        bltu a2, t1, pgfmul_0

    xc.xcr2gpr a0, c0
    mv         a1, zero

    ret
.endfunc

