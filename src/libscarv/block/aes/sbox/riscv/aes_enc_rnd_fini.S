.include "scarv/share/conf.h"
.include "aes_macro.S"

#ifdef CONF_AES_ROUND_PACK

.section .text
.global aes_enc_rnd_fini
aes_enc_rnd_fini:
// a0 =  uint32_t * s 
// a1 =  uint32_t * k
// a2 =	uint8_t * sbox
	
//load & sub
AES_ENC_SUB_RV  0,  1,   2,  3, t0, t5, a0, a2
AES_ENC_SUB_RV  4,  5,   6,  7, t1, t5, a0, a2
AES_ENC_SUB_RV  8,  9,  10, 11, t2, t5, a0, a2
AES_ENC_SUB_RV  12, 13, 14, 15, t3, t5, a0, a2
//row
AES_ENC_ROW_RV	t0,t1,t2,t3,t5
//key
AES_KEY_RV      t0,t1,t2,t3,t5,a1
//store
AES_STW_RV      t0,t1,t2,t3,a0
ret

#endif
