
.text

#define N_STEPS 8
#define ROUNDS_PER_STEPS 3
#define N_BRANCHES 2

.global sparx_encrypt_64_128
.func
// void sparx_encrypt_64_128(uint16_t * x, uint16_t k[][2*3])
sparx_encrypt_64_128:

    // a0 - uint16_t x [6]
    // a1 - uint16_t k [16][6]
    
    mv      a2, a0          // For stepping through x
    mv      t2, a1          // For stepping through k

    li      t0, 0           // s = 0 = a0 = &k[0]
    li      t1, N_STEPS     //            = end of loop

    l_s:
        
        mv   t3, a0          // t3 = b = 0
        addi t4, t3, N_BRANCHES*4

        l_b:
            
            addi t6, t2, ROUNDS_PER_STEPS*2*2
            
            xc.ld.hu    c2,(0),0(t3) // c2 = twob = x[2*b  ]
            xc.ld.hu    c3,(0),2(t3) // c3 = twob1= x[2*b+1]

            l_r:
                
                xc.ld.hu    c0,(0),0(t2) // c0 = koff[2*r  ]
                xc.ld.hu    c1,(0),2(t2) // c3 = koff[2*r+1]

                xc.bop      c2, c2, c0, 0x66
                xc.bop      c3, c3, c1, 0x66

                xc.prot.i   h, c2, c2,16-9
                xc.padd     h, c2, c2, c3
                
                addi t2, t2, 4
                
                xc.prot.i   h, c3, c3,16-2
                xc.bop         c3, c3, c2, 0x66

                bltu t2, t6, l_r
            
            xc.st.h     c2,(0),0(t3) // c2 = twob = x[2*b  ]
            xc.st.h     c3,(0),2(t3) // c3 = twob1= x[2*b+1]

            addi t3, t3, 4
            bltu t3, t4, l_b

        xc.ld.hu  c0,(0),0(a0)
        xc.ld.hu  c1,(0),2(a0)
        // Don't need to load next two halfwords as they are
        // already in c2,c3 from the previous loops.

        xc.bop    c4, c0, c1, 0x66
        xc.prot.i h, c4, c4, 16-8

        xc.bop    c2, c0, c4, 0x96
        xc.bop    c3, c1, c4, 0x96
        
        addi t0, t0, 1          // 
        
        xc.st.h   c0, (0), 4(a0)
        xc.st.h   c1, (0), 6(a0)
        xc.st.h   c2, (0), 0(a0)
        xc.st.h   c3, (0), 2(a0)

        bltu t0, t1, l_s        // 
    
    xc.ld.hu  c4,(0),192(a1)
    xc.ld.hu  c5,(0),194(a1)
    xc.ld.hu  c6,(0),196(a1)
    xc.ld.hu  c7,(0),198(a1)

    xc.bop    c4, c2, c4, 0x66
    xc.bop    c5, c3, c5, 0x66
    xc.bop    c6, c0, c6, 0x66
    xc.bop    c7, c1, c7, 0x66
        
    xc.st.h   c4, (0), 0(a0)
    xc.st.h   c5, (0), 2(a0)
    xc.st.h   c6, (0), 4(a0)
    xc.st.h   c7, (0), 6(a0)

    ret

.endfunc
