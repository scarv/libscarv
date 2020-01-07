// Copyright (C) 2019 SCARV project <info@scarv.org>
// 
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).
// 

.data 
.align 4
sbox:               // Forward SBOX for prince
    .word 0x19ca23fb        // 7..0
    .word 0x4d5e0876        // 15..8

inv_sbox:           // Inverse SBOX for prince
    .word 0x98df237b        // 7..0
    .word 0x1ce5046a        // 15..8

.text

.func   prince_sbox
.global prince_sbox
prince_sbox:
    // 
    // a0/a1 - uint64_t s_in
    //

    la t0, sbox

    lw a3, 0(t0)
    lw a4, 4(t0)
    
    xc.lut  a0, a4, a3
    xc.lut  a1, a4, a3

    ret
.endfunc


.func   prince_isbox
.global prince_isbox
prince_isbox:
    // 
    // a0/a1 - uint64_t s_in
    //

    la t0, inv_sbox

    lw a3, 0(t0)
    lw a4, 4(t0)
    
    xc.lut  a0, a4, a3
    xc.lut  a1, a4, a3

    ret
.endfunc


.func   prince_gf_mul
.global prince_gf_mul
prince_gf_mul:
    //
    // a1,a0 = in
    // a2    = uint16_t mat [16]
    //

    li t0, 0                            // t0 = i
    li t1, 16

    li a3, 0                            // out = 0
    
    // Loop through two iterations at a time.
    pgfmul_0:

        xc.ldr.hu   t2, a2(t0)          // t2 = mat[i]
        andi        t3, a0, 0x1         // t3 = in & 0x1

        cmov        t3, t3, t2, zero    // t3 = t3 ? mat[i] : 0

        xor         a3, a3, t3          // out ^= t3

        srli        a0, a0, 1           // in >> 1
        addi        t0, t0, 1           // i += 1
        bltu        t0, t1, pgfmul_0

    mv a0, a3
    mv a1, zero

    ret
.endfunc

.func   prince_shift_rows
.global prince_shift_rows
prince_shift_rows:

    // TODO

    li t0, 1000
    .l0:
        addi t0, t0, -1
        bnez t0, .l0

    ret
.endfunc

