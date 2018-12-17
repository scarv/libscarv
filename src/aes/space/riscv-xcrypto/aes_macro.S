.macro AES_LDW_RV RD0 RD1 RD2 RD3 SP
	lw \RD0, 0(\SP)
	lw \RD1, 4(\SP)
	lw \RD2, 8(\SP)
	lw \RD3, 12(\SP)
.endm

.macro AES_STW_RV RS0 RS1 RS2 RS3 SP
	sw \RS0, 0(\SP)
	sw \RS1, 4(\SP)
	sw \RS2, 8(\SP)
	sw \RS3, 12(\SP)
.endm

.macro AES_KEY_RV RS0 RS1 RS2 RS3 RT RK
	lw 	\RT,  0(\RK)
	xor	\RS0, 	\RS0, \RT
	lw 	\RT,  4(\RK)
	xor \RS1,	\RS1, \RT
	lw 	\RT,  8(\RK)
	xor \RS2, 	\RS2, \RT
	lw 	\RT, 12(\RK)
	xor \RS3, 	\RS3, \RT
.endm

.macro AES_ENC_SUB_RV B0 B1 B2 B3 RD RT SP SBOX
	add 	\RD, zero, zero
	lbu		\RT, \B3(\SP)
	add 	\RT, \RT, \SBOX
	lbu		\RT, 0(\RT)
	or  	\RD, \RD, \RT	
	slli	\RD, \RD, 8

	lbu		\RT, \B2(\SP)
	add 	\RT, \RT, \SBOX
	lbu		\RT, 0(\RT)
	or  	\RD, \RD, \RT	
	slli	\RD, \RD, 8

	lbu		\RT, \B1(\SP)
	add 	\RT, \RT, \SBOX
	lbu		\RT, 0(\RT)
	or  	\RD, \RD, \RT	
	slli	\RD, \RD, 8

	lbu		\RT, \B0(\SP)
	add 	\RT, \RT, \SBOX
	lbu		\RT, 0(\RT)
	or  	\RD, \RD, \RT	
.endm

.macro AES_ENC_ROW_RV RS0 RS1 RS2 RS3 RT
	slli \RT,	\RS1, 	 24
	srli \RS1,	\RS1, 	  8
	or 	 \RS1,	\RS1, 	\RT
	slli \RT,	\RS2, 	 16
	srli \RS2,	\RS2, 	 16
	or 	 \RS2,	\RS2, 	\RT
	slli \RT,	\RS3, 	  8
	srli \RS3,	\RS3, 	 24
	or 	 \RS3,	\RS3, 	\RT
.endm

.macro AES_LDW_XC XD0 XD1 XD2 XD3 SP
	xc.ld.w \XD0, 0(\SP)
	xc.ld.w \XD1, 4(\SP)
	xc.ld.w \XD2, 8(\SP)
	xc.ld.w \XD3, 12(\SP)
.endm

.macro AES_STW_XC XS0 XS1 XS2 XS3 SP
	xc.st.w \XS0, 0(\SP)
	xc.st.w \XS1, 4(\SP)
	xc.st.w \XS2, 8(\SP)
	xc.st.w \XS3, 12(\SP)
.endm

.macro AES_KEY_XC XS0 XS1 XS2 XS3 XK0 XK1 XK2 XK3
	xc.bop	\XS0, \XS0, \XK0, 0x6		#xor
	xc.bop	\XS1, \XS1, \XK1, 0x6		#xor
	xc.bop	\XS2, \XS2, \XK2, 0x6		#xor
	xc.bop	\XS3, \XS3, \XK3, 0x6		#xor
.endm

.macro AES_MULX_PACKED_RV RD RS	
	li	 a6,  0x7f7f7f7f
	and  a4, \RS, a6
	slli a4,  a4, 1
	
	li 	 a6,  0x80808080
	and	 a5, \RS, a6
	
	#shift right 7 and multiply 0x1b
	srli a5,  a5, 3
	srli a6,  a5, 1
	or   a5,  a5, a6
	srli a6,  a5, 3
	or   a5,  a5, a6

	xor \RD,  a4, a5	
.endm

.macro AES_MULX_PACKED RD RS	
	li	 a6,  0x7f7f7f7f
	and  a4, \RS, a6
	li 	 a6,  0x80808080
	and	 a5, \RS, a6
	slli a4,  a4, 1
	srli a5,  a5, 7
	xc.gpr2xcr  c0, a5
	xc.gpr2xcr  c1, zero
	xc.psub 	b, c1, c1, c0
	xc.xcr2gpr	a5, c1
	li	 a6,  0x1b1b1b1b
	and  a5,  a5, a6
	xor \RD,  a4, a5	
.endm

.macro X0R3_RV RD RS1 RS2 RS3
	xor	 \RD, \RS1, \RS2
	xor	 \RD, \RD,  \RS3
.endm
