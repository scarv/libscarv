/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#
# Auxiliary storage 
.data

rho_off:
    .hword 64- 0
    .hword 64- 1
    .hword 64-62
    .hword 64-28
    .hword 64-27
    .hword 64-36
    .hword 64-44
    .hword 64- 6
    .hword 64-55
    .hword 64-20
    .hword 64- 3
    .hword 64-10
    .hword 64-43
    .hword 64-25
    .hword 64-39
    .hword 64-41
    .hword 64-45
    .hword 64-15
    .hword 64-21
    .hword 64- 8
    .hword 64-18
    .hword 64- 2
    .hword 64-61
    .hword 64-56
    .hword 64-14

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

    addi    sp, sp, -416
    sw      s4, 4(sp)
    sw      s5, 8(sp)
    sw      s2,12(sp)

    //  Setup xc.bop
    //  - b1 = 96 = a ^ b ^ c
    //  - b0 = 9A = a ^ (~b & c)
    lui     a2, 0x96D20
    csrw    uxcrypto, a2

    #
    # Theta function preparation
    addi a2, sp, 16                         # a2 = &theta_c
    mv  a3, a0                              # a3 = &A
    add a4, a2, 40                          # a4 = &theta_c[5]

    .theta_prep:
        
        lw      t0,   0(a3)
        lw      t1,  40(a3)
        lw      t2,  80(a3)
        xc.bop  t0, t1, t2, 1
        lw      t1, 120(a3)
        lw      t2, 160(a3)
        xc.bop  t0, t1, t2, 1
        
        lw      t2,   4(a3)
        lw      t3,  44(a3)
        lw      t1,  84(a3)
        xc.bop  t2, t1, t3, 1
        lw      t1, 124(a3)
        lw      t3, 164(a3)
        xc.bop  t2, t1, t3, 1

        sw      t0,   0(a2)
        sw      t2,   4(a2)
        
        addi    a3, a3, 8
        addi    a2, a2, 8
        bltu    a2, a4, .theta_prep


    la      a7, rho_off
    addi    a6, sp,  216                    # a6 = &tempa
    li      t0, 0                           # t0 = x = 0
    li      t2, 5
    addi    a2, a2, -40                     # a2 = &theta_c

    # Theta / Rho / Pi

    .L0:
        
        li      t1, 0                       # t1 = y = 0
        
        xc.sha3.x1 a3, t0, zero, 3          
        add     a3, a2, a3                  # a3 = &theta_c[(x+1)%5]

        lw      t3, 0(a3)                   # 
        lw      t4, 4(a3)                   # t4,t3 = theta_c[(x+1)%5]
        
        li      a3, 63
        xc.mror (t4,t3),t4,t3,a3
        
        xc.sha3.x4 a3, t0, zero, 3          
        add     a3, a2, a3                  # a3 = &theta_c[(x+4)%5]

        lw      t5, 0(a3)                   # 
        lw      t6, 4(a3)                   # t6,t5 = theta_c[(x+4)%5]

        xor     t5, t3, t5                  # t6,t5 = (theta_c[(x+1)%5]<<<1)^
        xor     t6, t4, t6                  #          theta_c[(x+4)%5]
        
        .L1:

            xc.sha3.xy t3, t0, t1, 3        # t3 = index(x,y)
            add     t4, t3, a0              # t4 = &A[index(x,y)]
            lw      a4, 0(t4)               # 
            lw      a5, 4(t4)               # a4,a5 = A[index(x,y)]

            xor     a4, a4, t5              # a4,a5 = A[index(x,y)] ^ D
            xor     a5, a5, t6              #

            srli    t4, t3, 3               # Halfword align index(x,y)
            xc.ldr.hu t4, a7(t4)            # t4 = rho_off[index(x,y)]
            
            xc.mror (a5,a4),a5,a4,t4

            #
            # Store a5,a4 back to tempA[index(y,2x+3y)]
            #  - t0 = x 
            #  - t1 = y
        
            xc.sha3.yx t3, t0, t1, 3
            add     t4, t3, a6              # t4 = &a_temp[5((2x+3y)%5)+y]

            sw      a4, 0(t4)               #   a5,a4
            sw      a5, 4(t4)               # a_temp[y + 5((2*x+3*y)%5)] =

            addi    t1, t1, 1               # y += 1
            bltu    t1, t2, .L1

        addi    t0, t0, 1                   # x += 1
        bltu    t0, t2, .L0
    
    # Chi
    
    addi    t2, a6, 4                       # t2 = a6+4
    addi    t3, a0, 4                       # t3 = a0+4
    li      t0, 0                           # t0 = x = 0
    li      t5, 5 

    .L3:
        
        li      t1, 0                       # t1 = y = 0

        .L4:
            
            xc.sha3.x1 t4, t0, t1, 1        # t4 = (((x+1)%5) + 5y) << 3

            xc.ldr.w   a4, a6(t4)           # a5,a4 =a_temp[((x+1)%5) + 5y] 
            xc.ldr.w   a5, t2(t4)           # 
            
            xc.sha3.x2 t4, t0, t1, 1        # t4 = (((x+2)%5) + 5y) << 3
            
            xc.ldr.w   s4, a6(t4)           # s5,s4 = a_temp[((x+2)%5) + 5y] 
            xc.ldr.w   s5, t2(t4)           # 
            
            xc.sha3.xy s2, t0, t1, 1        # s2 = index(xy)
            
            xc.ldr.w   t6, a6(s2)           # a7,t6 =a_temp[index(x,y)] 
            xc.ldr.w   a7, t2(s2)           # 

            xc.bop  t6, a4, s4, 0          //
            xc.bop  a7, a5, s5, 0          //
            
            xc.str.w   t6, a0(s2)           # A[t4] = a7,t6
            xc.str.w   a7, t3(s2)           # 
            
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
    addi    sp, sp, 416

    ret

.endfunc
