.include "aes_macro.S"

.section .text
.global aes_enc_rnd_iter
aes_enc_rnd_iter:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k

.ifdef CONF_AES_ROUND_PACK
	# a2 =	uint8_t * sbox
	.ifndef CONF_AES_ENC_XCRYPT
		#load & sub
		AES_ENC_SUB_RV 0,  1,   2,  3, t0, t5, a0, a2
		AES_ENC_SUB_RV 4,  5,   6,  7, t1, t5, a0, a2
		AES_ENC_SUB_RV 8,  9,  10, 11, t2, t5, a0, a2
		AES_ENC_SUB_RV 12, 13, 14, 15, t3, t5, a0, a2
		#row
		AES_ENC_ROW_RV	t0,t1,t2,t3,t5
		#mix
		X0R3_RV 		t4, t1, t2, t3
		X0R3_RV 		t5, t0, t2, t3
		X0R3_RV 		t6, t0, t1, t3
		X0R3_RV 		a7, t0, t1, t2
		AES_MULX_PACKED_RV  t0, t0 
		AES_MULX_PACKED_RV  t1, t1
		AES_MULX_PACKED_RV  t2, t2
		AES_MULX_PACKED_RV  t3, t3		
		X0R3_RV 		t4, t4, t0, t1
		X0R3_RV 		t5, t5, t1, t2
		X0R3_RV 		t6, t6, t2, t3
		X0R3_RV 		a7, a7, t3, t0	
		#key
		AES_KEY_RV 		t4,t5,t6,a7,t0,a1
		#store
		AES_STW_RV		t4,t5,t6,a7,a0
	.else
		# a3 =	uint8_t * mulx
		#load
		AES_LDW_XC		c0,c1,c2,c3, a0	
		#sub
		AES_ENC_SUB_XC	c0,c1,c2,c3, a2
		#row
		AES_ENC_ROW_XC	c0,c1,c2,c3
		#mix
		X0R3_XC 		c4,c1,c2,c3
		X0R3_XC 		c5,c0,c2,c3
		X0R3_XC 		c6,c0,c1,c3
		X0R3_XC 		c7,c0,c1,c2
		AES_MULX_PACKED_XC c0,c1,c2,c3 a3
		X0R3_XC 		c4,c4,c0,c1
		X0R3_XC 		c5,c5,c1,c2
		X0R3_XC 		c6,c6,c2,c3
		X0R3_XC 		c7,c7,c3,c0	
		#key
		AES_LDW_XC		c0,c1,c2,c3, a1
		AES_KEY_XC		c0,c1,c2,c3, c4,c5,c6,c7	
		#store
		AES_STW_XC 		c0,c1,c2,c3, a0
	.endif
.else
	.ifdef CONF_AES_ENC_XCRYPT
		#load
		AES_LDW_XC		c0,c1,c2,c3, a0	
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
		AES_LDW_XC		c4,c5,c6,c7, a1
		AES_KEY_XC		c0,c1,c2,c3, c4,c5,c6,c7	
		#store
		AES_STW_XC		c0,c1,c2,c3, a0
	.endif
.endif
	ret
