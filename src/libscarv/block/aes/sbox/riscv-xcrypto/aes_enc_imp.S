// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/block/aes/aes_enc_imp.h"

#include "macro.S"
	
// ============================================================================	

.section .text

.func    aes_enc
.global  aes_enc

// void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k );
//
// a0 =  uint8_t* r
// a1 =  uint8_t* m 
// a2 =  uint8_t* k
//
// t0 = i
	
aes_enc: AES_LDM         c0, c1, c2, c3, a1


         AES_LDM         c4, c5, c6, c7, a2
         AES_ENC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7

         li t0, 9

.l0:     xc.aessub.enc   c4, c0, c1
         xc.aessub.enc   c5, c2, c3
         xc.aessub.enc   c6, c1, c2
         xc.aessub.enc   c7, c3, c0
     
         xc.aesmix.enc   c0, c4, c5
         xc.aesmix.enc   c1, c6, c7
         xc.aesmix.enc   c2, c5, c4
         xc.aesmix.enc   c3, c7, c6

         addi a2, a2,  16
         AES_LDM         c4, c5, c6, c7, a2
         AES_ENC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7

         addi t0, t0, -1
         bgtz t0, .l0

         xc.aessub.enc   c4, c2, c3
         xc.aessub.enc   c5, c3, c0
         xc.aessub.enc   c6, c0, c1
         xc.aessub.enc   c7, c1, c2
    
         xc.ins          c1, c4, 0, 16
         xc.ins          c2, c5, 0, 16
         xc.ins          c4, c6, 0, 16
         xc.ins          c5, c7, 0, 16
         xc.ins          c6, c1, 0, 16
         xc.ins          c7, c2, 0, 16

         addi a2, a2,  16    
         AES_LDM         c0, c1, c2, c3, a2
         AES_ENC_RND_KEY c0, c1, c2, c3, c4, c5, c6, c7
    
         AES_STM         c0, c1, c2, c3, a0
    
         ret

.endfunc
	
// ============================================================================	
