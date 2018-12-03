
.section .text
.global aes_enc_rnd_sub
aes_enc_rnd_sub:
    # a0 =  uint32_t * s 
	
	li 	 t5, 0x00FF00FF
	slli t6, t5, 8

	lw t1, 0(a0)
	lw t2, 4(a0)
	and t3, t1, t6
	and t4, t2, t6 
	and t1, t1, t5
	add t1, t1, t4  
	and t2, t2, t5
	add t2, t2, t3
	xc.gpr2xcr  c0, t1
	xc.gpr2xcr  c1, t2


	lw t1, 8(a0)
	lw t2, 12(a0)
	and t3, t1, t6
	and t4, t2, t6 
	and t1, t1, t5
	add t1, t1, t4  
	and t2, t2, t5
	add t2, t2, t3
	xc.gpr2xcr  c2, t1
	xc.gpr2xcr  c3, t2

	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c1, c0
	xc.aessub.enc c6, c2, c3
	xc.aessub.enc c7, c3, c2

	xc.xcr2gpr  t1, c4
	xc.xcr2gpr  t2, c5
	xc.xcr2gpr  t3, c6
	xc.xcr2gpr  t4, c7
	
	sw t1, 0(a0)
	sw t2, 4(a0)
	sw t3, 8(a0)
	sw t4, 12(a0)

#	xc.st.w c4, 0(a0)
#	xc.st.w c5, 4(a0)
#	xc.st.w c6, 8(a0)
#	xc.st.w c7, 12(a0)

	ret
