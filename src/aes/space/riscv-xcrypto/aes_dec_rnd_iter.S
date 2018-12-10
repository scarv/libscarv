
.section .text
.global aes_dec_rnd_iter
aes_dec_rnd_iter:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k
	
#load 
	xc.ld.w c0,  0(a0)
	xc.ld.w c1,  4(a0)
	xc.ld.w c2,  8(a0)
	xc.ld.w c3, 12(a0)

#sub; second row
	xc.aessub.dec c4, c0, c3
	xc.aessub.dec c5, c1, c0
	xc.aessub.dec c6, c2, c1
	xc.aessub.dec c7, c3, c2

#key
	xc.ld.w c0,  0(a1)
	xc.ld.w c1,  4(a1)
	xc.ld.w c2,  8(a1)
	xc.ld.w c3, 12(a1)

	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

#mix
	xc.aesmix.dec c4, c0, c2
	xc.aesmix.dec c5, c1, c3
	xc.aesmix.dec c6, c2, c0
	xc.aesmix.dec c7, c3, c1

	xc.st.w c4, 0(a0)
	xc.st.w c5, 4(a0)
	xc.st.w c6, 8(a0)
	xc.st.w c7, 12(a0)

	ret
