
.text


.global sparx_L_2    
.func   sparx_L_2    
//
// a0: uint16_t *
//
sparx_L_2:

    lhu t0, 0(a0)           // t0 = x[0]
    lhu t1, 2(a0)           // t1 = x[1]
    lhu t2, 4(a0)           // t2 = x[2]
    lhu t3, 6(a0)           // t3 = x[3]
    
    xor t4, t0, t1          // tmp = x[0] ^ x[1]
    xc.pror.i h, t4, t4, 8  // tmp = ROTL(tmp, 8)

    xc.bop t2, t0, t4, 0    // t2 = x[2] ^ x[0] ^ tmp
    xc.bop t3, t1, t4, 0    // t3 = x[3] ^ x[1] ^ tmp

    sh  t2, 0(a0)           // x[0] = x[2]
    sh  t3, 2(a0)           // x[1] = x[3]
    sh  t0, 4(a0)           // x[2] = x[0]
    sh  t1, 6(a0)           // x[3] = x[1]

ret
.endfunc


.global sparx_L_2_inv
.func   sparx_L_2_inv
//
// a0: uint16_t *
//
sparx_L_2_inv:

    lhu t0, 4(a0)           // x[0] = x[2]
    lhu t1, 6(a0)           // x[1] = x[3]
    lhu t2, 0(a0)           // x[2] = x[0]
    lhu t3, 2(a0)           // x[3] = x[1]
    
    xor t4, t0, t1          // tmp = x[0] ^ x[1]
    xc.pror.i h, t4, t4, 8  // tmp = ROTL(tmp, 8)
    
    xc.bop t2, t0, t4, 0    // t2 = x[2] ^ x[0] ^ tmp
    xc.bop t3, t1, t4, 0    // t3 = x[3] ^ x[1] ^ tmp
    
    sh  t0, 0(a0)           // t0 = x[0]
    sh  t1, 2(a0)           // t1 = x[1]
    sh  t2, 4(a0)           // t2 = x[2]
    sh  t3, 6(a0)           // t3 = x[3]

ret
.endfunc


.global sparx_L_4    
.func   sparx_L_4    
//
// a0: uint16_t *
//
sparx_L_4:

    lhu	t3,0(a0)            // t3 = x[0]
    lhu	t1,2(a0)            // t1 = x[1]
    lhu	a7,4(a0)            // a7 = x[2]
    lhu	a6,6(a0)            // a6 = x[3]
    
    xor	a4,t3,t1
    xc.bop a4, a6, a7, 0

    lhu	a3,14(a0)           // a3 = x[7]
    lhu	a1,10(a0)           // a1 = x[5]
    lhu	a2,12(a0)           // a2 = x[6]
    lhu	t4,8(a0)            // t4 = x[4]

    xc.pror.i h,a5,a4,8     // a5 = tmp

    xc.bop a3, a6, a5, 0
    xc.bop a1, t1, a5, 0
    xc.bop a2, t3, a5, 0
    xc.bop t4, a7, a5, 0

    sh	t4,0(a0)
    sh	a1,2(a0)
    sh	a2,4(a0)
    sh	a3,6(a0)
    sh	t3,8(a0)
    sh	t1,10(a0)
    sh	a7,12(a0)
    sh	a6,14(a0)

	ret
.endfunc


.global sparx_L_4_inv
.func   sparx_L_4_inv
//
// a0: uint16_t *
//
sparx_L_4_inv:

    lhu	t3,8(a0)
    lhu	t1,10(a0)
    lhu	a7,12(a0)
    lhu	a6,14(a0)

    xor	a4,t3,t1
    xc.bop a4, a6, a7, 0

    lhu	a3,4(a0)
    lhu	a1,0(a0)
    lhu	a2,2(a0)
    lhu	t4,6(a0)

    xc.pror.i h, a5, a4, 8

    xc.bop a3, t3, a5, 0
    xc.bop a1, a7, a5, 0
    xc.bop a2, t1, a5, 0
    xc.bop t4, a6, a5, 0

    sh	t3,0(a0)
    sh	t1,2(a0)
    sh	a7,4(a0)
    sh	a6,6(a0)
    sh	a1,8(a0)
    sh	a2,10(a0)
    sh	a3,12(a0)
    sh	t4,14(a0)

    ret
.endfunc

