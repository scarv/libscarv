#include "scarv/share/conf.h"
.include "aes_macro.S"

.extern AES_DEC_SBOX
.extern AES_MULX

.section .text
.global aes_dec
aes_dec:
// a0 =  uint32_t * r
// a1 =  uint32_t * c 
// a2 =  uint32_t * k
	
#if LIBSCARV_CONF_AES_ROUND_PACK

la a3, AES_DEC_SBOX
la a4, AES_MULX	
	
//load 
AES_LDW_T_XC	c0,c1,c2,c3, c9,c10, a1
// set key pointer from the end of array
addi a2, a2, 160
//init round
//load key
AES_LDW_XC      c4,c5,c6,c7, a2
//key
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7

//iterative rounds
li t1, 9
rnd_loop:
    addi a2, a2, -16			
    //sub
    AES_DEC_SUB_XC  c0,c1,c2,c3, a3
    //row
    AES_DEC_ROW_XC  c0,c1,c2,c3	
    //key
    AES_LDW_XC      c4,c5,c6,c7, a2
    AES_KEY_XC      c4,c5,c6,c7, c0,c1,c2,c3	
    //mix
    AES_DEC_MIX_XC  c0,c1,c2,c3, c4,c5,c6,c7, a4	
	
    addi t1, t1, -1
    bgtz t1, rnd_loop
//final round
addi a2, a2, -16
//sub
AES_DEC_SUB_XC  c0,c1,c2,c3, a3
//row
AES_DEC_ROW_XC  c0,c1,c2,c3
//key
AES_LDW_XC      c4,c5,c6,c7, a2
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	
//store
AES_STW_T_XC    c0,c1,c2,c3, c9,c10, a0

#else

// AES_ROUND_UNPACK using XCRYPTO AES instructions ================
//load 
AES_LDW_XC      c0,c1,c2,c3, a1
// set key pointer from the end of array
addi a2, a2, 160
//init round
//load key
AES_LDW_XC      c4,c5,c6,c7, a2
//key
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7

//iterative rounds
li t1, 9
rnd_loop:
    addi a2, a2, -16
    //sub; second row
    xc.aessub.dec c4, c0, c3
    xc.aessub.dec c5, c1, c0
    xc.aessub.dec c6, c2, c1
    xc.aessub.dec c7, c3, c2
    //key
    AES_LDW_XC    c0,c1,c2,c3, a2
    AES_KEY_XC    c4,c5,c6,c7, c0,c1,c2,c3
    //mix; row
    xc.aesmix.dec c0, c4, c6
    xc.aesmix.dec c1, c5, c7
    xc.aesmix.dec c2, c6, c4
    xc.aesmix.dec c3, c7, c5

    addi t1, t1, -1
    bgtz t1, rnd_loop
//final round
addi a2, a2, -16
//sub; second row	
xc.aessub.dec  c4, c2, c1
xc.aessub.dec  c5, c3, c2
xc.aessub.dec  c6, c0, c3
xc.aessub.dec  c7, c1, c0
// third and fourth row
xc.ins c1, c4, 0, 16
xc.ins c2, c5, 0, 16
xc.ins c4, c6, 0, 16
xc.ins c5, c7, 0, 16
xc.ins c6, c1, 0, 16
xc.ins c7, c2, 0, 16
//key
AES_LDW_XC     c0,c1,c2,c3, a2
AES_KEY_XC     c0,c1,c2,c3, c4,c5,c6,c7
//store
AES_STW_XC     c0,c1,c2,c3, a0

#endif
ret
