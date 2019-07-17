// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

.macro AES_LDM M0 M1 M2 M3 ADDR
  xc.ld.w \M0, 0x0(\ADDR)
  xc.ld.w \M1, 0x4(\ADDR)
  xc.ld.w \M2, 0x8(\ADDR)
  xc.ld.w \M3, 0xC(\ADDR)
.endm

.macro AES_STM M0 M1 M2 M3 ADDR
  xc.st.w \M0, 0x0(\ADDR)
  xc.st.w \M1, 0x4(\ADDR)
  xc.st.w \M2, 0x8(\ADDR)
  xc.st.w \M3, 0xC(\ADDR)
.endm

.macro AES_ENC_RND_KEY S0 S1 S2 S3 K0 K1 K2 K3
  xc.bop  \S0, \S0, \K0, 0x66
  xc.bop  \S1, \S1, \K1, 0x66
  xc.bop  \S2, \S2, \K2, 0x66
  xc.bop  \S3, \S3, \K3, 0x66
.endm

.macro AES_DEC_RND_KEY S0 S1 S2 S3 K0 K1 K2 K3
  xc.bop  \S0, \S0, \K0, 0x66
  xc.bop  \S1, \S1, \K1, 0x66
  xc.bop  \S2, \S2, \K2, 0x66
  xc.bop  \S3, \S3, \K3, 0x66
.endm
