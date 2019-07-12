// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/share/conf.h"
#include "macro.S"

// ============================================================================	

.section .text

.func    chacha20_block
.global  chacha20_block

// void chacha20_block( uint32_t* r, uint32_t* x );
//
// a0 = uint32_t* r
// a1 = uint32_t* x
//
// t0 = i	
// t1 = n = 10
	
chacha20_block: CHACHA20_LD c0,  a1,  0
                CHACHA20_LD c1,  a1,  4
                CHACHA20_LD c2,  a1,  8
                CHACHA20_LD c3,  a1, 12
                CHACHA20_LD c4,  a1, 16
                CHACHA20_LD c5,  a1, 20
                CHACHA20_LD c6,  a1, 24
                CHACHA20_LD c7,  a1, 28
                CHACHA20_LD c8,  a1, 32
                CHACHA20_LD c9,  a1, 36
                CHACHA20_LD c10, a1, 40
                CHACHA20_LD c11, a1, 44
                CHACHA20_LD c12, a1, 48
                CHACHA20_LD c13, a1, 52
                CHACHA20_LD c14, a1, 56
                CHACHA20_LD c15, a1, 60

                li t0,  0
                li t1, 10

.l0:            CHACHA20_QR c0, c4, c8,  c12
                CHACHA20_QR c1, c5, c9,  c13
                CHACHA20_QR c2, c6, c10, c14
                CHACHA20_QR c3, c7, c11, c15

                CHACHA20_QR c0, c5, c10, c15
                CHACHA20_QR c1, c6, c11, c12
                CHACHA20_QR c2, c7, c8,  c13
                CHACHA20_QR c3, c4, c9,  c14

                addi t0, t0, 1
                bltu t0, t1, .l0

                xc.xcr2gpr  t0, c1
                xc.ld.w     c1, 0(a1)
                xc.padd  w, c0, c0, c1
                xc.st.w     c0, 0(a0)    
                xc.gpr2xcr  c1, t0

                CHACHA20_ST c0, c1 , a1, a0,  4
                CHACHA20_ST c0, c2 , a1, a0,  8
                CHACHA20_ST c0, c3 , a1, a0, 12
                CHACHA20_ST c0, c4 , a1, a0, 16
                CHACHA20_ST c0, c5 , a1, a0, 20
                CHACHA20_ST c0, c6 , a1, a0, 24
                CHACHA20_ST c0, c7 , a1, a0, 28
                CHACHA20_ST c0, c8 , a1, a0, 32
                CHACHA20_ST c0, c9 , a1, a0, 36
                CHACHA20_ST c0, c10, a1, a0, 40
                CHACHA20_ST c0, c11, a1, a0, 44
                CHACHA20_ST c0, c12, a1, a0, 48
                CHACHA20_ST c0, c13, a1, a0, 52
                CHACHA20_ST c0, c14, a1, a0, 56
                CHACHA20_ST c0, c15, a1, a0, 60
            
                ret

.endfunc

// ============================================================================	
