// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/block/aes/aes_enc_imp.h"

#include "macro.S"
	
// ============================================================================	

#if ( LIBSCARV_CONF_AES_ENC_EXTERN ) 
.section .text

.func    aes_enc
.global  aes_enc

// void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k );
//
// a0 =  uint8_t* r
// a1 =  uint8_t* m 
// a2 =  uint8_t* k
//
// a6 = i
	
aes_enc: AES_LDM         t0, t1, t2, t3, a1


         AES_LDM         t4, t5, t6, a7, a2
         AES_ENC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7

         li a6, 9

.l0:     xc.aessub.enc   t4, t0, t1
         xc.aessub.enc   t5, t2, t3
         xc.aessub.enc   t6, t1, t2
         xc.aessub.enc   a7, t3, t0
     
         xc.aesmix.enc   t0, t4, t5
         xc.aesmix.enc   t1, t6, a7
         xc.aesmix.enc   t2, t5, t4
         xc.aesmix.enc   t3, a7, t6

         addi a2, a2,  16
         AES_LDM         t4, t5, t6, a7, a2
         AES_ENC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7

         addi a6, a6, -1
         bgtz a6, .l0

         xc.aessub.enc   t4, t2, t3
         xc.aessub.enc   t5, t3, t0
         xc.aessub.enc   t6, t0, t1
         xc.aessub.enc   a7, t1, t2
    
         or              t1, t1, t4
         or              t2, t2, t5
         or              t4, t4, t6
         or              t5, t5, a7
         or              t6, t6, t1
         or              a7, a7, t2

         addi a2, a2,  16    
         AES_LDM         t0, t1, t2, t3, a2
         AES_ENC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7
    
         AES_STM         t0, t1, t2, t3, a0
    
         ret

.endfunc
#endif
	
// ============================================================================	
