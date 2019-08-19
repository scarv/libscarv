// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

.macro AES_LDM M0 M1 M2 M3 ADDR
  lw \M0, 0x0(\ADDR)
  lw \M1, 0x4(\ADDR)
  lw \M2, 0x8(\ADDR)
  lw \M3, 0xC(\ADDR)
.endm

.macro AES_STM M0 M1 M2 M3 ADDR
  sw \M0, 0x0(\ADDR)
  sw \M1, 0x4(\ADDR)
  sw \M2, 0x8(\ADDR)
  sw \M3, 0xC(\ADDR)
.endm

.macro AES_ENC_RND_KEY S0 S1 S2 S3 K0 K1 K2 K3
  xor  \S0, \S0, \K0
  xor  \S1, \S1, \K1
  xor  \S2, \S2, \K2
  xor  \S3, \S3, \K3
.endm

.macro AES_DEC_RND_KEY S0 S1 S2 S3 K0 K1 K2 K3
  xor  \S0, \S0, \K0
  xor  \S1, \S1, \K1
  xor  \S2, \S2, \K2
  xor  \S3, \S3, \K3
.endm
