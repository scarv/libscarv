
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
        xc.ld.w     c2,  80(a3)
        xc.bop      c0, c1, c2, 0b10010110
        xc.ld.w     c1, 120(a3)
        xc.ld.w     c2, 160(a3)
        xc.bop      c0, c1, c2, 0b10010110
        xc.st.w     c0,   0(a2)
        
        xc.ld.w     c0,   4(a3)
        xc.ld.w     c1,  44(a3)
        xc.ld.w     c2,  84(a3)
        xc.bop      c0, c1, c2, 0b10010110
        xc.ld.w     c1, 124(a3)
        xc.ld.w     c2, 164(a3)
        xc.bop      c0, c1, c2, 0b10010110
        xc.st.w     c0,   4(a2)
        
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

    addi a5, a2, 4          # a5 = &theta_c[1]
    addi t5, a0, 4          # t5 = &A[1]
    addi t6, a6, 4          # t5 = &temp_a[1]

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        xc.sha3.x1 a3, t0, zero, 3          # a3 = (x+1)%5
        
        xc.ldr.w c6, a3, a2                 # 
        xc.ldr.w c7, a3, a5                 # c7,c6 = theta_c[(x+1)%5]

        xc.msll (c8,c9), c6, c7, c15
        xc.msrl (c6,c7), c6, c7, c14

        xc.bop  c6, c6, c8, 0xEE            # OR
        xc.bop  c7, c7, c9, 0xEE            # OR
        
        xc.sha3.x4 a3, t0, zero, 3          # a4 = (x+4)%5
        
        xc.ldr.w c8, a3, a2                    # 
        xc.ldr.w c9, a3, a5                    # c9,c8 = theta_c[(x+1)%5]
        
        xc.bop  c6, c6, c8, 0x66            # c7,c6 = D
        xc.bop  c7, c7, c9, 0x66            #
        
        .L1:

            xc.sha3.xy t3, t0, t1, 3        # t3 = (5*y)+x = index(x,y)

            xc.ldr.w c4, t3, a0             # 
            xc.ldr.w c3, t3, t5             # c4,c3 = A[index(x,y)]

            xc.bop  c3, c3, c7, 0x66        # c7,c6 = D
            xc.bop  c4, c4, c6, 0x66        #

            srli    t4, t3, 2               # Halfword align index(x,y)
            xc.ldr.hu c1(0), t4, a7         # c1 = rho_off[index(x,y)]
            
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
        
            xc.sha3.yx t3, t0, t1, 3        # t3 = y + 5((2*x+3*y)%5)
            
            xc.str.w c4, t3, a6             #
            xc.str.w c5, t3, t6             # a_temp[y + 5((2*x+3*y)%5)] =

            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L1

        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    li      t5, 40
    addi    a7, a6, 4                       # a7 = &a_temp[1]
    addi    t3, a0, 4                       # t3 = &A[1]

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:
            
            xc.sha3.x1 t4, t0, t1, 3        # t4 = (x+1)%5 + 5y

            xc.ldr.w c0, t4, a6             # c1,c0 =a_temp[((x+1)%5) + 5y] 
            xc.ldr.w c1, t4, a7             # 
            
            xc.sha3.x2 t4, t0, t1, 3        # t4 = (x+2)%5 + 5y
            
            xc.ldr.w c2, t4, a6             # c1,c0 =a_temp[((x+2)%5) + 5y] 
            xc.ldr.w c3, t4, a7             # 

            xc.sha3.xy s2, t0, t1, 3        # s2 = x + 5y
            
            xc.ldr.w c4, s2, a6             # c1,c0 =a_temp[x + 5y] 
            xc.ldr.w c5, s2, a7             # 
            
            xc.bop  c2, c0, c4, 0b10011010  # c2 = (c2 & (~c0)) ^ c4
            xc.bop  c3, c1, c5, 0b10011010  # c2 = (c3 & (~c1)) ^ c5
            
            xc.str.w c2, s2, a0             # A[(x) + 5y] = c1,c0
            xc.str.w c3, s2, t3             # 
            
            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L3

    # Iota
    la      t0, round_consts
    slli    a1, a1, 3
    add     t1, t0, a1

    xc.ld.w c2, 0(t1)                       # c3,c2 = round_consts[index]
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
