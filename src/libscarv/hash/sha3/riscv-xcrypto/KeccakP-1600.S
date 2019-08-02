
#
# Auxiliary storage 
.data

theta_c: .fill 40, 8, 0

.align 8,0
temp_a : .fill 200, 8, 0

rho_off:
    .hword 64 -  0
    .hword 64 -  1
    .hword 64 - 62
    .hword 64 - 28
    .hword 64 - 27
    .hword 64 - 36
    .hword 64 - 44
    .hword 64 -  6
    .hword 64 - 55
    .hword 64 - 20
    .hword 64 -  3
    .hword 64 - 10
    .hword 64 - 43
    .hword 64 - 25
    .hword 64 - 39
    .hword 64 - 41
    .hword 64 - 45
    .hword 64 - 15
    .hword 64 - 21
    .hword 64 -  8
    .hword 64 - 18
    .hword 64 -  2
    .hword 64 - 61
    .hword 64 - 56
    .hword 64 - 14

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

    addi    sp, sp, -16
    sw      s4, 4(sp)
    sw      s5, 8(sp)
    sw      s2,12(sp)

    #
    # Theta function preparation
    la  a2, theta_c                         # a2 = &theta_c
    mv  a3, a0                              # a3 = &A
    add a4, a2, 40                          # a4 = &theta_c[5]

    .theta_prep:
        
        lw      t0,   0(a3)
        lw      t1,  40(a3)
        lw      t2,  80(a3)
        xor     t0, t0, t1
        lw      t1, 120(a3)
        xor     t0, t0, t2
        lw      t2, 160(a3)
        xor     t0, t0, t1
        xor     t0, t0, t2
        
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
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    addi    a2, a2, -40                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        xc.sha3.x1 a3, a3, zero, 3          # a3 = (x+1)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+1)%5]

        lw      t3, 0(a3)                   # 
        lw      t4, 4(a3)                   # t4,t3 = theta_c[(x+1)%5]

        li      t5, 64-1
        xc.mror (t4,t3), t4, t3, t5         # t4,t3 = theta_c[(x+1)%5] << 1
        
        xc.sha3.x4 a3, a3, zero, 3          # a3 = (x+4)%5
        add     a3, a2, a3                  # a3 = &theta_c[(x+4)%5]

        lw      t5, 0(a3)                   # 
        lw      t6, 4(a3)                   # t6,t5 = theta_c[(x+4)%5]

        xor     t5, t4, t5                  # t6,t5 = (theta_c[(x+1)%5]<<<1)^
        xor     t6, t3, t6                  #          theta_c[(x+4)%5]
        
        .L1:

            xc.sha3.xy t3, t0, t1, 3        # t3 = index(x,y)

            add     t4, t3, a0              # t4 = &A[index(x,y)]
            lw      a4, 0(t4)               # 
            lw      a5, 4(t4)               # a5,a4 = A[index(x,y)]

            xor     a4, a4, t5              # a5,a4 = A[index(x,y)] ^ D
            xor     a5, a5, t6              #

            srli    t4, t3, 2               # Halfword align index(x,y)
            xc.ldr.hu t4, a7(t4)            # t4 = rho_off[index(x,y)]

            xc.mror (a5,a4), a5, a4, t4

            #
            # Store a5,a4 back to tempA[index(y,2x+3y)]
            #  - t0 = x 
            #  - t1 = y
        
            xc.sha3.yx t3, t0, t1, 3
            add     t4, t3, a6              # t4 = &a_temp[5((2x+3y)%5)+y]

            sw      a5, 0(t4)               # a5,a4
            sw      a4, 4(t4)               # a_temp[y + 5((2*x+3*y)%5)] =

            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L1

        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t5, 5 

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:
            
            xc.sha3.x1 t4, t0, t1, 3        # t4 = ((x+1)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+1)%5) + 5y]

            lw      a4, 0(t4)               # a5,a4 =a_temp[((x+1)%5) + 5y] 
            lw      a5, 4(t4)               # 
            
            xc.sha3.x2 t4, t0, t1, 3        # t4 = ((x+2)%5) + 5y
            add     t4, t4, a6              # t4 = &a_temp[((x+2)%5) + 5y]
            
            lw      s4, 0(t4)               # a5,a4 =a_temp[((x+2)%5) + 5y] 
            lw      s5, 4(t4)               # 

            not     a4, a4
            not     a5, a5

            and     s4, s4, a4              # s5,s4 = ~X & Y
            and     s5, s5, a5              #
            
            xc.sha3.xy s2, t0, t1, 3        # t4 = index(x,y)
            add     t4, s2, a6              # t4 = &a_temp[((x) + 5y]
            
            lw      a4, 0(t4)               # a5,a4 =a_temp[((x)) + 5y] 
            lw      a5, 4(t4)               # 
            
            xor     a4, s4, a4              # s5,s4 = ~X & Y
            xor     a5, s5, a5              #
            
            add     t4, s2, a0              # t4 = &A[((x) + 5y]
            
            sw      a4, 0(t4)               # A[t4] = a5,a4
            sw      a5, 4(t4)               # 
            
            addi    t1, t1, 1               # y += 1
            bltu    t1, t5, .L4
        
        addi    t0, t0, 1                   # x += 1
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

    lw      s4, 4(sp)
    lw      s5, 8(sp)
    lw      s2,12(sp)
    addi    sp, sp, 16

    ret

.endfunc