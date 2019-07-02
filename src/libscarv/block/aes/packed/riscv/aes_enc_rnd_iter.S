#include "scarv/share/conf.h"
.include "aes_macro.S"

#if LIBSCARV_CONF_AES_ROUND_PACK

.section .text
.global aes_enc_rnd_iter
aes_enc_rnd_iter:
// a0 =  uint32_t * s 
// a1 =  uint32_t * k
// a2 =	uint8_t * sbox
// a3 =	uint8_t * mulx

//load & sub
AES_ENC_SUB_RV 0,  1,   2,  3, t0, t5, a0, a2
AES_ENC_SUB_RV 4,  5,   6,  7, t1, t5, a0, a2
AES_ENC_SUB_RV 8,  9,  10, 11, t2, t5, a0, a2
AES_ENC_SUB_RV 12, 13, 14, 15, t3, t5, a0, a2
//row
AES_ENC_ROW_RV t0,t1,t2,t3,t5
//mix
AES_ENC_MIX_RV t4,t5,t6,a7, t0,t1,t2,t3, a4,a5,a6
//key
AES_KEY_RV     t4,t5,t6,a7,t0,a1
//store
AES_STW_RV     t4,t5,t6,a7,a0
ret

#endif
