.include "aes_macro.S"

.ifdef CONF_AES_ROUND_PACK

.section .text
.global aes_enc
aes_enc:
# a0 =  uint32_t * r
# a1 =  uint32_t * m 
# a2 =  uint32_t * k
# a3 =	uint8_t * sbox	
# a4 =	uint8_t * mulx	

addi    sp,sp,-20
sw      s1,4(sp)
sw      s2,8(sp)
sw      s3,12(sp)
sw      s4,16(sp)

#load
AES_LDW_T_RV	t0,t1,t2,t3, a1, a0

#init round	
#key
AES_KEY_RV 	t0,t1,t2,t3,t5,a2
#store
AES_STW_RV	t0,t1,t2,t3,a0

#iterative rounds
li s1, 9
rnd_loop:
  addi a2, a2, 0x10
  #load & sub
  AES_ENC_SUB_RV  0,  1,   2,  3, t0, t5, a0, a3
  AES_ENC_SUB_RV  4,  5,   6,  7, t1, t5, a0, a3
  AES_ENC_SUB_RV  8,  9,  10, 11, t2, t5, a0, a3
  AES_ENC_SUB_RV  12, 13, 14, 15, t3, t5, a0, a3
  #row
  AES_ENC_ROW_RV  t0,t1,t2,t3,t5
  #mix
  AES_ENC_MIX_RV  t4,t5,t6,a7, t0,t1,t2,t3, s2,s3,s4
  #key
  AES_KEY_RV      t4,t5,t6,a7,t0,a2
  #store
  AES_STW_RV      t4,t5,t6,a7,a0

  addi s1, s1, -1
  bgtz s1, rnd_loop

#final round
addi a2, a2, 0x10
#load & sub
AES_ENC_SUB_RV  0,  1,   2,  3, t0, t5, a0, a3
AES_ENC_SUB_RV  4,  5,   6,  7, t1, t5, a0, a3
AES_ENC_SUB_RV  8,  9,  10, 11, t2, t5, a0, a3
AES_ENC_SUB_RV  12, 13, 14, 15, t3, t5, a0, a3
#row
AES_ENC_ROW_RV  t0,t1,t2,t3,t5
#key
AES_KEY_RV      t0,t1,t2,t3,t5, a2
#store
AES_STW_T_RV    t0,t1,t2,t3, a0

lw      s4,16(sp)
lw      s3,12(sp)
lw      s2,8(sp)
lw      s1,4(sp)
addi    sp,sp,20
ret

.endif
