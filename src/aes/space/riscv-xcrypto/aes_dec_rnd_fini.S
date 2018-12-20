.include "aes_macro.S"

.section .text
.global aes_dec_rnd_fini
aes_dec_rnd_fini:
# a0 =  uint32_t * s 
# a1 =  uint32_t * k
.ifdef CONF_AES_ROUND_PACK
	# a2 =	uint8_t * sbox
	.ifndef CONF_AES_DEC_XCRYPT
		#load & sub
		AES_DEC_SUB_RV 0,  1,   2,  3, t0, t5, a0, a2
		AES_DEC_SUB_RV 4,  5,   6,  7, t1, t5, a0, a2
		AES_DEC_SUB_RV 8,  9,  10, 11, t2, t5, a0, a2
		AES_DEC_SUB_RV 12, 13, 14, 15, t3, t5, a0, a2
		#row
		AES_DEC_ROW_RV	t0,t1,t2,t3,t5
		#key
		AES_KEY_RV 		t0,t1,t2,t3,t5,a1
		#store
		AES_STW_RV		t0,t1,t2,t3,a0
	.else
		#load
		AES_LDW_XC		c0,c1,c2,c3, a0
		#sub
		AES_DEC_SUB_XC	c0,c1,c2,c3, a2
		#row
		AES_DEC_ROW_XC	c0,c1,c2,c3
		#key
		AES_LDW_XC		c4,c5,c6,c7, a1
		AES_KEY_XC		c0,c1,c2,c3, c4,c5,c6,c7	
		#store
		AES_STW_XC 		c0,c1,c2,c3, a0
	.endif
.else
	.ifdef CONF_AES_DEC_XCRYPT	
		#load 
		AES_LDW_XC	c0,c1,c2,c3, a0
		#sub; second row	
		xc.aessub.dec c4, c0, c3
		xc.aessub.dec c5, c1, c0
		xc.aessub.dec c6, c2, c1
		xc.aessub.dec c7, c3, c2
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
		AES_LDW_XC	c0,c1,c2,c3, a1
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7	
		#store
		AES_STW_XC 	c0,c1,c2,c3, a0
	.endif
.endif

ret
