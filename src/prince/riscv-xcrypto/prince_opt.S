
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
    
    xc.gpr2xcr c0, zero
    xc.gpr2xcr c1, zero
    xc.gpr2xcr c2, a0
    li         t0, 0
    li         t1, 32

    pgfmul_0:

        xc.ldr.hu c3(0), a2, t0

        xc.ext    c4, c2, 0, 1  // Put 0'th bit of c2 in c4

        xc.cmov.t c5, c3, c4
        xc.cmov.f c5, c1, c4    // if c4, c5 = c3, else c3=0

        xc.bop    c0, c0, c5, 0x66 // XOR

        xc.psrl.i w, c2, c2, 1  // Shift down c0

        addi t0, t0, 2
        bltu t0, t1, pgfmul_0

    xc.xcr2gpr a0, c0
    mv         a1, zero

    ret
.endfunc


.func prince_shift_rows
.global prince_shift_rows
prince_shift_rows:

    # a1,a0 = in
    # a2    = inverse

    li t0, 0
    li t1, 4

    xc.ld.liu c2, 0xF000
    xc.pbyte  c2, c2, 0,1,0,1

    xc.gpr2xcr c0, a0
    xc.gpr2xcr c1, a1

    li t2, 16
    li t3, 0 
    li t4, 0 
    
    beqz a2, psr_0

    li t2, -16
    li t3, 64
    li t4, 64

    xc.gpr2xcr c6, t2
    xc.gpr2xcr c7, t3
    xc.gpr2xcr c8, t4
    xc.gpr2xcr c9, t4

    psr_0:
        
        // row = in & smask
        xc.bop       c3, c0, c2, 0x88   // c3 = c0 & c2
        xc.bop       c4, c1, c2, 0x88   // c4 = c1 & c2

        xc.psll.i w, c2, c2, 4          // Shift the mask down

        // compute the shift
        //xc.msrl.i 

        addi t0, t0, 1
        bltu t0, t1, psr_0

    ret

.endfunc

