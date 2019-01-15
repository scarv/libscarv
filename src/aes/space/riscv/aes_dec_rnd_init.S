.include "aes_macro.S"

.ifdef CONF_AES_ROUND_PACK

.section .text
.global aes_dec_rnd_init
aes_dec_rnd_init:
# a0 =  uint32_t * s 
# a1 =  uint32_t * k

#load
AES_LDW_RV  t0,t1,t2,t3,a0
#key
AES_KEY_RV  t0,t1,t2,t3,t5,a1
#store
AES_STW_RV  t0,t1,t2,t3,a0
ret

.endif

