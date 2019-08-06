
.text


.global sparx_L_2    
.func   sparx_L_2    
//
// a0: uint16_t *
//
sparx_L_2:

    lh  t0, 0(a0)           // t0 = x[0]
    lh  t1, 2(a0)           // t1 = x[1]
    lh  t2, 4(a0)           // t2 = x[2]
    lh  t3, 6(a0)           // t3 = x[3]
    
    xor t4, t0, t1          // tmp = x[0] ^ x[1]
    xc.pror.i h, t4, t4, 8  // tmp = ROTL(tmp, 8)

    xor t2, t2, t4
    xor t2, t0, t2          // t2 = x[2] ^ x[0] ^ tmp

    xor t3, t3, t4
    xor t3, t1, t3          // t3 = x[3] ^ x[1] ^ tmp

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

    lh  t0, 4(a0)           // x[0] = x[2]
    lh  t1, 6(a0)           // x[1] = x[3]
    lh  t2, 0(a0)           // x[2] = x[0]
    lh  t3, 2(a0)           // x[3] = x[1]
    
    xor t4, t0, t1          // tmp = x[0] ^ x[1]
    xc.pror.i h, t4, t4, 8  // tmp = ROTL(tmp, 8)
    
    xor t2, t2, t4
    xor t2, t0, t2          // t2 = x[2] ^ x[0] ^ tmp

    xor t3, t3, t4
    xor t3, t1, t3          // t3 = x[3] ^ x[1] ^ tmp
    
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

    lhu	t3,0(a0)
    lhu	t1,2(a0)
    lhu	a7,4(a0)
    lhu	a6,6(a0)
    
    xor	a4,t3,t1
    xor	a4,a7,a4
    xor	a4,a6,a4

    lhu	a3,14(a0)
    lhu	a1,10(a0)
    lhu	a2,12(a0)
    lhu	t4,8(a0)

    xc.pror.i h,a5,a4,8

    xor	a4,a6,a3
    xor	a1,t1,a1
    xor	a2,t3,a2
    xor	t4,a7,t4
    xor	a1,a1,a5
    xor	a3,a5,a2
    xor	a4,a4,a5
    xor	a5,a5,t4

    sh	a5,0(a0)
    sh	t3,8(a0)
    sh	a1,2(a0)
    sh	t1,10(a0)
    sh	a3,4(a0)
    sh	a7,12(a0)
    sh	a4,6(a0)
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
    xor	a4,a7,a4
    xor	a4,a6,a4

    lhu	a3,4(a0)
    lhu	a1,0(a0)
    lhu	a2,2(a0)
    lhu	t4,6(a0)

    xc.pror.i h,a5,a4,8

    xor	a4,t3,a3
    xor	a1,a7,a1
    xor	a2,t1,a2
    xor	t4,a6,t4
    xor	a1,a1,a5
    xor	a3,a5,a2
    xor	a4,a4,a5
    xor	a5,a5,t4

    sh	t3,0(a0)
    sh	t1,2(a0)
    sh	a7,4(a0)
    sh	a6,6(a0)
    sh	a1,8(a0)
    sh	a3,10(a0)
    sh	a4,12(a0)
    sh	a5,14(a0)

    ret
.endfunc

