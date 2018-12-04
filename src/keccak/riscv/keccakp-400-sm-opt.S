
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
        
        li  t1, 0               # C[x] = 0

        lhu t2, 0 (t6)           # load A[x+5*0]
        xor t1, t1, t2
        lhu t2, 10(t6)          # load A[x+5*1]
        xor t1, t1, t2
        lhu t2, 20(t6)          # load A[x+5*2]
        xor t1, t1, t2
        lhu t2, 30(t6)          # load A[x+5*3]
        xor t1, t1, t2
        lhu t2, 40(t6)          # load A[x+5*4]
        xor t1, t1, t2

        # t1  = A[x+0*y] ^ A[x+1*y] ^ A[x+2*y] ^ A[x+3*y] ^ A[x+4*y]

        sh  t1, 0(t0)           # C[x] = t1

        addi t0, t0, 2
        addi t6, t6, 2
        bltu t0, a3, .theta_0

    # Second loop
    li      t0, 0
    li      t1, 5
    mv      t3, a2

    .theta_1:
        
        addi    a3, t0, 1
        addi    a4, t0, 4
        remu    a3, a3, t1
        remu    a4, a4, t1
        slli    a3, a3, 1           
        slli    a4, a4, 1           
        add     a3, a3, a1          # a3 = &C[(x+1)%5]
        add     a4, a4, a1          # a4 = &C[(x+4)%5]

        lhu     a3, 0(a3)           # a3 =  C[(x+1)%5]
        lhu     a4, 0(a4)           # a4 =  C[(x+4)%5]

        srli    t2, a3, 15
        slli    a3, a3, 1
        xor     a3, a3, t2          # a3 = ROL16(C[(x+1)%5],1)

        xor     a3, a3, a4          # a3 = ROL16(C[(x+1)%5],1) ^ C[(x+4)%5]

        sh      a3, 0(t3)           # D[x] = a3
        
        addi    t3, t3, 2
        addi    t0, t0, 1
        bltu    t0, t1, .theta_1

    # third loop, inner unrolled
    
    li      a5, 0
    li      t1, 10

    .theta_2:
        
        add     t4, a5, a2      # t4 = &D[x]
        add     t3, a5, a0      # t3 = &A[x]

        lhu     t4, 0(t4)       # t4 = D[x]

        lhu     t5, 0(t3)       # t5 = A[x + (5*y)] y=0
        xor     t5, t5, t4      # t5 = t5 ^ D[x]
        sh      t5, 0(t3)

        lhu     t5, 10(t3)      # t5 = A[x + (5*y)] y=1
        xor     t5, t5, t4      # t5 = t5 ^ D[x]
        sh      t5, 10(t3)

        lhu     t5, 20(t3)      # t5 = A[x + (5*y)] y=2
        xor     t5, t5, t4      # t5 = t5 ^ D[x]
        sh      t5, 20(t3)

        lhu     t5, 30(t3)      # t5 = A[x + (5*y)] y=3
        xor     t5, t5, t4      # t5 = t5 ^ D[x]
        sh      t5, 0(t3)

        lhu     t5, 40(t3)      # t5 = A[x + (5*y)] y=4
        xor     t5, t5, t4      # t5 = t5 ^ D[x]
        sh      t5, 0(t3)

        addi    a5, a5, 2
        bltu    a5, t1, .theta_2
        

    ret
.endfunc
