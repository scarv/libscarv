
.section .text

#ifdef CONF_KERNELS_PRESENT_SLAYER_EXTERN
.global present_slayer
present_slayer:

    xc.gpr2xcr c0, a0
    xc.gpr2xcr c1, a1
    xc.gpr2xcr c2, zero
    xc.gpr2xcr c3, zero

    xc.bmv     c2, c0, 0 ,  0   
    xc.bmv     c2, c0, 1 , 16   
    xc.bmv     c3, c0, 2 , 32-32
    xc.bmv     c3, c0, 3 , 48-32
    xc.bmv     c2, c0, 4 ,  1   
    xc.bmv     c2, c0, 5 , 17   
    xc.bmv     c3, c0, 6 , 33-32
    xc.bmv     c3, c0, 7 , 49-32
                          
    xc.bmv     c2, c0, 8 ,  2   
    xc.bmv     c2, c0, 9 , 18   
    xc.bmv     c3, c0, 10, 34-32
    xc.bmv     c3, c0, 11, 50-32
    xc.bmv     c2, c0, 12,  3   
    xc.bmv     c2, c0, 13, 19   
    xc.bmv     c3, c0, 14, 35-32
    xc.bmv     c3, c0, 15, 51-32
                          
    xc.bmv     c2, c0, 16,  4   
    xc.bmv     c2, c0, 17, 20   
    xc.bmv     c3, c0, 18, 36-32
    xc.bmv     c3, c0, 19, 52-32
    xc.bmv     c2, c0, 20,  5   
    xc.bmv     c2, c0, 21, 21   
    xc.bmv     c3, c0, 22, 37-32
    xc.bmv     c3, c0, 23, 53-32
                          
    xc.bmv     c2, c0, 24,  6   
    xc.bmv     c2, c0, 25, 22   
    xc.bmv     c3, c0, 26, 38-32
    xc.bmv     c3, c0, 27, 54-32
    xc.bmv     c2, c0, 28,  7   
    xc.bmv     c2, c0, 29, 23   
    xc.bmv     c3, c0, 30, 39-32
    xc.bmv     c3, c0, 31, 55-32
                          
    xc.bmv     c2, c1, 0 ,  8   
    xc.bmv     c2, c1, 1 , 24   
    xc.bmv     c3, c1, 2 , 40-32
    xc.bmv     c3, c1, 3 , 56-32
    xc.bmv     c2, c1, 4 ,  9   
    xc.bmv     c2, c1, 5 , 25   
    xc.bmv     c3, c1, 6 , 41-32
    xc.bmv     c3, c1, 7 , 57-32
                          
    xc.bmv     c2, c1, 8 , 10   
    xc.bmv     c2, c1, 9 , 26   
    xc.bmv     c3, c1, 10, 42-32
    xc.bmv     c3, c1, 11, 58-32
    xc.bmv     c2, c1, 12, 11   
    xc.bmv     c2, c1, 13, 27   
    xc.bmv     c3, c1, 14, 43-32
    xc.bmv     c3, c1, 15, 59-32
                          
    xc.bmv     c2, c1, 16, 12   
    xc.bmv     c2, c1, 17, 28   
    xc.bmv     c3, c1, 18, 44-32
    xc.bmv     c3, c1, 19, 60-32
    xc.bmv     c2, c1, 20, 13   
    xc.bmv     c2, c1, 21, 29   
    xc.bmv     c3, c1, 22, 45-32
    xc.bmv     c3, c1, 23, 61-32
                          
    xc.bmv     c2, c1, 24, 14   
    xc.bmv     c2, c1, 25, 30   
    xc.bmv     c3, c1, 26, 46-32
    xc.bmv     c3, c1, 27, 62-32
    xc.bmv     c2, c1, 28, 15   
    xc.bmv     c2, c1, 29, 31   
    xc.bmv     c3, c1, 30, 47-32
    xc.bmv     c3, c1, 31, 63-32

    xc.xcr2gpr a0, c2
    xc.xcr2gpr a1, c3

    ret
#endif
