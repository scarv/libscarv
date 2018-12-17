
.data 
sbox:               # Forward SBOX for prince
    .byte 0xb
    .byte 0xf
    .byte 0x3
    .byte 0x2
    .byte 0xa
    .byte 0xc
    .byte 0x9
    .byte 0x1
    .byte 0x6
    .byte 0x7
    .byte 0x8
    .byte 0x0
    .byte 0xe
    .byte 0x5
    .byte 0xd
    .byte 0x4

inv_sbox:           # Inverse SBOX for prince
    .byte 0xb
    .byte 0x7
    .byte 0x3
    .byte 0x2
    .byte 0xf
    .byte 0xd
    .byte 0x8
    .byte 0x9
    .byte 0xa
    .byte 0x6
    .byte 0x4
    .byte 0x0
    .byte 0x5
    .byte 0xe
    .byte 0xc
    .byte 0x1

.text

.func   prince_sbox
.global prince_sbox
prince_sbox:
    # 
    # a0/a1 - uint64_t s_in
    #

    la t0, sbox
    j  prince_sbox_dual
.endfunc


.func   prince_inv_sbox
.global prince_inv_sbox
prince_inv_sbox:
    # 
    # a0/a1 - uint64_t s_in
    #

    la t0, inv_sbox
    j  prince_sbox_dual
.endfunc

#
# Dual purpose sbox code.
# - Expects the address of the SBOX to use to be in register t0
# - a0/a1 - uint64)t s_in
#
.func   prince_sbox_dual
prince_sbox_dual:
    la t1, 0
    la t2, 32

    la t5, 0
    la t6, 0

    .prince_sbox_l0:

        srl  a2, a0, t1             # a2 = lo(s_in) >> t3
        srl  a3, a1, t1             # a3 = hi(s_in) >> t3

        andi a2, a2, 0xF            # Isolate nibble
        andi a3, a3, 0xF            # Isolate nibble

        add  a2, a2, t0             # a2 = &sbox[(hi(s_in) >> t3) & 0xF]
        add  a3, a3, t0             # a3 = &sbox[(lo(s_in) >> t3) & 0xF]

        lbu  a2, 0(a2)              # a2 =  sbox[(hi(s_in) >> t3) & 0xF]
        lbu  a3, 0(a3)              # a3 =  sbox[(lo(s_in) >> t3) & 0xF]

        sll  a2, a2, t1
        sll  a3, a3, t1

        or   t5, t5, a2
        or   t6, t6, a3
        
        addi t1, t1, 4
        bltu t1, t2, .prince_sbox_l0
    
    mv a0, t5
    mv a1, t6

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

