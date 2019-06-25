.macro AES_LDW_RV RD0 RD1 RD2 RD3 SP
	lw \RD0, 0(\SP)
	lw \RD1, 4(\SP)
	lw \RD2, 8(\SP)
	lw \RD3, 12(\SP)
.endm

.macro AES_CPY_RV RD0 RD1 RD2 RD3 SP0 SP1 B00 B01 B02 B03 B10 B11 B12 B13
    lbu \RD0,  \B00(\SP0)
    lbu \RD1,  \B01(\SP0)
    lbu \RD2,  \B02(\SP0)
    lbu \RD3,  \B03(\SP0)
    sb  \RD0,  \B10(\SP1)
    sb  \RD1,  \B11(\SP1)
    sb  \RD2,  \B12(\SP1)
    sb  \RD3,  \B13(\SP1) 
.endm

.macro AES_LDW_T_RV RD0 RD1 RD2 RD3 SP0 SP1
    AES_CPY_RV \RD0,\RD1,\RD2,\RD3, \SP0,\SP1,  0, 1, 2, 3, 0,4, 8,12
    AES_CPY_RV \RD0,\RD1,\RD2,\RD3, \SP0,\SP1,  4, 5, 6, 7, 1,5, 9,13
    AES_CPY_RV \RD0,\RD1,\RD2,\RD3, \SP0,\SP1,  8, 9,10,11, 2,6,10,14
    AES_CPY_RV \RD0,\RD1,\RD2,\RD3, \SP0,\SP1, 12,13,14,15, 3,7,11,15

	lw \RD0, 0(\SP1)
	lw \RD1, 4(\SP1)
	lw \RD2, 8(\SP1)
	lw \RD3, 12(\SP1)  
.endm

.macro AES_STW_T_RV RS0 RS1 RS2 RS3 SP
	sw \RS0, 0(\SP)
	sw \RS1, 4(\SP)
	sw \RS2, 8(\SP)
	sw \RS3, 12(\SP)

    AES_CPY_RV \RS0,\RS1,\RS2,\RS3, \SP,\SP,  1, 4, 2, 8,   4,1, 8, 2
    AES_CPY_RV \RS0,\RS1,\RS2,\RS3, \SP,\SP,  3,12, 6, 9,  12,3, 9, 6
    AES_CPY_RV \RS0,\RS1,\RS2,\RS3, \SP,\SP,  7,13,11,14,  13,7,14,11
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

