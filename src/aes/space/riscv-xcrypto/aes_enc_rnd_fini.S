
.section .text
.global aes_enc_rnd_fini
aes_enc_rnd_fini:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k

# sub & second row	
	xc.ld.w c0, 0(a0)
	xc.ld.w c1, 4(a0)
	xc.ld.w c2, 8(a0)
	xc.ld.w c3, 12(a0)
	
	xc.aessub.enc c4, c0, c1
	xc.aessub.enc c5, c1, c2
	xc.aessub.enc c6, c2, c3
	xc.aessub.enc c7, c3, c0
	
# third and fourth row
	xc.ld.hiu c0, 0xFFFF
	xc.ld.liu c0, 0x0000
	
	xc.mix.l c1, c4, c0, 0
	xc.mix.l c2, c5, c0, 0

	xc.mix.l c4, c6, c0, 0
	xc.mix.l c5, c7, c0, 0
	xc.mix.l c6, c1, c0, 0
	xc.mix.l c7, c2, c0, 0

#key
	xc.ld.w c0, 0(a1)
	xc.ld.w c1, 4(a1)
	xc.ld.w c2, 8(a1)
	xc.ld.w c3, 12(a1)

	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

	xc.st.w c0, 0(a0)
	xc.st.w c1, 4(a0)
	xc.st.w c2, 8(a0)
	xc.st.w c3, 12(a0)

	ret
