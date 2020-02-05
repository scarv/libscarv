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
// a6 = i
	
aes_dec: AES_LDM         t0, t1, t2, t3, a1

         addi a2, a2,  16 * 10
         AES_LDM         t4, t5, t6, a7, a2
         AES_DEC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7

         li a6, 9

.l0:     xc.aessub.dec   t4, t0, t3
         xc.aessub.dec   t5, t1, t0
         xc.aessub.dec   t6, t2, t1
         xc.aessub.dec   a7, t3, t2

         xc.aesmix.dec   t0, t4, t6
         xc.aesmix.dec   t1, t5, a7
         xc.aesmix.dec   t2, t6, t4
         xc.aesmix.dec   t3, a7, t5

         addi a2, a2, -16
         AES_LDM         t4, t5, t6, a7, a2
         AES_DEC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7

         addi a6, a6, -1
         bgtz a6, .l0

         li     a3, 0x0000FFFF
         li     a4, 0xFFFF0000

         xc.aessub.dec   t4, t2, t1
         xc.aessub.dec   t5, t3, t2
         xc.aessub.dec   t6, t0, t3
         xc.aessub.dec   a7, t1, t0

         //mv t0, t4
         //mv t1, t5
         //mv t2, t6
         //mv t3, a7

         and    a5, t6, a3          // a5 =  X, X, 0, 5
         and    a6, t4, a4          // a6 = 15,10, X, X
         or     t0, a5, a6          // t0 = 15,10, 0, 5

         and    a5, a7, a3          // a5 =  X, X, 4, 9
         and    a6, t5, a4          // a6 =  3,14, X, X
         or     t1, a5, a6

         and    a5, t4, a3          // a5 =  X, X, 8, 3
         and    a6, t6, a4          // a6 =  7, 2, X, X
         or     t2, a5, a6

         and    a5, t5, a3          // a5 =  X, X,12, 1
         and    a6, a7, a4          // a6 = 11, 6, X, X
         or     t3, a5, a6

         addi a2, a2, -16
         AES_LDM         t4, t5, t6, a7, a2
         AES_DEC_RND_KEY t0, t1, t2, t3, t4, t5, t6, a7

         AES_STM         t0, t1, t2, t3, a0

         ret

.endfunc
#endif
	
// ============================================================================	
