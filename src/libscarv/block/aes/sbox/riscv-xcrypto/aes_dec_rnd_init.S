.include "aes_macro.S"

.section .text
.global aes_dec_rnd_init
aes_dec_rnd_init:
# a0 =  uint32_t * s 
# a1 =  uint32_t * k

#load 
AES_LDW_XC  c0,c1,c2,c3, a0
AES_LDW_XC  c4,c5,c6,c7, a1
#key
AES_KEY_XC  c0,c1,c2,c3, c4,c5,c6,c7
#store
AES_STW_XC  c0,c1,c2,c3, a0
ret


