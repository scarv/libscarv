

.section .text
.global mpn_mul
mpn_mul:
    # a0 = limb_t * r
    # a1 = limb_t * x
    # a2 = int      l_x
    # a3 = limb_t * y
    # a4 = int      l_y
    
    # Auxilliary storage on the stack.
    addi        sp, sp, -4          # sp = end of aux array R

    # How long will the result be?
    add     t0, a2, a4              # t0 = l_x + l_y
    beqz    t0, .mpn_mul_finish     # if len=0, finish
    
    # Clear the auxiliary result array
    slli    t1, t0, 2               # t1 = size in bytes of R
    sub     t2, sp, t1              # t2 = start of R
    .clear_r:
        sw      zero, 0(t2)         # r[t2] = 0
        addi    t2, t2, 4           # r ++
        blt     t2, sp, .clear_r
    sub     t2, sp, t1              # t2 = start of aux array R

    # Start computation loop
    beqz    a4, .mpn_mul_finish
    mv      t0, zero                # t0 = outer loop counter

    slli    t5, a4, 2               # Word aligned l_y
    slli    t6, a2, 2               # Word aligned l_x

    .mpn_mul_outer:
        
        beqz a2, .mpn_mul_outer_finish
        mv          t1, zero                # t1 = inner loop counter
        xc.gpr2xcr  c7, zero                # C  = 0
            
        # Load inputs to MUL function
        add     t3, t0, a3              #          
        xc.ld.w c2, 0(t3)               # c2 = y[j]
        
        .mpn_mul_inner:

            # Load inputs to MUL function
            add     t3, t1, a1              #
            xc.ld.w c3, 0(t3)               # c3 = x[i]

            add     t3, t0, t1              # t3 = i+j = t0+t1
            add     t3, t3, t2              # t3 = addr of R[i+j]
            xc.ld.w c4, 0(t3)               # c4 = R[j+i]

            # Compute (y[i] * x[i]) + R[i+j] + C
            xc.mmul.3 (c6,c7), c2, c3, c7
            xc.macc.1 (c6,c7), c4

            # Store results back to carry and aux Result array
            xc.st.w c6, 0(t3)               # R[j+i] = low word 

            addi    t1, t1, 4
            blt     t1, t6, .mpn_mul_inner  # if(i(t1) < l_x) goto inner loop

        .mpn_mul_outer_finish:

        # R[j+l_x] = c
        add     t3, t0, t6
        add     t3, t3, t2                  # t3 = addr of R[j+l_x]
        xc.st.w c7, 0(t3)                   # R[j+l_x] = C

        addi    t0, t0, 4
        blt     t0, t5, .mpn_mul_outer      # if(j(t0) < l_y) goto outer loop

    .mpn_mul_finish:

    # Copy aux R array into result array
    mv  t0, t2          # src
    mv  t1, a0          # dst
    add t3, a2, a4
    mv  t4, zero

    .mpn_cpy_back:

        xc.ld.w  c14, 0(t0)
        xc.st.w  c14, 0(t1)
        
        addi t0, t0, 4
        addi t1, t1, 4
        addi t4, t4, 1

        blt  t4, t3, .mpn_cpy_back
    
    addi        sp, sp, 4
    ret

