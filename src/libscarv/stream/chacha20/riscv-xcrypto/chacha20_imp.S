// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/stream/chacha20/chacha20_imp.h"

#include "macro.S"

// ============================================================================	

#if ( LIBSCARV_CONF_CHACHA20_BLOCK_EXTERN )	
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
	
chacha20_block: 

    addi    sp, sp, -32                    // Allocate stack space.

    sw      s0 , 0(sp)
    sw      s1 , 4(sp)
    sw      s2 , 8(sp)
    sw      s8 ,12(sp)
    sw      s9 ,16(sp)
    sw      s10,20(sp)
    sw      s11,24(sp)

    CHACHA20_LD s0 , a1,  0             // s0  = x[ 0]
    CHACHA20_LD s1 , a1,  4             // s1  = x[ 1]
    CHACHA20_LD s2 , a1,  8             // s2  = x[ 2]
    CHACHA20_LD t3 , a1, 12             // t3  = x[ 3]
    CHACHA20_LD t4 , a1, 16             // t4  = x[ 4]
    CHACHA20_LD t5 , a1, 20             // t5  = x[ 5]
    CHACHA20_LD t6 , a1, 24             // t6  = x[ 6]
    CHACHA20_LD a7 , a1, 28             // a7  = x[ 7]
    CHACHA20_LD s8 , a1, 32             // s8  = x[ 8]
    CHACHA20_LD s9 , a1, 36             // s9  = x[ 9]
    CHACHA20_LD s10, a1, 40             // s10 = x[10]
    CHACHA20_LD s11, a1, 44             // s11 = x[11]
    CHACHA20_LD a2 , a1, 48             // a2  = x[12]
    CHACHA20_LD a3 , a1, 52             // a3  = x[13]
    CHACHA20_LD a4 , a1, 56             // a4  = x[14]
    CHACHA20_LD a5 , a1, 60             // a5  = x[15]

    li      t1, 0                       // i  = 0
    li      t2, 10
    .L1:                                // for(i=0; i < 10; i++) {
        
        CHACHA20_QR s0, t4, s8 , a2
        CHACHA20_QR s1, t5, s9 , a3
        CHACHA20_QR s2, t6, s10, a4
        CHACHA20_QR t3, a7, s11, a5
        
        CHACHA20_QR s0, t5, s10, a5
        CHACHA20_QR s1, t6, s11, a2
        CHACHA20_QR s2, a7, s8 , a3
        CHACHA20_QR t3, t4, s9 , a4
        
        addi t1, t1, 1
        bltu t1, t2, .L1                // }
    
    CHACHA20_ST a6, s0 , a1, a0,  0
    CHACHA20_ST a6, s1 , a1, a0,  4
    CHACHA20_ST a6, s2 , a1, a0,  8
    CHACHA20_ST a6, t3 , a1, a0, 12
    CHACHA20_ST a6, t4 , a1, a0, 16
    CHACHA20_ST a6, t5 , a1, a0, 20
    CHACHA20_ST a6, t6 , a1, a0, 24
    CHACHA20_ST a6, a7 , a1, a0, 28
    CHACHA20_ST a6, s8 , a1, a0, 32
    CHACHA20_ST a6, s9 , a1, a0, 36
    CHACHA20_ST a6, s10, a1, a0, 40
    CHACHA20_ST a6, s11, a1, a0, 44
    CHACHA20_ST a6, a2 , a1, a0, 48
    CHACHA20_ST a6, a3 , a1, a0, 52
    CHACHA20_ST a6, a4 , a1, a0, 56
    CHACHA20_ST a6, a5 , a1, a0, 60

    lw      s0 , 0(sp)
    lw      s1 , 4(sp)
    lw      s2 , 8(sp)
    lw      s8 ,12(sp)
    lw      s9 ,16(sp)
    lw      s10,20(sp)
    lw      s11,24(sp)
    
    addi    sp, sp, 32                    // de-Allocate stack space.
            
ret

.endfunc
#endif
	
// ============================================================================	
