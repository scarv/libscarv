
.macro QR a,b,c,d
    xc.padd     w, \a, \a, \b               // a += b
    xc.bop         \d, \d, \a, 0b01100110   // d ^= a
    xc.prot.i   w, \d, \d, 32-16            // d <<< 16

    xc.padd     w, \c, \c, \d               // c += d
    xc.bop         \b, \b, \c, 0b01100110   // b ^= c
    xc.prot.i   w, \b, \b, 32-12            // b <<< 12

    xc.padd     w, \a, \a, \b               // a += b
    xc.bop         \d, \d, \a, 0b01100110   // d ^= a
    xc.prot.i   w, \d, \d, 32-8             // d <<< 8

    xc.padd     w, \c, \c, \d               // c += d
    xc.bop         \b, \b, \c, 0b01100110   // b ^= c
    xc.prot.i   w, \b, \b, 32-7             // b <<< 7
.endm

.macro FINAL a,b,IN,OUT,o
    xc.ld.w     \a , \o(\IN)
    xc.padd  w, \b , \b, \a
    xc.st.w     \b , \o(\OUT)      // output[ 1] = c1 
.endm

.func     chacha20_block
.global   chacha20_block
chacha20_block:
    // uint32 * a0 - output
    // uint32 * a1 - input

    xc.ld.w c0 , 0(a1)      // c0  = tmp[ 0]
    xc.ld.w c1 , 4(a1)      // c1  = tmp[ 1]
    xc.ld.w c2 , 8(a1)      // c2  = tmp[ 2]
    xc.ld.w c3 ,12(a1)      // c3  = tmp[ 3]
    xc.ld.w c4 ,16(a1)      // c4  = tmp[ 4]
    xc.ld.w c5 ,20(a1)      // c5  = tmp[ 5]
    xc.ld.w c6 ,24(a1)      // c6  = tmp[ 6]
    xc.ld.w c7 ,28(a1)      // c7  = tmp[ 7]
    xc.ld.w c8 ,32(a1)      // c8  = tmp[ 8]
    xc.ld.w c9 ,36(a1)      // c9  = tmp[ 9]
    xc.ld.w c10,40(a1)      // c10 = tmp[10]
    xc.ld.w c11,44(a1)      // c11 = tmp[11]
    xc.ld.w c12,48(a1)      // c12 = tmp[12]
    xc.ld.w c13,52(a1)      // c13 = tmp[13]
    xc.ld.w c14,56(a1)      // c14 = tmp[14]
    xc.ld.w c15,60(a1)      // c15 = tmp[15]

    li t0, 0
    li t1, 10

    .L0:

        QR c0 , c4 , c8 , c12
        QR c1 , c5 , c9 , c13
        QR c2 , c6 , c10, c14
        QR c3 , c7 , c11, c15

        QR c0 , c5 , c10, c15
        QR c1 , c6 , c11, c12
        QR c2 , c7 , c8 , c13
        QR c3 , c4 , c9 , c14

        addi t0, t0, 1
        bltu t0, t1, .L0

    xc.xcr2gpr  t0, c1
    xc.ld.w     c1, 0(a1)
    xc.padd  w, c0, c0, c1
    xc.st.w     c0, 0(a0)      // output[ 0] = c0 
    xc.gpr2xcr  c1, t0

    FINAL c0, c1 , a1, a0, 4
    FINAL c0, c2 , a1, a0, 8 // output[ 2] = c2 
    FINAL c0, c3 , a1, a0,12 // output[ 3] = c3 
    FINAL c0, c4 , a1, a0,16 // output[ 4] = c4 
    FINAL c0, c5 , a1, a0,20 // output[ 5] = c5 
    FINAL c0, c6 , a1, a0,24 // output[ 6] = c6 
    FINAL c0, c7 , a1, a0,28 // output[ 7] = c7 
    FINAL c0, c8 , a1, a0,32 // output[ 8] = c8 
    FINAL c0, c9 , a1, a0,36 // output[ 9] = c9 
    FINAL c0, c10, a1, a0,40 // output[10] = c10
    FINAL c0, c11, a1, a0,44 // output[11] = c11
    FINAL c0, c12, a1, a0,48 // output[12] = c12
    FINAL c0, c13, a1, a0,52 // output[13] = c13
    FINAL c0, c14, a1, a0,56 // output[14] = c14
    FINAL c0, c15, a1, a0,60 // output[15] = c15

    ret

.endfunc

