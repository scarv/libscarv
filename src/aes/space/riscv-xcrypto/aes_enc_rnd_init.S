.include "aes_macro.S"

.section .text
.global aes_enc_rnd_init
aes_enc_rnd_init:
# a0 =  uint32_t * s 
# a1 =  uint32_t * k
.ifdef CONF_AES_ROUND_PACK 
	.ifndef CONF_AES_ENC_XCRYPT
		#load
		AES_LDW_RV	t0,t1,t2,t3,a0
		#key
		AES_KEY_RV 	t0,t1,t2,t3,t5,a1
		#store
		AES_STW_RV	t0,t1,t2,t3,a0
	.else
		#load 
		AES_LDW_XC	c0,c1,c2,c3, a0
		AES_LDW_XC	c4,c5,c6,c7, a1
		#key
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7
		#store
		AES_STW_XC	c0,c1,c2,c3, a0
	.endif
.else
	.ifdef CONF_AES_ENC_XCRYPT
		#load 
		AES_LDW_XC	c0,c1,c2,c3, a0
		AES_LDW_XC	c4,c5,c6,c7, a1
		#key
		AES_KEY_XC	c0,c1,c2,c3, c4,c5,c6,c7
		#store
		AES_STW_XC	c0,c1,c2,c3, a0
	.endif
.endif
	ret

