
.section .text
.global aes_enc_rnd_mix
aes_enc_rnd_mix:
    # a0 =  uint32_t * s 

	mv   t6, zero
	li	 t6, 0xFFFF0000
	srli t5, t6, 16

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

	xc.aesmix.enc c4, c0, c1
	xc.aesmix.enc c5, c1, c0
	xc.aesmix.enc c6, c2, c3
	xc.aesmix.enc c7, c3, c2

	xc.st.w c4, 0(a0)
	xc.st.w c5, 4(a0)
	xc.st.w c6, 8(a0)
	xc.st.w c7, 12(a0)

	ret
