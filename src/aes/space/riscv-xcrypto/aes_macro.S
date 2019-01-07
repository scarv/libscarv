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

.macro AES_DEC_SUB_RV B0 B1 B2 B3 RD RT SP SBOX
	AES_ENC_SUB_RV \B0,\B1,\B2,\B3,\RD,\RT,\SP,\SBOX
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

.macro AES_DEC_ROW_RV RS0 RS1 RS2 RS3 RT
	slli \RT,	\RS1, 	  8
	srli \RS1,	\RS1, 	 24 
	or 	 \RS1,	\RS1, 	\RT
	slli \RT,	\RS2, 	 16
	srli \RS2,	\RS2, 	 16
	or 	 \RS2,	\RS2, 	\RT
	slli \RT,	\RS3, 	 24
	srli \RS3,	\RS3, 	  8
	or 	 \RS3,	\RS3, 	\RT
.endm

.macro AES_ENC_MIX_RV RD0 RD1 RD2 RD3 RS0 RS1 RS2 RS3 MT0 MT1 MT2
	X0R3_RV 		\RD0, \RS1, \RS2, \RS3
	X0R3_RV 		\RD1, \RS0, \RS2, \RS3
	X0R3_RV 		\RD2, \RS0, \RS1, \RS3
	X0R3_RV 		\RD3, \RS0, \RS1, \RS2
	AES_MULX_PACKED_RV    \RS0, \RS0, \MT0,\MT1,\MT2 
	AES_MULX_PACKED_RV    \RS1, \RS1, \MT0,\MT1,\MT2
	AES_MULX_PACKED_RV    \RS2, \RS2, \MT0,\MT1,\MT2
	AES_MULX_PACKED_RV	  \RS3, \RS3, \MT0,\MT1,\MT2		
	X0R3_RV 		\RD0, \RD0, \RS0, \RS1
	X0R3_RV 		\RD1, \RD1, \RS1, \RS2
	X0R3_RV 		\RD2, \RD2, \RS2, \RS3
	X0R3_RV 		\RD3, \RD3, \RS3, \RS0	
.endm
.macro AES_DEC_MIX_RV RD0 RD1 RD2 RD3 RS0 RS1 RS2 RS3 MT0 MT1 MT2  
	AES_ENC_MIX_RV  \RD0, \RD1, \RD2, \RD3, \RS0, \RS1, \RS2, \RS3, \MT0,\MT1,\MT2
	xor	\RS0, \RS0, \RS2
	xor \RS1, \RS1, \RS3
	AES_MULX_PACKED_RV  \RS0, \RS0, \MT0,\MT1,\MT2 
	AES_MULX_PACKED_RV  \RS1, \RS1, \MT0,\MT1,\MT2 
	xor	\RD0, \RD0, \RS0
	xor \RD1, \RD1, \RS1
	xor	\RD2, \RD2, \RS0
	xor \RD3, \RD3, \RS1
	xor	\RS0, \RS0, \RS1
	AES_MULX_PACKED_RV  \RS0, \RS0, \MT0,\MT1,\MT2  
	xor	\RD0, \RD0, \RS0
	xor \RD1, \RD1, \RS0
	xor	\RD2, \RD2, \RS0
	xor \RD3, \RD3, \RS0
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
	xc.bop	\XS0, \XS0, \XK0, 0x66	#xor
	xc.bop	\XS1, \XS1, \XK1, 0x66	#xor
	xc.bop	\XS2, \XS2, \XK2, 0x66	#xor
	xc.bop	\XS3, \XS3, \XK3, 0x66	#xor
.endm

.macro AES_ENC_SUB_XC XS0 XS1 XS2 XS3 SBOX
	xc.gather.b \XS0, \XS0, \SBOX
	xc.gather.b \XS1, \XS1, \SBOX
	xc.gather.b \XS2, \XS2, \SBOX
	xc.gather.b \XS3, \XS3, \SBOX
.endm
.macro AES_DEC_SUB_XC XS0 XS1 XS2 XS3 SBOX
	AES_ENC_SUB_XC \XS0, \XS1, \XS2, \XS3, \SBOX
.endm

.macro AES_ENC_ROW_XC XS0 XS1 XS2 XS3 
	xc.pperm.w \XS1, \XS1, 1, 2, 3, 0
	xc.pperm.w \XS2, \XS2, 2, 3, 0, 1
	xc.pperm.w \XS3, \XS3, 3, 0, 1, 2

.endm
.macro AES_DEC_ROW_XC XS0 XS1 XS2 XS3 
	xc.pperm.w \XS1, \XS1, 3, 0, 1, 2
	xc.pperm.w \XS2, \XS2, 2, 3, 0, 1
	xc.pperm.w \XS3, \XS3, 1, 2, 3, 0
.endm

.macro AES_ENC_MIX_XC XD0 XD1 XD2 XD3 XS0 XS1 XS2 XS3 MULX
	X0R3_XC	\XD0, \XS1, \XS2, \XS3
	X0R3_XC	\XD1, \XS0, \XS2, \XS3
	X0R3_XC	\XD2, \XS0, \XS1, \XS3
	X0R3_XC	\XD3, \XS0, \XS1, \XS2
	xc.gather.b   \XS0, \XS0, \MULX
	xc.gather.b   \XS1, \XS1, \MULX
	xc.gather.b   \XS2, \XS2, \MULX
	xc.gather.b   \XS3, \XS3, \MULX
	X0R3_XC	\XD0, \XD0, \XS0, \XS1
	X0R3_XC	\XD1, \XD1, \XS1, \XS2
	X0R3_XC	\XD2, \XD2, \XS2, \XS3
	X0R3_XC	\XD3, \XD3, \XS3,  \XS0
.endm

.macro AES_DEC_MIX_XC XD0 XD1 XD2 XD3 XS0 XS1 XS2 XS3 MULX  
	AES_ENC_MIX_XC \XD0 \XD1 \XD2 \XD3 \XS0 \XS1 \XS2 \XS3 \MULX
	xc.bop	\XS0, \XS0, \XS2, 0x66	#xor
	xc.bop	\XS1, \XS1, \XS3, 0x66	#xor
	xc.gather.b   \XS0, \XS0, \MULX
	xc.gather.b   \XS1, \XS1, \MULX
	xc.bop	\XD0, \XD0, \XS0, 0x66	#xor
	xc.bop	\XD1, \XD1, \XS1, 0x66	#xor
	xc.bop	\XD2, \XD2, \XS0, 0x66	#xor
	xc.bop	\XD3, \XD3, \XS1, 0x66	#xor
	xc.bop	\XS0, \XS0, \XS1, 0x66	#xor
	xc.gather.b   \XS0, \XS0, \MULX
	xc.bop	\XD0, \XD0, \XS0, 0x66	#xor
	xc.bop	\XD1, \XD1, \XS0, 0x66	#xor
	xc.bop	\XD2, \XD2, \XS0, 0x66	#xor
	xc.bop	\XD3, \XD3, \XS0, 0x66	#xor
.endm

.macro AES_MULX_PACKED_RV RD RS	MT0 MT1 MT2
	li	 \MT2,  0x7f7f7f7f
	and  \MT0,	\RS, \MT2
	slli \MT0,	\MT0, 1
	
	li 	 \MT2,	0x80808080
	and	 \MT1,	\RS, \MT2
	
	#shift right 7 and multiply 0x1b
	srli \MT1,	\MT1, 3
	srli \MT2,	\MT1, 1
	or   \MT1,	\MT1, \MT2
	srli \MT2,	\MT1, 3
	or   \MT1,	\MT1, \MT2

	xor	 \RD,	\MT0, \MT1	
.endm

.macro X0R3_RV RD RS1 RS2 RS3
	xor	 \RD, \RS1, \RS2
	xor	 \RD, \RD,  \RS3
.endm

.macro X0R3_XC XD XS1 XS2 XS3
	xc.bop	\XD, \XS1, \XS2, 0x66	#xor
	xc.bop	\XD, \XD,  \XS3, 0x66	#xor
.endm
