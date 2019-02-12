.include "aes_macro.S"

.section .text
.global aes_enc
aes_enc:
// a0 =  uint32_t * r
// a1 =  uint32_t * m 
// a2 =  uint32_t * k
// a3 =	uint8_t * sbox	
// a4 =	uint8_t * mulx

#ifdef CONF_AES_ROUND_PACK

//load plaintext and key
AES_LDW_T_XC  c0,c1,c2,c3, c9,c10 a1
AES_LDW_XC  c4,c5,c6,c7, a2
		
//init round	
//key
AES_KEY_XC  c0,c1,c2,c3, c4,c5,c6,c7

//iterative rounds
li t1, 9
rnd_loop:
    addi a2, a2, 0x10
    //sub
    AES_ENC_SUB_XC  c0,c1,c2,c3, a3
    //row
    AES_ENC_ROW_XC  c0,c1,c2,c3
    //mix
    AES_ENC_MIX_XC  c4,c5,c6,c7, c0,c1,c2,c3, a4	
    //key
    AES_LDW_XC      c0,c1,c2,c3, a2
    AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	

    addi t1, t1, -1
    bgtz t1, rnd_loop
//final round
addi a2, a2, 0x10
//sub
AES_ENC_SUB_XC  c0,c1,c2,c3, a3
//row
AES_ENC_ROW_XC  c0,c1,c2,c3
//key
AES_LDW_XC      c4,c5,c6,c7, a2
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	
//store
AES_STW_T_XC    c0,c1,c2,c3, c9,c10 a0

#else

// AES_ROUND_UNPACK using XCRYPTO AES instructions ================

//load plaintext and key
AES_LDW_XC  c0,c1,c2,c3, a1
AES_LDW_XC  c4,c5,c6,c7, a2
		
//init round	
//key
AES_KEY_XC  c0,c1,c2,c3, c4,c5,c6,c7

//iterative rounds
li t1, 9
rnd_loop:
    addi a2, a2, 0x10
    // sub; row
    xc.aessub.enc  c4, c0, c1
    xc.aessub.enc  c5, c2, c3
    xc.aessub.enc  c6, c1, c2
    xc.aessub.enc  c7, c3, c0
    // mix; row
    xc.aesmix.enc  c0, c4, c5
    xc.aesmix.enc  c1, c6, c7
    xc.aesmix.enc  c2, c5, c4
    xc.aesmix.enc  c3, c7, c6
    // key	
    AES_LDW_XC     c4,c5,c6,c7, a2
    AES_KEY_XC     c0,c1,c2,c3, c4,c5,c6,c7

    addi t1, t1, -1
    bgtz t1, rnd_loop
//final round
addi a2, a2, 0x10
//sub; second row	
xc.aessub.enc  c4, c2, c3
xc.aessub.enc  c5, c3, c0
xc.aessub.enc  c6, c0, c1
xc.aessub.enc  c7, c1, c2
// third and fourth row
xc.ins         c1, c4, 0, 16
xc.ins         c2, c5, 0, 16
xc.ins         c4, c6, 0, 16
xc.ins         c5, c7, 0, 16
xc.ins         c6, c1, 0, 16
xc.ins         c7, c2, 0, 16
//key
AES_LDW_XC     c0,c1,c2,c3, a2
AES_KEY_XC     c0,c1,c2,c3, c4,c5,c6,c7
//store
AES_STW_XC     c0,c1,c2,c3, a0

#endif
ret
