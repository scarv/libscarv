
#
# Auxiliary storage 
.data
theta_c: .fill 10, 8, 0
theta_d: .fill 10, 8, 0
chi_aux: .fill 10, 8, 0
.align 8,0
temp_a : .fill 50, 8, 0
rho_off:
    .hword  0
    .hword  1
    .hword 14
    .hword 12
    .hword 11
    .hword  4
    .hword 12
    .hword  6
    .hword  7
    .hword  4
    .hword  3
    .hword 10
    .hword 11
    .hword  9
    .hword  7
    .hword  9
    .hword 13
    .hword 15
    .hword  5
    .hword  8
    .hword  2
    .hword  2
    .hword 13
    .hword  8
    .hword 14                                             
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
.if LIBSCARV_CONF_KECCAKP400_INDEX_FUNC == 1
mod5_lut:
    .hword 0 << 1# 0
    .hword 1 << 1# 1
    .hword 2 << 1# 2
    .hword 3 << 1# 3
    .hword 4 << 1# 4
    .hword 0 << 1# 5
    .hword 1 << 1# 6
    .hword 2 << 1# 7
    .hword 3 << 1# 8
    .hword 4 << 1# 9
    .hword 0 << 1# 10
    .hword 1 << 1# 11
    .hword 2 << 1# 12
    .hword 3 << 1# 13
    .hword 4 << 1# 14
    .hword 0 << 1# 15
    .hword 1 << 1# 16
    .hword 2 << 1# 17
    .hword 3 << 1# 18
    .hword 4 << 1# 19
    .hword 0 << 1# 20
    .hword 1 << 1# 21
    .hword 2 << 1# 22
    .hword 3 << 1# 23
    .hword 4 << 1# 24
    .hword 0 << 1# 25
.endif

.macro MOD5 A, B, C
    .if LIBSCARV_CONF_KECCAKP400_INDEX_FUNC==1
        add     \A, \A, \C
        lbu     \A, 0(\A)
    .else
        remu    \A, \A, \B
    .endif
.endm

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
    add a4, a2, 10                          # a4 = &theta_c[5]

    .theta_prep:
        
        lhu     t0, 0 (a3)                  # t0 = A[x+5*y], y = 0
        lhu     t1, 10(a3)                  # t0 = A[x+5*y], y = 1
        xor     t0, t0, t1                  #
        lhu     t1, 20(a3)                  # t0 = A[x+5*y], y = 2
        xor     t0, t0, t1                  #
        lhu     t1, 30(a3)                  # t0 = A[x+5*y], y = 3
        xor     t0, t0, t1                  #
        lhu     t1, 40(a3)                  # t0 = A[x+5*y], y = 4
        xor     t0, t0, t1                  #

        sh      t0, 0(a2)                   # C[x] = t0
        
        addi    a3, a3, 2
        addi    a2, a2, 2
        bltu    a2, a4, .theta_prep

    la      a7, rho_off
    la      a6, temp_a

    .if LIBSCARV_CONF_KECCAKP400_INDEX_FUNC
        la      a5, mod5_lut
    .endif

    li      t0, 0                           # t0 = x = 0
    li      t2, 10
    addi    a2, a2, -10                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0

        addi    a3, t0, 2                   # a3 = x+1
        MOD5    a3, t2, a5
        add     a3, a2, a3                  # a3 = &theta_c[(x+1)%5]
        lhu     t3, 0(a3)                   # t3 = theta_c[(x+1)%5]

        srli    t4, t3, 15
        slli    t3, t3, 1
        or      t3, t3, t4                  # t3 = theta_c[(x+1)%5]<<<1
        
        addi    a3, t0, 8                   # a3 = x+4
        MOD5    a3, t2, a5
        add     a3, a2, a3                  # a3 = &theta_c[(x+4)%5]
        lhu     t4, 0(a3)                   # t4 = theta_c[(x+4)%5]

        xor     t6, t3, t4                  # t6 = D = t3 ^ t4
        slli    t6, t6, 16
        srli    t6, t6, 16
        
        .L1:

            slli    t4, t1, 2               # t4 = 4*y
            add     t4, t4, t1              # t4 = 5*y
            add     t5, t4, t0              # t5 = (5*y)+x = index(x,y)
            add     t4, t5, a0              # t4 = &A[index(x,y)]
            lhu     t4, 0(t4)               # t4 = A[index(x,y)

            xor     t3, t4, t6              # t3 = A[index(x,y)] ^ D

            add     t4, a7, t5              # t4 = &RhoOffsets[index(x,y)]
            lhu     t4, 0 (t4)              # t4 = RhoOffsets[index(x,y)]
            
            sll     t5, t3, t4              # t5 = t3 << t4
            neg     t4, t4
            andi    t4, t4, 0xF
            srl     t4, t3, t4
            or      t3, t5, t4              # t3 = (A[index(x,y)]^D)<<<ROff...

            add     t4, t0, t0              # t4 = 2*x
            slli    t5, t1, 1               # t5 = 2*y
            add     t5, t5, t1              # t5 = 3*y
            add     t4, t4, t5              # t4 = 2*x + 3*y

            MOD5    t4, t2, a5

            slli    t5, t4, 2               # t5 = 4((2*x+3*y)%5)
            add     t4, t4, t5              # t4 = 5((2*x+3*y)%5)
            add     t4, t4, t1              # t4 = y + 5((2*x+3*y)%5)
            add     t4, t4, a6              # t4 = &a_temp[y + 5((2*x+3*y)%5)]
            
            sh      t3, 0(t4)               # a_temp[y + 5((2*x+3*y)%5)] = t3
            
            addi    t1, t1, 2               # y += 1
            bltu    t1, t2, .L1
        
        addi    t0, t0, 2                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    li      t0, 0                           # t0 = x = 0
    li      t2, 50
    li      t5, 10

    .L3:
        
        li      t1, 0                       # t1 = y = 0
            
        addi    t3, t0, 2                   # t3 = (x+1)
        MOD5    t3, t5, a5
            
        addi    a2, t0, 4                   # t4 = (x+2)
        MOD5    a2, t5, a5

        .L4:

            add     t6, t0, t1              # t6 = x + 5y
            add     t4, t6, a6              # t4 = &a_temp[x+5y]
            lhu     a7, 0(t4)               # a7 =  a_temp[x+5y]
            
            add     t4, t3, t1              # t3 = (x+1)%5 + 5y
            add     t4, t4, a6              # t3 = &a_temp[(x+1)%5 + 5y]
            lhu     a4, 0(t4)               # a4 =  a_temp[(x+1)%5 + 5y]
            
            add     t4, a2, t1              # t4 = (x+2)%5 + 5y
            add     t4, t4, a6              # t4 = &a_temp[(x+2)%5 + 5y]
            lhu     a3, 0(t4)               # a3 =  a_temp[(x+2)%5 + 5y]
            
            not     a4, a4
            and     a3, a3, a4
            xor     a3, a3, a7              #

            add     t4, a0, t6              # t4 = &A[x+5y]
            sh      a3, 0(t4)               # A[x+5y] = t3
            
            addi    t1, t1, 10              # y += 1
            bltu    t1, t2, .L4
        
        addi    t0, t0, 2                   # x += 1
        bltu    t0, t5, .L3

    # Iota
    la      t0, round_consts
    slli    a2, a1, 1
    add     t1, t0, a2              # t0 = &round_consts[a1]

    lhu     t2, 0(a0)               # t1 = A[index(0,0)]
    lhu     t3, 0(t1)               # t2 = round_consts[a1]

    xor     t4, t2, t3              # t1 = A[index(0,0)] ^ round_consts[a1]
    sh      t4, 0(a0)               # A[index(0,0)] = t1

    ret

.endfunc
