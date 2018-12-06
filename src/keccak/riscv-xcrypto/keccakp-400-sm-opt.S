
#
# Auxiliary storage for theta function
.data
theta_c: .fill 10, 8, 0
theta_d: .fill 10, 8, 0

.text

.func KeccakP400_theta
.global KeccakP400_theta
KeccakP400_theta:
    # Arguments:
    # - a0 - tKeccakLane * A
    
    la      a1, theta_c
    la      a2, theta_d
    
    addi    a3, a1, 10          # End of theta_c
    addi    a4, a2, 10          # End of theta_d

    mv      t0, a1
    mv      t6, a0
    
    # First loop - inner loop unrolled
    .theta_0:
        
        xc.ld.hu    c0, (0), 0 (t6)          # load A[x+5*0]
        xc.ld.hu    c0, (1), 10(t6)          # load A[x+5*1]
        xc.ld.hu    c1, (0), 20(t6)          # load A[x+5*2]
        xc.ld.hu    c1, (1), 30(t6)          # load A[x+5*3]
        xc.ld.hu    c2, (0), 40(t6)          # load A[x+5*4]
        
        xc.bop      c0, c0, c1, 0x6          # XOR
        xc.bop      c0, c0, c2, 0x6          # XOR
        xc.pperm.w  c1, c0, 2,3,2,3
        xc.bop      c0, c0, c1, 0x6          # XOR

        # t1  = A[x+0*y] ^ A[x+1*y] ^ A[x+2*y] ^ A[x+3*y] ^ A[x+4*y]

        xc.st.h     c0,(0), 0(t0)           # C[x] = t1

        addi t0, t0, 2
        addi t6, t6, 2
        bltu t0, a3, .theta_0

    # Second loop
    li      t0, 0
    li      t1, 10
    mv      t3, a2

    .theta_1:
        
        addi    a3, t0, 2
        addi    a4, t0, 8
        remu    a3, a3, t1
        remu    a4, a4, t1
        add     a3, a3, a1          # a3 = &C[(x+1)%5]
        add     a4, a4, a1          # a4 = &C[(x+4)%5]
 
        xc.ld.hu  c0,(0), 0(a3)     # a3 =  C[(x+1)%5]
        xc.ld.hu  c1,(0), 0(a4)     # a4 =  C[(x+4)%5]
        xc.prot.i h, c0, c0, 15     # c0 = ROL16(C[(x+1)%5],1)
        xc.bop    c0, c0, c1, 0x6   # a3 = ROL16(C[(x+1)%5],1) ^ C[(x+4)%5]
        xc.st.h   c0, (0), 0(t3)    # D[x] = a3
        
        addi    t3, t3, 2
        addi    t0, t0, 2
        bltu    t0, t1, .theta_1

    # third loop, inner unrolled
    
    li      a5, 0
    li      t1, 10

    .theta_2:
        
        add     t4, a5, a2      # t4 = &D[x]
        add     t3, a5, a0      # t3 = &A[x]

        xc.ld.hu    c0,(0), 0(t4)   # c1 = D[x]
        xc.pperm.w  c0, c0, 0,1,0,1

        xc.ld.hu c1,(0), 0(t3)       # c1 = A[x + (5*y)] y=0
        xc.ld.hu c1,(1), 10(t3)      # c1 = A[x + (5*y)] y=1
        xc.bop   c1, c1, c0, 0x6     # c1 = c1 ^ D[x]
        xc.st.h  c1,(0), 0(t3)
        xc.st.h  c1,(1), 10(t3)
        
        xc.ld.hu c1,(0), 20(t3)      # c1 = A[x + (5*y)] y=2
        xc.ld.hu c1,(1), 30(t3)      # c1 = A[x + (5*y)] y=3
        xc.bop   c1, c1, c0, 0x6    # c1 = c1 ^ D[x]
        xc.st.h  c1,(0), 20(t3)
        xc.st.h  c1,(1), 30(t3)
        
        xc.ld.hu c1,(0), 40(t3)      # c1 = A[x + (5*y)] y=4
        xc.bop   c1, c1, c0, 0x6    # c1 = c1 ^ D[x]
        xc.st.h  c1,(0), 40(t3)

        addi    a5, a5, 2
        bltu    a5, t1, .theta_2
        

    ret
.endfunc


#
# Auxiliary storage for rho function
.data
rho_offsets:
.hword 16- 0
.hword 16- 1
.hword 16-14
.hword 16-12
.hword 16-11
.hword 16- 4
.hword 16-12
.hword 16- 6
.hword 16- 7
.hword 16- 4
.hword 16- 3
.hword 16-10
.hword 16-11
.hword 16- 9
.hword 16- 7
.hword 16- 9
.hword 16-13
.hword 16-15
.hword 16- 5
.hword 16- 8
.hword 16- 2
.hword 16- 2
.hword 16-13
.hword 16- 8
.hword 16-14

.text

.func KeccakP400_rho
.global KeccakP400_rho
KeccakP400_rho:
    # Arguments:
    # - a0 - tKeccakLane * A
    
    la  a1, rho_offsets
    li  t0, 0
    li  t2, 10
    li  a6, 50

    .rho_0:
    
        li  t1, 0

        .rho_1:
        
            add  t3, t1, t0         # t3 = x + 5*y

            add  t5, a0, t3         # t5 = &A[x+5y]
            add  t6, a1, t3         # t6 = &rho_offsets[x+5y]

            xc.ld.hu  c2, (0), 0(t5)          # c2 = A[x+5y]
            xc.ld.hu  c3, (0), 0(t6)          # c3 = rho_offsets[x+5y]

            xc.prot   h, c2, c2, c3

            xc.st.h   c2,(0), 0(t5)
            
            addi  t1, t1, 10
            bltu  t1, a6, .rho_1
        
        addi t0, t0, 2
        bltu t0, t2, .rho_0

    ret
.endfunc


#
# Auxiliary storage for pi function
.data
pi_aux:
.fill 50, 8, 0

.text

.func KeccakP400_pi
.global KeccakP400_pi
KeccakP400_pi:
    # Arguments:
    # - a0 - tKeccakLane * A
    
    mv   t0, a0
    addi t1, t0, 50
    la   t2, pi_aux

    .pi_0:                          # Copy A to pi_aux
        xc.ld.hu c3, (0), 0(t0)
        xc.st.h  c3, (0), 0(t2)
        xc.ld.hu c3, (0), 2(t0)
        xc.st.h  c3, (0), 2(t2)
        xc.ld.hu c3, (0), 4(t0)
        xc.st.h  c3, (0), 4(t2)
        xc.ld.hu c3, (0), 6(t0)
        xc.st.h  c3, (0), 6(t2)
        xc.ld.hu c3, (0), 8(t0)
        xc.st.h  c3, (0), 8(t2)

        addi t0, t0, 10
        addi t2, t2, 10
        bltu t0, t1, .pi_0

    li t0, 0                            # t0 = x = 0
    li t2, 5
    li a6, 10
    la t6, pi_aux

    .pi_1:
        li t1, 0                        # t1 = y = 0
        li a7, 0                        # a7 = 10y = 0

        .pi_2:
            
            add      t4, a7, t0          # t4 = x+5y
            add      t4, t4, t6          # t4 = &pi_aux[x+5y]
            xc.ld.hu c5, (0), 0(t4)           # t5 = pi_aux[x+5y]

            # compute index(0*x+1*y, 2*x+3*y)
            #       = index(      y, 2*x+3*y)
            #       =         y + 5*((2*x+3*y) %5)

            slli    t4, t1, 1           # t4 = 2y
            add     t4, t4, t1          # t4 = 3y
            add     t4, t4, t0          # t4 = 2x + 3y
            remu    t4, t4, t2          # t4 = (2x + 3y) % 5
            mul     t4, t4, t2          # t4 = 5*((2x + 3y)%5)
            add     t4, t4, t1          # t4 = y + 5*((2x + 3y)%5)
            slli    t4, t4, 1
            add     t4, t4, a0          # t4 = &A[y + 5*((2x + 3y)%5)]
            
            xc.st.h c5, (0), 0(t4)
            
            addi    a7, a7, 10
            addi    t1, t1, 1
            bltu    t1, t2, .pi_2
        
        addi    t0, t0, 2
        bltu    t0, a6, .pi_1
    
    ret
.endfunc



#
# Auxiliary storage for chi function
.data
chi_aux:
.fill 10, 8, 0

.text

.func KeccakP400_chi
.global KeccakP400_chi
KeccakP400_chi:
    # Arguments:
    # - a0 - tKeccakLane * A

    la  a1, chi_aux
    
    li  t0, 0                           # y = 0
    li  t2, 10
    li  t3, 50

    .chi_0:
        
        li t1, 0                        # x = 0
        .chi_1:

            addi    a3, t1, 2           # a3 = (x+1)
            addi    a4, t1, 4           # a4 = (x+2)

            remu    a3, a3, t2          # a3 = (x+1) % 5
            remu    a4, a4, t2          # a4 = (x+2) % 5
            
            add     a2, t0, t1          # a2 = x+5y
            add     a3, a3, t0          # a3 = ((x+1)%5) + 5y
            add     a4, a4, t0          # a4 = ((x+2)%5) + 5y

            add     a2, a2, a0          # a2 = &A[index(x  , y)]
            add     a3, a3, a0          # a3 = &A[index(x+1, y)]
            add     a4, a4, a0          # a4 = &A[index(x+2, y)]

            xc.ld.hu c0,(0), 0(a2)          # c0 =  A[index(x  , y)]
            xc.ld.hu c1,(0), 0(a3)          # c1 =  A[index(x+1, y)]
            xc.ld.hu c2,(0), 0(a4)          # c2 =  A[index(x+2, y)]

            xc.bop  c1, c1, c2, 2       # c1 = ~c1 & c2
            xc.bop  c0, c0, c1, 6       # c0 = c0 ^ c1

            add     t6, t1, a1          # t6 = &chi_aux[x]
            xc.st.h c0, (0), 0(t6)           # chi_aux[x] = t4 ^ (~t5 & t6)

            addi    t1, t1, 2
            bltu    t1, t2, .chi_1

        li t1, 0                        # x = 0
        .chi_2:
            
            add      t6, t1, a1         # t6 = &chi_aux[x]
            xc.ld.hu c0, (0), 0(t6)          # t6 =  chi_aux[x]

            add      t6, t1, t0         # t6 = x+5y
            add      t6, t6, a0         # t6 = &A[index(x,y)]
            xc.st.h  c0, (0), 0(t6)          # A[index(x,y)] = chi_aux[x]
            
            addi    t1, t1, 2
            bltu    t1, t2, .chi_2

        addi t0, t0, 10
        bltu t0, t3, .chi_0

    ret

.endfunc
