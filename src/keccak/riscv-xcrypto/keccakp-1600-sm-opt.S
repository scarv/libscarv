
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

    addi    sp, sp, -40
    sw      s3, 4(sp)
    sw      s4, 8(sp)
    sw      s5,16(sp)
    sw      s6,20(sp)
    sw      s7,24(sp)
    sw      s2,28(sp)

    #
    # Theta function preparation
    la  a2, theta_c                         # a2 = &theta_c
    mv  a3, a0                              # a3 = &A
    add a4, a2, 40                          # a4 = &theta_c[5]

    .theta_prep:
        
        xc.ld.w     c0,   0(a3)
        xc.ld.w     c1,  40(a3)
        xc.bop      c0, c0, c1, 0x6
        xc.ld.w     c1,  80(a3)
        xc.bop      c0, c0, c1, 0x6
        xc.ld.w     c1, 120(a3)
        xc.bop      c0, c0, c1, 0x6
        xc.ld.w     c1, 160(a3)
        xc.bop      c0, c0, c1, 0x6
        
        xc.ld.w     c2,   4(a3)
        xc.ld.w     c3,  44(a3)
        xc.bop      c2, c2, c3, 0x6
        xc.ld.w     c3,  84(a3)
        xc.bop      c2, c2, c3, 0x6
        xc.ld.w     c3, 124(a3)
        xc.bop      c2, c2, c3, 0x6
        xc.ld.w     c3, 164(a3)
        xc.bop      c2, c2, c3, 0x6

        xc.st.w     c0,   0(a2)
        xc.st.w     c2,   4(a2)
        
        addi    a3, a3, 8
        addi    a2, a2, 8
        bltu    a2, a4, .theta_prep


    la      a7, rho_off
    la      a6, temp_a
    li      t0, 0                           # t0 = x = 0
    li      t2, 40
    addi    a2, a2, -40                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        addi    a3, t0, 8                   # a3 = x+1
        remu    a3, a3, t2                  # a3 = (x+1)%5
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
        remu    a3, a3, t2                  # a3 = (x+4)%5
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
            remu    t3, t3, t2              # t3 = (2x+3y)%5
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
            remu    t4, t4, t5              # t4 = (x+1) % 5
            add     t4, t4, t1              # t4 = ((x+1)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+1)%5) + 5y]

            xc.ld.w c0, 0(t4)               # c1,c0 =a_temp[((x+1)%5) + 5y] 
            xc.ld.w c1, 4(t4)               # 
            
            addi    t4, t0, 16              # t4 = x+2
            remu    t4, t4, t5              # t4 = (x+2) % 5
            add     t4, t4, t1              # t4 = ((x+2)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+2)%5) + 5y]
            
            xc.ld.w c2, 0(t4)               # c3,c2 =a_temp[((x+2)%5) + 5y] 
            xc.ld.w c3, 4(t4)               # 

            xc.bop  c0, c0, c2, 0x2         # c0 = (~c0) & c2
            xc.bop  c1, c1, c3, 0x2         # c1 = (~c1) & c3
            
            add     s2, t0, t1              # t4 = ((x) + 5y
            add     t4, s2, a6              # t4 = &a_temp[((x) + 5y]
            
            xc.ld.w c4, 0(t4)               # c5,c4 =a_temp[((x)) + 5y] 
            xc.ld.w c5, 4(t4)               # 
            
            xc.bop  c0, c0, c4, 0x6         # c0 = c0 ^ c2
            xc.bop  c1, c1, c5, 0x6         # c1 = c1 ^ c3
            
            add     t4, s2, a0              # t4 = &A[((x) + 5y]
            
            xc.st.w c0, 0(t4)               # A[t4] = c1,c0
            xc.st.w c1, 4(t4)               # 
            
            addi    t1, t1, 40              # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 8                   # x += 1
        bltu    t0, t5, .L3

    # Iota
    la      t0, round_consts
    slli    a1, a1, 3
    add     t1, t0, a1

    xc.ld.w c2, 0(t1)                       # t3,t2 = round_consts[index]
    xc.ld.w c3, 4(t1)                       #

    xc.ld.w c4, 0(a0)
    xc.ld.w c5, 4(a0)

    xc.bop  c4, c4, c2, 0x6                 # XOR
    xc.bop  c5, c5, c3, 0x6                 # XOR
    
    xc.st.w c4, 0(a0)
    xc.st.w c5, 4(a0)

    #
    # Stack management

    lw      s3, 4(sp)
    lw      s4, 8(sp)
    lw      s5,16(sp)
    lw      s6,20(sp)
    lw      s7,24(sp)
    lw      s2,28(sp)
    addi    sp, sp, 40

    ret

.endfunc
