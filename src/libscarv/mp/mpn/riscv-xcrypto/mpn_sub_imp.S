// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/mp/mpn/mpn_sub_imp.h"

// ============================================================================	

#if ( LIBSCARV_CONF_MPN_SUB_EXTERN )
.section .text

.func    mpn_sub
.global  mpn_sub

// limb_t mpn_sub( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );
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
// c0 =            r[ i ]  = s
// c1 =                      c
// c2 =            x[ i ] ~= d_0
// c3 =            y[ i ] ~= d_1
	
#if ( LIBSCARV_CONF_MPN_SUB_GUARD  )
mpn_sub: slli       t0, a2, 2              // l_r = l_x scaled into number of bytes
         bltu       a4, a2, .l0            // if l_y <  l_x, goto .l0
         slli       t0, a4, 2              // l_r = l_y scaled into number of bytes

.l0:     slli       a2, a2, 2              // l_x = l_x scaled into number of bytes
         slli       a4, a4, 2              // l_y = l_y scaled into number of bytes

	 xc.gpr2xcr c1, zero               // c = 0

         li         t1, 0                  // i = 0
         bgeu       t1, t0, .l5            // if i   >= l_r, goto .l5

.l1:     xc.gpr2xcr c2, zero               // d_0 = 0
         bgeu       t1, a2, .l2            // if i   >= l_x, goto .l2
         xc.ldr.w   c2, t1, a1             // d_0 = x[ i ]         
.l2:     xc.gpr2xcr c3, zero               // d_1 = 0
         bgeu       t1, a4, .l3            // if i   >= l_y, goto .l3
         xc.ldr.w   c3, t1, a3             // d_1 = y[ i ]
.l3:     xc.msub.3  ( c0, c1 ), c2, c3, c1 // ( s, c ) = d_0 - d_1 - c
         xc.str.w   c0, t1, a0             // r[ i ] = s

         addi       t1, t1, 4              // i = i + 1
         bltu       t1, t0, .l1            // if i   <  l_r, goto .l1

.l5:     xc.xcr2gpr a0, c1                 // return c
         ret
#endif

#if ( LIBSCARV_CONF_MPN_SUB_UNROLL )
mpn_sub: slli       t0, a2, 2              // l_r = l_x scaled into number of bytes
         bltu       a2, a4, .l0            // if l_x <  l_y, goto .l0
         slli       t0, a4, 2              // l_r = l_y scaled into number of bytes

.l0:     slli       a2, a2, 2              // l_x = l_x scaled into number of bytes
         slli       a4, a4, 2              // l_y = l_y scaled into number of bytes

	 xc.gpr2xcr c1, zero               // c = 0

         li         t1, 0                  // i = 0
         bgeu       t1, t0, .l5            // if i   >= l_r, goto .l5

.l1:     xc.ldr.w   c2, t1, a1             // d_0 = x[ i ]
         xc.ldr.w   c3, t1, a3             // d_1 = y[ i ]
         xc.msub.3  ( c0, c1 ), c2, c3, c1 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   c0, t1, a0             // r[ i ] = s

         addi       t1, t1, 4              // i = i + 1
         bltu       t1, t0, .l1            // if i   <  l_r, goto .l1

         xc.gpr2xcr c3, zero               // d_1 = 0

         bgeu       t1, a2, .l5            // if i   >= l_x, goto .l5

.l2:     xc.ldr.w   c2, t1, a1             // d_0 = x[ i ]
         xc.msub.3  ( c0, c1 ), c2, c3, c1 // ( s, c ) = d_0 + d_1 + c
         xc.str.w   c0, t1, a0             // r[ i ] = s

         addi       t1, t1, 4              // i = i + 1
         bltu       t1, a2, .l2            // if i   <  l_x, goto .l2

.l5:     xc.xcr2gpr a0, c1                 // return c
         ret
#endif

.endfunc
#endif
	
// ============================================================================	
