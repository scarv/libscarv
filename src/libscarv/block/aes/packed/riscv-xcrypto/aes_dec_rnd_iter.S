#include "scarv/share/conf.h"
.include "aes_macro.S"

.section .text
.global aes_dec_rnd_iter
aes_dec_rnd_iter:
// a0 =  uint32_t * s 
// a1 =  uint32_t * k
// a2 =	uint8_t * sbox
// a3 =	uint8_t * mulx

#if LIBSCARV_CONF_AES_ROUND_PACK
//load
AES_LDW_XC      c0,c1,c2,c3, a0	
//sub
AES_DEC_SUB_XC  c0,c1,c2,c3, a2
//row
AES_DEC_ROW_XC  c0,c1,c2,c3	
//key
AES_LDW_XC      c4,c5,c6,c7, a1
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	
//mix
AES_DEC_MIX_XC  c4,c5,c6,c7, c0,c1,c2,c3, a3	
//store
AES_STW_XC      c4,c5,c6,c7, a0

#else
// AES_ROUND_UNPACK using XCRYPTO AES instructions ================
//load
AES_LDW_XC      c0,c1,c2,c3, a0	 
//sub// second row
xc.aessub.dec c4, c0, c3
xc.aessub.dec c5, c1, c0
xc.aessub.dec c6, c2, c1
xc.aessub.dec c7, c3, c2
//key
AES_LDW_XC      c0,c1,c2,c3, a1
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	 
//mix// row
xc.aesmix.dec c4, c0, c2
xc.aesmix.dec c5, c1, c3
xc.aesmix.dec c6, c2, c0
xc.aesmix.dec c7, c3, c1
//store
AES_STW_XC      c4,c5,c6,c7, a0

#endif
ret
