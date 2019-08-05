// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/mp/mpn/mpn_add_imp.h"

// ============================================================================	

#if ( LIBSCARV_CONF_MPN_ADD_EXTERN )	
.section .text

.func    mpn_add
.global  mpn_add

// limb_t mpn_add( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );
//
// a0 = limb_t *   r
// a1 = limb_t *   x
// a2 = int      l_x
// a3 = limb_t *   y
// a4 = int      l_y
//
// t0 =          l_r
// t1 =            i
//
// a6 =            r[ i ]  = s	
// a7 =                      c
// t4 =            x[ i ] ~= d_0
// t5 =            y[ i ] ~= d_1

#if ( LIBSCARV_CONF_MPN_ADD_GUARD  )
mpn_add: mv         t0, a2                 // l_r = l_x
         bltu       a4, a2, .l0            // if l_y <  l_x, goto .l0
         mv         t0, a4                 // l_r = l_y

.l0:     mv         a7, zero               // c = 0
	
         li         t1, 0                  // i = 0
         bgeu       t1, t0, .l5            // if i   >= l_r, goto .l5

.l1:     mv         t4, zero               // d_0 = 0
         bgeu       t1, a2, .l2            // if i   >= l_x, goto .l2
         xc.ldr.w   t4, a1(t1)             // d_0 = x[ i ]         
.l2:     mv         t5, zero               // d_1 = 0
         bgeu       t1, a4, .l3            // if i   >= l_y, goto .l3
         xc.ldr.w   t5, a3(t1)             // d_1 = y[ i ]
.l3:     xc.madd.3  ( a7, a6 ), t4, t5, a7 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   a6, a0(t1)             // r[ i ] = s

         addi       t1, t1, 1              // i = i + 1
         bltu       t1, t0, .l1            // if i   <  l_r, goto .l1

.l5:     mv         a0, a7                 // return c
         ret
#endif

#if ( LIBSCARV_CONF_MPN_ADD_UNROLL )
mpn_add: mv         t0, a2                 // l_r = l_x
         bltu       a2, a4, .l0            // if l_x <  l_y, goto .l0
         mv         t0, a4                 // l_r = l_y

.l0:     mv         a7, zero               // c = 0

         li         t1, 0                  // i = 0
         bgeu       t1, t0, .l5            // if i   >= l_r, goto .l5

.l1:     xc.ldr.w   t4, a1(t1)             // d_0 = x[ i ]
         xc.ldr.w   t5, a3(t1)             // d_1 = y[ i ]
         xc.madd.3  ( a7, a6 ), t4, t5, a7 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   a6, a0(t1)             // r[ i ] = s

         addi       t1, t1, 1              // i = i + 1
         bltu       t1, t0, .l1            // if i   <  l_r, goto .l1

         mv         t5, zero               // d_1 = 0

         bgeu       t1, a2, .l3            // if i   >= l_x, goto .l3

.l2:     xc.ldr.w   t4, a1(t1)             // d_0 = x[ i ]
         xc.madd.3  ( a7, a6 ), t4, t5, a7 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   a6, a0(t1)             // r[ i ] = s

         addi       t1, t1, 1              // i = i + 1
         bltu       t1, a2, .l2            // if i   <  l_x, goto .l2
    
.l3:     bgeu       t1, a4, .l5            // if i   >= l_y, goto .l5

.l4:     xc.ldr.w   t4, a3(t1)             // d_0 = y[ i ]
         xc.madd.3  ( a7, a6 ), t4, t5, a7 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   a6, a0(t1)             // r[ i ] = s

         addi       t1, t1, 1              // i = i + 1
         bltu       t1, a4, .l4            // if i   <  l_y, goto .l4

.l5:     mv         a0, a7                 // return c
         ret
#endif

.endfunc
#endif
	
// ============================================================================	
