
.section .text
.global mpn_add
mpn_add:
    # a0 = limb_t * r
    # a1 = limb_t * x
    # a2 = int      l_x
    # a3 = limb_t * y
    # a4 = int      l_y
    mv      t1, a4
    bge     a4, a2, l_y_is_max
    mv      t1, a2

l_y_is_max:
    # t1 = MAX(l_x, l_y)
    li      t0, 0 
    # t0 = loop counter i.

    xc.gpr2xcr c3, zero
    # c3 = Carry out/in

    beqz    t1, mpn_add_done

mpn_add_x_loop:
    xc.gpr2xcr  c0, zero        #
    bgeu        t0, a2, .+8     #   c0 = i < l_x ? x[i] : 0
    xc.ld.w     c0, 0(a1)       #
    
    xc.gpr2xcr  c1, zero        #
    bgeu        t0, a4, .+8     #  c1 = i < l_y ? y[i] : 0
    xc.ld.w     c1, 0(a3)       #

    xc.madd.3   (c2,c3), c0, c1, c3

    addi        a1, a1, 4       # Increment source pointers
    addi        a3, a3, 4

    xc.st.w     c2, 0(a0)       # Store result back

    addi        t0, t0, 1       # Increment loop counter.
    addi        a0, a0, 0x4     # Increment result pointer.

    bltu        t0, t1, mpn_add_x_loop

mpn_add_done:
    xc.xcr2gpr  a0, c3          # Move a0 <= c3    
    ret

