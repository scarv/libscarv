
#
# Auxiliary storage 
.data
theta_c: .fill 10, 8, 0
theta_d: .fill 10, 8, 0
chi_aux: .fill 10, 8, 0
.align 8,0
temp_a : .fill 50, 8, 0
rho_off:
    .hword 16 -  0
    .hword 16 -  1
    .hword 16 - 14
    .hword 16 - 12
    .hword 16 - 11
    .hword 16 -  4
    .hword 16 - 12
    .hword 16 -  6
    .hword 16 -  7
    .hword 16 -  4
    .hword 16 -  3
    .hword 16 - 10
    .hword 16 - 11
    .hword 16 -  9
    .hword 16 -  7
    .hword 16 -  9
    .hword 16 - 13
    .hword 16 - 15
    .hword 16 -  5
    .hword 16 -  8
    .hword 16 -  2
    .hword 16 -  2
    .hword 16 - 13
    .hword 16 -  8
    .hword 16 - 14                                             
round_consts:
    .hword 0x0001
    .hword 0x8082
    .hword 0x808a
    .hword 0x8000
    .hword 0x808b
    .hword 0x0001
    .hword 0x8081
    .hword 0x8009
    .hword 0x008a
    .hword 0x0088
    .hword 0x8009
    .hword 0x000a
    .hword 0x808b
    .hword 0x008b
    .hword 0x8089
    .hword 0x8003
    .hword 0x8002
    .hword 0x0080
    .hword 0x800a
    .hword 0x000a

.text

.func KeccakP400Round
.global KeccakP400Round
KeccakP400Round:
    # Arguments:
    # - a0 - tKeccakLane * A
    # - a1 - unsigned int  roundIndex

    #
    # Theta function preparation
    la  a2, theta_c                         # a2 = &theta_c
    mv  a3, a0                              # a3 = &A
    addi a4, a2, 10                         # a4 = &theta_c[5]

    .theta_prep:
        
        xc.ld.hu   c0,(0), 0 (a3)           # t0 = A[x+5*y], y = 0
        xc.ld.hu   c0,(1), 10(a3)           # t0 = A[x+5*y], y = 1
        xc.ld.hu   c1,(0), 20(a3)           # t0 = A[x+5*y], y = 2
        xc.ld.hu   c1,(1), 30(a3)           # t0 = A[x+5*y], y = 3
        xc.ld.hu   c2,(0), 40(a3)           # t0 = A[x+5*y], y = 4

        xc.bop     c0, c1, c2, 0b10010110    # XOR3
        xc.pbyte   c1, c0, 2,3,2,3
        xc.bop     c0, c0, c1, 0x66          # XOR2

        xc.st.h    c0,(0), 0(a2)            # C[x] = t0
        
        addi    a3, a3, 2
        addi    a2, a2, 2
        bltu    a2, a4, .theta_prep

    la      a7, rho_off
    la      a6, temp_a
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    addi    a2, a2, -10                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0

        xc.sha3.x1 a3, t0, zero, 1          # a3 = (x+1)%5

        xc.ldr.hu c3(0), a2, a3            # c3 = theta_c[(x+1)%5]

        xc.prot.i h,c3, c3, 15              # c3 = theta_c[(x+1)%5]<<<1
        
        xc.sha3.x4 a3, t0, zero, 1          # a3 = (x+4)%5
        xc.ldr.hu c4(0), a2, a3             # t4 = theta_c[(x+4)%5]

        xc.bop  c6, c3, c4, 0x66            # c6 = D = c3 ^ c4
        
        .L1:

            xc.sha3.xy t5, t0, t1, 1        # t5 = (5*y)+x = index(x,y)

            xc.ldr.hu c4(0), t5, a0         # t4 = A[index(x,y)

            xc.bop  c3, c4, c6, 0x66        # c3 = A[index(x,y)] ^ D

            xc.ldr.hu c4(0), a7, t5         # t4 = A[index(x,y)]
            
            xc.prot h, c3, c3, c4

            xc.sha3.yx t4, t0, t1, 1

            xc.str.h c3(0), a6,t4            # a_temp[y + 5((2*x+3*y)%5)] = t3
            
            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L1
        
        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t2, 5

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:

            xc.sha3.xy t6, t0, t1, 1        # t6 = x + 5y
            xc.ldr.hu c5(0), t6, a6         # c5 =  a_temp[x+5y]
            
            xc.sha3.x1 t4, t0, t1, 1        # t4 = (x+1)%5 + 5y
            xc.ldr.hu c4(0), t4, a6         # c4 =  a_temp[(x+1)%5 + 5y]
            
            xc.sha3.x2 t4, t0, t1, 1        # t4 = (x+2)%5 + 5y
            xc.ldr.hu c3(0), t4, a6         # c3 =  a_temp[(x+2)%5 + 5y]
            
            xc.bop  c3, c4, c5, 0b10011010  # c3 = (c3 & (~c4)) ^ c5

            xc.str.h c3(0), a0, t6          # A[x+5y] = t3
            
            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L3

    # Iota
    la      t0, round_consts
    slli    a2, a1, 1
    add     t1, t0, a2              # t0 = &round_consts[a1]

    xc.ld.hu c2,(0), 0(a0)          # c1 = A[index(0,0)]
    xc.ld.hu c3,(0), 0(t1)          # c2 = round_consts[a1]

    xc.bop  c4, c2, c3, 0x66        # c4 = A[index(0,0)] ^ round_consts[a1]
    xc.st.h c4,(0), 0(a0)           # A[index(0,0)] = c4

    ret

.endfunc
