#include "scarv/share/conf.h"
.include "aes_macro.S"
	
.section .text
.global aes_enc_exp_step
aes_enc_exp_step:
    # a0 = uint32_t * r
	# a1 = uint32_t * rk
	# a2 = uint8 rc
	
//load 
	xc.ld.w c0,  0(a1)
	xc.ld.w c1,  4(a1)
	xc.ld.w c2,  8(a1)
	xc.ld.w c3, 12(a1)
	xc.gpr2xcr  c8, a2

	xc.aessub.enc c4, c3, c3
	xc.pbyte   c4, c4, 1, 2, 3, 0
	xc.bop	c4, c4, c8, 0x66	#xor
	
	xc.bop	c4, c4, c0, 0x66	#xor
	xc.bop	c5, c4, c1, 0x66	#xor
	xc.bop	c6, c5, c2, 0x66	#xor
	xc.bop	c7, c6, c3, 0x66	#xor
	
	xc.st.w c4, 0(a0)
	xc.st.w c5, 4(a0)
	xc.st.w c6, 8(a0)
	xc.st.w c7, 12(a0)

	ret

