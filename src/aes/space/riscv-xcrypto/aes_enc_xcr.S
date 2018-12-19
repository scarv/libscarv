.include "aes_macro.S"

.section .text
.global aes_enc
aes_enc:
# a0 =  uint32_t * r
# a1 =  uint32_t * m 
# a2 =  uint32_t * k
.ifdef CONF_AES_ROUND_PACK
# a3 =	uint8_t * sbox	
	.ifndef CONF_AES_ENC_XCRYPT	
		#load
		AES_LDW_RV	t0,t1,t2,t3,a1
		#init round	
		#key
		AES_KEY_RV 	t0,t1,t2,t3,t5,a2
		#store
		AES_STW_RV	t0,t1,t2,t3,a0
		#iterative rounds
		li s11, 9
		rnd_loop:
			addi a2, a2, 0x10
			#load & sub
			AES_ENC_SUB_RV 0,  1,   2,  3, t0, t5, a0, a3
			AES_ENC_SUB_RV 4,  5,   6,  7, t1, t5, a0, a3
			AES_ENC_SUB_RV 8,  9,  10, 11, t2, t5, a0, a3
			AES_ENC_SUB_RV 12, 13, 14, 15, t3, t5, a0, a3
			#row
			AES_ENC_ROW_RV	t0,t1,t2,t3,t5
			#mix
			AES_ENC_MIX_RV	t4,t5,t6,a7, t0,t1,t2,t3, a4,a5,a6
			#key
			AES_KEY_RV 	t4,t5,t6,a7,t0,a2
			#store
			AES_STW_RV	t4,t5,t6,a7,a0

			addi s11, s11, -1
			bgtz s11, rnd_loop

		#final round
		addi a2, a2, 0x10
		#load & sub
		AES_ENC_SUB_RV 0,  1,   2,  3, t0, t5, a0, a3
		AES_ENC_SUB_RV 4,  5,   6,  7, t1, t5, a0, a3
		AES_ENC_SUB_RV 8,  9,  10, 11, t2, t5, a0, a3
		AES_ENC_SUB_RV 12, 13, 14, 15, t3, t5, a0, a3
		#row
		AES_ENC_ROW_RV	t0,t1,t2,t3,t5
		#key
		AES_KEY_RV 	t0,t1,t2,t3,t5, a2
		#store
		AES_STW_RV	t0,t1,t2,t3, a0
	.else
	# a4 =	uint8_t * mulx
		#load plaintext and key
		AES_LDW_XC	c0,c1,c2,c3, a1
		AES_LDW_XC	c4,c5,c6,c7, a2
		
		#init round	
		#key
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7
		#iterative rounds
		li t1, 9
		rnd_loop:
			addi a2, a2, 0x10
			#sub
			AES_ENC_SUB_XC	c0,c1,c2,c3, a3
			#row
			AES_ENC_ROW_XC	c0,c1,c2,c3
			#mix
			AES_ENC_MIX_XC 	c4,c5,c6,c7, c0,c1,c2,c3, a4	
			#key
			AES_LDW_XC		c0,c1,c2,c3, a2
			AES_KEY_XC		c0,c1,c2,c3, c4,c5,c6,c7	

			addi t1, t1, -1
			bgtz t1, rnd_loop
		#final round
		addi a2, a2, 0x10
		#sub
		AES_ENC_SUB_XC	c0,c1,c2,c3, a3
		#row
		AES_ENC_ROW_XC	c0,c1,c2,c3
		#key
		AES_LDW_XC		c4,c5,c6,c7, a2
		AES_KEY_XC		c0,c1,c2,c3, c4,c5,c6,c7	
		#store
		AES_STW_XC 		c0,c1,c2,c3, a0
	.endif
.else	# AES_ROUND_UNPACK======================
	.ifdef CONF_AES_ENC_XCRYPT	
		#load plaintext and key
		AES_LDW_XC	c0,c1,c2,c3, a1
		AES_LDW_XC	c4,c5,c6,c7, a2
		
		#init round	
		#key
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7
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
			AES_LDW_XC	c4,c5,c6,c7, a2
			AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7

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
		AES_LDW_XC	c0,c1,c2,c3, a2
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7
		#store
		AES_STW_XC	c0,c1,c2,c3, a0
	.endif
.endif
ret
