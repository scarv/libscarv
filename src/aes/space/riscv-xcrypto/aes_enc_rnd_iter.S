
.section .text
.global aes_enc_rnd_iter
aes_enc_rnd_iter:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k
	
	xc.ld.w c0, 0(a0)
	xc.ld.w c1, 4(a0)
	xc.ld.w c2, 8(a0)
	xc.ld.w c3, 12(a0)
	
	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c2, c3
	xc.aessub.enc c6, c1, c2
	xc.aessub.enc c7, c3, c0
	
	xc.aesmix.enc c0, c4, c5
	xc.aesmix.enc c1, c6, c7
	xc.aesmix.enc c2, c5, c4
	xc.aesmix.enc c3, c7, c6

	xc.xcr2gpr  t1, c0
	xc.xcr2gpr  t2, c1
	xc.xcr2gpr  t3, c2
	xc.xcr2gpr  t4, c3

	lw t5, 0(a1)
	xor t1, t1, t5
	lw t5, 4(a1)
	xor t2, t2, t5
	lw t5, 8(a1)
	xor t3, t3, t5
	lw t5, 12(a1)
	xor t4, t4, t5

	sw t1, 0(a0)
	sw t2, 4(a0)
	sw t3, 8(a0)
	sw t4, 12(a0)

	ret
