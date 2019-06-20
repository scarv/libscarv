
#
# Auxiliary storage 
.data
theta_c: .fill 40, 8, 0
theta_d: .fill 40, 8, 0
chi_aux: .fill 40, 8, 0
.align 8,0
temp_a : .fill 200, 8, 0
rho_off:
    .hword  0
    .hword  1
    .hword 62
    .hword 28
    .hword 27
    .hword 36
    .hword 44
    .hword  6
    .hword 55
    .hword 20
    .hword  3
    .hword 10
    .hword 43
    .hword 25
    .hword 39
    .hword 41
    .hword 45
    .hword 15
    .hword 21
    .hword  8
    .hword 18
    .hword  2
    .hword 61
    .hword 56
    .hword 14
.align 8,0
round_consts:
    .dword 0x0000000000000001
    .dword 0x0000000000008082
    .dword 0x800000000000808a
    .dword 0x8000000080008000
    .dword 0x000000000000808b
    .dword 0x0000000080000001
    .dword 0x8000000080008081
    .dword 0x8000000000008009
    .dword 0x000000000000008a
    .dword 0x0000000000000088
    .dword 0x0000000080008009
    .dword 0x000000008000000a
    .dword 0x000000008000808b
    .dword 0x800000000000008b
    .dword 0x8000000000008089
    .dword 0x8000000000008003
    .dword 0x8000000000008002
    .dword 0x8000000000000080
    .dword 0x000000000000800a
    .dword 0x800000008000000a
    .dword 0x8000000080008081
    .dword 0x8000000000008080
    .dword 0x0000000080000001
    .dword 0x8000000080008008

.if CONF_KECCAKP1600_INDEX_FUNC==1
mod5_lut:
    .dword 0 << 3# 0
    .dword 1 << 3# 1
    .dword 2 << 3# 2
    .dword 3 << 3# 3
    .dword 4 << 3# 4
    .dword 0 << 3# 5
    .dword 1 << 3# 6
    .dword 2 << 3# 7
    .dword 3 << 3# 8
    .dword 4 << 3# 9
    .dword 0 << 3# 10
    .dword 1 << 3# 11
    .dword 2 << 3# 12
    .dword 3 << 3# 13
    .dword 4 << 3# 14
    .dword 0 << 3# 15
    .dword 1 << 3# 16
    .dword 2 << 3# 17
    .dword 3 << 3# 18
    .dword 4 << 3# 19
    .dword 0 << 3# 20
    .dword 1 << 3# 21
    .dword 2 << 3# 22
    .dword 3 << 3# 23
    .dword 4 << 3# 24
    .dword 0 << 3# 25
.endif

.macro MOD5 A, B, C
    .if CONF_KECCAKP1600_INDEX_FUNC==1
        add     \A, \A, \C
        lbu     \A, 0(\A)
    .else
        remu    \A, \A, \B
    .endif
.endm

.text

.func KeccakP1600Round
.global KeccakP1600Round
KeccakP1600Round:
    # Arguments:
    # - a0 - tKeccakLane * A
    # - a1 - unsigned int  roundIndex
    #
    # Notes:
    # - 1 lane = 2 words = 8 bytes
    #

    addi    sp, sp, -44
    sw      s3, 4(sp)
    sw      s4, 8(sp)
    sw      s5,16(sp)
    sw      s6,20(sp)
    sw      s7,24(sp)
    sw      s2,28(sp)
    .if CONF_KECCAKP1600_INDEX_FUNC==1
         sw s0,32(sp)
    .endif

    #
    # Theta function preparation
    la  a2, theta_c                         # a2 = &theta_c
    mv  a3, a0                              # a3 = &A
    add a4, a2, 40                          # a4 = &theta_c[5]

    .theta_prep:
        
        lw      t0,   0(a3)
        lw      t1,  40(a3)
        xor     t0, t0, t1
        lw      t1,  80(a3)
        xor     t0, t0, t1
        lw      t1, 120(a3)
        xor     t0, t0, t1
        lw      t1, 160(a3)
        xor     t0, t0, t1
        
        lw      t2,   4(a3)
        lw      t3,  44(a3)
        xor     t2, t2, t3
        lw      t3,  84(a3)
        xor     t2, t2, t3
        lw      t3, 124(a3)
        xor     t2, t2, t3
        lw      t3, 164(a3)
        xor     t2, t2, t3

        sw      t0,   0(a2)
        sw      t2,   4(a2)
        
        addi    a3, a3, 8
        addi    a2, a2, 8
        bltu    a2, a4, .theta_prep


    la      a7, rho_off
    la      a6, temp_a
    .if CONF_KECCAKP1600_INDEX_FUNC==1
        la      s0, mod5_lut
    .endif
    li      t0, 0                           # t0 = x = 0
    li      t2, 40
    addi    a2, a2, -40                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        addi    a3, t0, 8                   # a3 = x+1
        MOD5    a3, t2, s0                  # a3 = (x+1)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+1)%5]

        lw      t3, 0(a3)                   # 
        lw      t4, 4(a3)                   # t4,t3 = theta_c[(x+1)%5]

        slli    t5, t3, 1
        slli    t6, t4, 1
        srli    t3, t3, 31
        srli    t4, t4, 31

        or      t4, t5, t4
        or      t3, t6, t3                  # t4,t3 = theta_c[(x+1)%5] << 1
        
        addi    a3, t0, 32                  # a3 = x+4
        MOD5    a3, t2, s0                  # a3 = (x+4)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+4)%5]

        lw      t5, 0(a3)                   # 
        lw      t6, 4(a3)                   # t6,t5 = theta_c[(x+4)%5]

        xor     t5, t4, t5                  # t6,t5 = (theta_c[(x+1)%5]<<<1)^
        xor     t6, t3, t6                  #          theta_c[(x+4)%5]
        
        .L1:

            slli    t4, t1, 2               # t4 = 4*y
            add     t4, t4, t1              # t4 = 5*y
            add     t3, t4, t0              # t3 = (5*y)+x = index(x,y)
            add     t4, t3, a0              # t4 = &A[index(x,y)]
            lw      a5, 0(t4)               # 
            lw      a4, 4(t4)               # a5,a4 = A[index(x,y)]

            xor     a5, a5, t5              # a5,a4 = A[index(x,y)] ^ D
            xor     a4, a4, t6              #

            srli    t4, t3, 2               # Halfword align index(x,y)
            add     t4, t4, a7              # t4 = &rho_off[index(x,y)]
            lhu     t4, 0(t4)               # t4 = rho_off[index(x,y)]
            
            #
            #  64-bit left rotation of a5,a4 by t4
            #

            beqz    t4, rot64_n_finish

            rot64_n:
                andi	s4,t4, 0x3f                 # s4 = t4
                addi	s5,s4,-32                   # s5 = t4 - 32
                bltz	s5, .rot64_1
                li	    s4,64
                sub	    t4,s4,t4
                addi	s4,t4,-32
                sll	    s5,a4,s5
                li	    s3,0
                bltz	s4, .rot64_2
            
            .rot64_0:
                srl	    a4,a5,s4                    # a4 = a5 >> s4
                li	    a5,0
                or	    a4,s3,a4
                or	    a5,s5,a5
                j       rot64_n_finish
            
            .rot64_1:
                li	    s5,31                       # s5 = 31
                sub	    s5,s5,s4                    # s5 = 31 - t4
                srli	s3,a4,0x1                   # s3 = a4 >> 1
                srl	    s3,s3,s5                    # s3 = a4 >> (32-t4)
                sll	    s5,a5,s4                    # s5 = a5 << t4
                or	    s5,s3,s5                    # s5 = 
                sll	    s3,a4,s4                    # s3 = a4 << t4
                li	    s4,64                       # s4 =  64
                sub	    t4,s4,t4                    # t4 =  64 - t4
                addi	s4,t4,-32                   # s4 = (64 - t4) - 32
                bgez	s4,.rot64_0
            
            .rot64_2:
                li	    s6,31
                slli	s4,a5,0x1
                sub	    s6,s6,t4
                sll	    s4,s4,s6
                srl	    a4,a4,t4
                or	    a4,s4,a4
                srl	    a5,a5,t4
                or	    a4,s3,a4
                or	    a5,s5,a5
            
            rot64_n_finish:

            #
            # Store a5,a4 back to tempA[index(y,2x+3y)]
            #  - t0 = x 
            #  - t1 = y
        
            slli    t3, t0, 1               # t3 = 2x
            slli    t4, t1, 1               # t4 = 2y
            add     t4, t4, t1              # t4 = 3y
            add     t3, t3, t4              # t4 = 2x + 3y
            MOD5    t3, t2, s0              # t3 = (2x+3y)%5
            slli    t4, t3, 2               # t4 = 4((2x+3y)%5)
            add     t3, t3, t4              # t3 = 5((2x+3y)%5)
            add     t3, t3, t1              # t3 = 5((2x+3y)%5) + y
            add     t4, t3, a6              # t4 = &a_temp[5((2x+3y)%5)+y]

            sw      a5, 0(t4)               #   a5,a4
            sw      a4, 4(t4)               # a_temp[y + 5((2*x+3*y)%5)] =

            addi    t1, t1, 8               # y += 1
            bltu    t1, t2, .L1

        addi    t0, t0, 8                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t2, 200
    li      t5, 40

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:
            
            addi    t4, t0, 8               # t4 = x+1
            MOD5    t4, t5, s0              # t4 = (x+1) % 5
            add     t4, t4, t1              # t4 = ((x+1)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+1)%5) + 5y]

            lw      a4, 0(t4)               # a5,a4 =a_temp[((x+1)%5) + 5y] 
            lw      a5, 4(t4)               # 
            
            addi    t4, t0, 16              # t4 = x+2
            MOD5    t4, t5, s0              # t4 = (x+2) % 5
            add     t4, t4, t1              # t4 = ((x+2)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+2)%5) + 5y]
            
            lw      s4, 0(t4)               # a5,a4 =a_temp[((x+2)%5) + 5y] 
            lw      s5, 4(t4)               # 

            not     a4, a4
            not     a5, a5

            and     s4, s4, a4              # s5,s4 = ~X & Y
            and     s5, s5, a5              #
            
            add     s2, t0, t1              # t4 = ((x) + 5y
            add     t4, s2, a6              # t4 = &a_temp[((x) + 5y]
            
            lw      a4, 0(t4)               # a5,a4 =a_temp[((x)) + 5y] 
            lw      a5, 4(t4)               # 
            
            xor     a4, s4, a4              # s5,s4 = ~X & Y
            xor     a5, s5, a5              #
            
            add     t4, s2, a0              # t4 = &A[((x) + 5y]
            
            sw      a4, 0(t4)               # A[t4] = a5,a4
            sw      a5, 4(t4)               # 
            
            addi    t1, t1, 40              # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 8                   # x += 1
        bltu    t0, t5, .L3

    # Iota
    la      t0, round_consts
    slli    a1, a1, 3
    add     t1, t0, a1

    lw      t2, 0(t1)                       # t3,t2 = round_consts[index]
    lw      t3, 4(t1)                       #

    lw      t4, 0(a0)
    lw      t5, 4(a0)

    xor     t4, t4, t2
    xor     t5, t5, t3
    
    sw      t4, 0(a0)
    sw      t5, 4(a0)

    #
    # Stack management

    lw      s3, 4(sp)
    lw      s4, 8(sp)
    lw      s5,16(sp)
    lw      s6,20(sp)
    lw      s7,24(sp)
    lw      s2,28(sp)
    .if CONF_KECCAKP1600_INDEX_FUNC==1
         lw s0,32(sp)
    .endif
    addi    sp, sp, 44

    ret

.endfunc
