
.section .text
.global aes_enc
aes_enc:
    # a0 =  uint32_t * r
	# a1 =  uint32_t * m 
	# a2 =  uint32_t * k
	
	xc.ld.w c0, 0(a1)
	xc.ld.w c1, 4(a1)
	xc.ld.w c2, 8(a1)
	xc.ld.w c3, 12(a1)	

#init round	
	#load key
	xc.ld.w c4, 0(a2)
	xc.ld.w c5, 4(a2)
	xc.ld.w c6, 8(a2)
	xc.ld.w c7, 12(a2)
	#key
	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

#iterative rounds
	li t1, 9
rnd_loop:
	addi a2, a2, 0x10
	# sub; row
	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c2, c3
	xc.aessub.enc c6, c1, c2
	xc.aessub.enc c7, c3, c0
	# mix; row
	xc.aesmix.enc c0, c4, c5
	xc.aesmix.enc c1, c6, c7
	xc.aesmix.enc c2, c5, c4
	xc.aesmix.enc c3, c7, c6
	# key	
	xc.ld.w c4, 0(a2)
	xc.ld.w c5, 4(a2)
	xc.ld.w c6, 8(a2)
	xc.ld.w c7, 12(a2)
	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

	addi t1, t1, -1
	bgtz t1, rnd_loop

#final round
	addi a2, a2, 0x10
	# sub & second row	
	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c1, c2
	xc.aessub.enc c6, c2, c3
	xc.aessub.enc c7, c3, c0
	# third and fourth row
	xc.ext c1, c4, 16, 16
	xc.ext c2, c5, 16, 16
	xc.ld.hiu c0, 0xFFFF
	xc.ld.liu c0, 0x0000	
	xc.mix.l c4, c6, c0, 0
	xc.mix.l c5, c7, c0, 0
	xc.ins c6, c1, 16, 16
	xc.ins c7, c2, 16, 16
	#key
	xc.ld.w c0, 0(a2)
	xc.ld.w c1, 4(a2)
	xc.ld.w c2, 8(a2)
	xc.ld.w c3, 12(a2)
	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

	xc.st.w c0, 0(a0)
	xc.st.w c1, 4(a0)
	xc.st.w c2, 8(a0)
	xc.st.w c3, 12(a0)

	ret
