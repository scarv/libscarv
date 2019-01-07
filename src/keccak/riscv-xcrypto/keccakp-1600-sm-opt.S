
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
    addi a4, a2, 40                          # a4 = &theta_c[5]

    .theta_prep:
        
        xc.ld.w     c0,   0(a3)
        xc.ld.w     c1,  40(a3)
        xc.bop      c0, c0, c1, 0x66
        xc.ld.w     c1,  80(a3)
        xc.bop      c0, c0, c1, 0x66
        xc.ld.w     c1, 120(a3)
        xc.bop      c0, c0, c1, 0x66
        xc.ld.w     c1, 160(a3)
        xc.bop      c0, c0, c1, 0x66
        
        xc.ld.w     c2,   4(a3)
        xc.ld.w     c3,  44(a3)
        xc.bop      c2, c2, c3, 0x66
        xc.ld.w     c3,  84(a3)
        xc.bop      c2, c2, c3, 0x66
        xc.ld.w     c3, 124(a3)
        xc.bop      c2, c2, c3, 0x66
        xc.ld.w     c3, 164(a3)
        xc.bop      c2, c2, c3, 0x66

        xc.st.w     c0,   0(a2)
        xc.st.w     c2,   4(a2)
        
        addi    a3, a3, 8
        addi    a2, a2, 8
        bltu    a2, a4, .theta_prep


    la      a7, rho_off
    la      a6, temp_a
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    addi    a2, a2, -40                     # a2 = &theta_c

    xc.gpr2xcr c15, zero
    xc.ld.liu  c15, 1                       # Shift amount
    xc.gpr2xcr c14, zero
    xc.ld.liu  c14, 63                      # Shift amount 2
    xc.padd    w, c13, c14, c15             # c13 = 64
    xc.bop     c12, c13, c14, 0xEE          # OR

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        xc.sha3.x1 a3, t0, zero, 3          # a3 = (x+1)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+1)%5]
        
        xc.ld.w c6, 0(a3)                   # 
        xc.ld.w c7, 4(a3)                   # t4,t3 = theta_c[(x+1)%5]

        xc.msll (c8,c9), c6, c7, c15
        xc.msrl (c6,c7), c6, c7, c14

        xc.bop  c6, c6, c8, 0xEE            # OR
        xc.bop  c7, c7, c9, 0xEE            # OR
        
        xc.sha3.x4 a3, t0, zero, 3          # a4 = (x+4)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+4)%5]
        
        xc.ld.w c8, 0(a3)                   # 
        xc.ld.w c9, 4(a3)                   # t4,t3 = theta_c[(x+1)%5]
        
        xc.bop  c6, c6, c8, 0x66            # c7,c6 = D
        xc.bop  c7, c7, c9, 0x66            #
        
        .L1:

            xc.sha3.xy t3, t0, t1, 3        # t3 = (5*y)+x = index(x,y)
            add     t4, t3, a0              # t4 = &A[index(x,y)]

            xc.ld.w c4, 0(t4)               # 
            xc.ld.w c3, 4(t4)               # c4,c3 = A[index(x,y)]

            xc.bop  c3, c3, c7, 0x66        # c7,c6 = D
            xc.bop  c4, c4, c6, 0x66        #

            srli    t4, t3, 2               # Halfword align index(x,y)
            add     t4, t4, a7              # t4 = &rho_off[index(x,y)]

            xc.ld.hu c1, (0), 0(t4)
            
            #
            #  64-bit left rotation of a5,a4 by t4
            #

            xc.psub w, c2, c13, c1
            xc.msll (c8, c9), c4, c3, c1
            xc.msrl (c4, c5), c4, c3, c2

            xc.bop  c4, c4, c8, 0xEE
            xc.bop  c5, c5, c9, 0xEE

            #
            # Store a5,a4 back to tempA[index(y,2x+3y)]
            #  - t0 = x 
            #  - t1 = y
        
            xc.sha3.yx t3, t0, t1, 3
            add     t4, t3, a6              # t4 = &a_temp[5((2x+3y)%5)+y]
            
            xc.st.w c4, 0(t4)               #   a5,a4
            xc.st.w c5, 4(t4)               # a_temp[y + 5((2*x+3*y)%5)] =

            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L1

        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    li      t5, 40

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:
            
            xc.sha3.x1 t4, t0, t1, 3        # t4 = (x+1)%5 + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+1)%5) + 5y]

            xc.ld.w c0, 0(t4)               # c1,c0 =a_temp[((x+1)%5) + 5y] 
            xc.ld.w c1, 4(t4)               # 
            
            xc.sha3.x2 t4, t0, t1, 3        # t4 = (x+2)%5 + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+2)%5) + 5y]
            
            xc.ld.w c2, 0(t4)               # c3,c2 =a_temp[((x+2)%5) + 5y] 
            xc.ld.w c3, 4(t4)               # 

            xc.bop  c0, c0, c2, 0x22        # c0 = (~c0) & c2
            xc.bop  c1, c1, c3, 0x22        # c1 = (~c1) & c3
            
            xc.sha3.xy s2, t0, t1, 3        # t6 = x + 5y
            add     t4, s2, a6              # t4 = &a_temp[((x) + 5y]
            
            xc.ld.w c4, 0(t4)               # c5,c4 =a_temp[((x)) + 5y] 
            xc.ld.w c5, 4(t4)               # 
            
            xc.bop  c0, c0, c4, 0x66        # c0 = c0 ^ c2
            xc.bop  c1, c1, c5, 0x66        # c1 = c1 ^ c3
            
            add     t4, s2, a0              # t4 = &A[((x) + 5y]
            
            xc.st.w c0, 0(t4)               # A[t4] = c1,c0
            xc.st.w c1, 4(t4)               # 
            
            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L3

    # Iota
    la      t0, round_consts
    slli    a1, a1, 3
    add     t1, t0, a1

    xc.ld.w c2, 0(t1)                       # t3,t2 = round_consts[index]
    xc.ld.w c3, 4(t1)                       #

    xc.ld.w c4, 0(a0)
    xc.ld.w c5, 4(a0)

    xc.bop  c4, c4, c2, 0x66                # XOR
    xc.bop  c5, c5, c3, 0x66                # XOR
    
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
