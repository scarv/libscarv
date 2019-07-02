.macro AES_LDW_XC XD0 XD1 XD2 XD3 SP
	xc.ld.w \XD0, 0(\SP)
	xc.ld.w \XD1, 4(\SP)
	xc.ld.w \XD2, 8(\SP)
	xc.ld.w \XD3, 12(\SP)
.endm

.macro AES_LDW_T_XC XD0 XD1 XD2 XD3 XT0 XT1 SP
    xc.ld.liu   \XT0, 0x0400
    xc.ld.hiu   \XT0, 0x0C08
    xc.ld.liu   \XT1, 0x0101
    xc.ld.hiu   \XT1, 0x0101
    xc.gather.b \XD0, \XT0, \SP
    xc.padd   b,\XT0, \XT0, \XT1
    xc.gather.b \XD1, \XT0, \SP
    xc.padd   b,\XT0, \XT0, \XT1
    xc.gather.b \XD2, \XT0, \SP
    xc.padd   b,\XT0, \XT0, \XT1
    xc.gather.b \XD3, \XT0, \SP
.endm

.macro AES_STW_XC XS0 XS1 XS2 XS3 SP
	xc.st.w \XS0, 0(\SP)
	xc.st.w \XS1, 4(\SP)
	xc.st.w \XS2, 8(\SP)
	xc.st.w \XS3, 12(\SP)
.endm

.macro AES_STW_T_XC XD0 XD1 XD2 XD3 XT0 XT1 SP
    xc.ld.liu    \XT0, 0x0400
    xc.ld.hiu    \XT0, 0x0C08
    xc.ld.liu    \XT1, 0x0101
    xc.ld.hiu    \XT1, 0x0101
    xc.scatter.b \XD0, \XT0, \SP
    xc.padd    b,\XT0, \XT0, \XT1
    xc.scatter.b \XD1, \XT0, \SP
    xc.padd    b,\XT0, \XT0, \XT1
    xc.scatter.b \XD2, \XT0, \SP
    xc.padd    b,\XT0, \XT0, \XT1
    xc.scatter.b \XD3, \XT0, \SP
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
	xc.pbyte   \XS1, \XS1, 1, 2, 3, 0
	xc.pbyte   \XS2, \XS2, 2, 3, 0, 1
	xc.pbyte   \XS3, \XS3, 3, 0, 1, 2

.endm
.macro AES_DEC_ROW_XC XS0 XS1 XS2 XS3 
	xc.pbyte  \XS1, \XS1, 3, 0, 1, 2
	xc.pbyte  \XS2, \XS2, 2, 3, 0, 1
	xc.pbyte  \XS3, \XS3, 1, 2, 3, 0
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

.macro X0R3_XC XD XS1 XS2 XS3
	xc.bop	\XD, \XS1, \XS2, 0x66	#xor
	xc.bop	\XD, \XD,  \XS3, 0x66	#xor
.endm
