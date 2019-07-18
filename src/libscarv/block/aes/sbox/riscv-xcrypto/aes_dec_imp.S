// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/block/aes/aes_dec_imp.h"

#include "macro.S"
	
// ============================================================================	

#if ( LIBSCARV_CONF_AES_DEC_EXTERN )	
.section .text

.func    aes_dec
.global  aes_dec

// void aes_dec( uint8_t* r, uint8_t* c, uint8_t* k );
//
// a0 =  uint8_t* r
// a1 =  uint8_t* c
// a2 =  uint8_t* k
//
// t0 = i
	
aes_dec: AES_LDM         c0, c1, c2, c3, a1

         addi a2, a2,  16 * 10
         AES_LDM         c4, c5, c6, c7, a2
         AES_DEC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7

         li t0, 9

.l0:     xc.aessub.dec   c4, c0, c3
         xc.aessub.dec   c5, c1, c0
         xc.aessub.dec   c6, c2, c1
         xc.aessub.dec   c7, c3, c2

         xc.aesmix.dec   c0, c4, c6
         xc.aesmix.dec   c1, c5, c7
         xc.aesmix.dec   c2, c6, c4
         xc.aesmix.dec   c3, c7, c5

         addi a2, a2, -16
         AES_LDM         c4, c5, c6, c7, a2
         AES_DEC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7

         addi t0, t0, -1
         bgtz t0, .l0

         xc.aessub.dec   c4, c2, c1
         xc.aessub.dec   c5, c3, c2
         xc.aessub.dec   c6, c0, c3
         xc.aessub.dec   c7, c1, c0

         xc.ins          c1, c4, 0, 16
         xc.ins          c2, c5, 0, 16
         xc.ins          c4, c6, 0, 16
         xc.ins          c5, c7, 0, 16
         xc.ins          c6, c1, 0, 16
         xc.ins          c7, c2, 0, 16

         addi a2, a2, -16
         AES_LDM         c0, c1, c2, c3, a2
         AES_DEC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7

         AES_STM         c0, c1, c2, c3, a0
         
         ret

.endfunc
#endif
	
// ============================================================================	
