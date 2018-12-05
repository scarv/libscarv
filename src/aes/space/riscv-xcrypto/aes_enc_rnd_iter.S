
.section .text
.global aes_enc_rnd_iter
aes_enc_rnd_iter:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k
	
	xc.ld.w c0, 0(a0)
	xc.ld.w c1, 4(a0)
	xc.ld.w c2, 8(a0)
	xc.ld.w c3, 12(a0)
# sub; row; mix	
	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c2, c3
	xc.aessub.enc c6, c1, c2
	xc.aessub.enc c7, c3, c0
	
	xc.aesmix.enc c0, c4, c5
	xc.aesmix.enc c1, c6, c7
	xc.aesmix.enc c2, c5, c4
	xc.aesmix.enc c3, c7, c6

# key
	xc.ld.w c4, 0(a1)
	xc.ld.w c5, 4(a1)
	xc.ld.w c6, 8(a1)
	xc.ld.w c7, 12(a1)

	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

	xc.st.w c0, 0(a0)
	xc.st.w c1, 4(a0)
	xc.st.w c2, 8(a0)
	xc.st.w c3, 12(a0)

	ret
