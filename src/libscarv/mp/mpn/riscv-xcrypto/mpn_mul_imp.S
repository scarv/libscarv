// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).

#include "scarv/mp/mpn/mpn_mul_imp.h"

// ============================================================================	

#if ( LIBSCARV_CONF_MPN_MUL_EXTERN )	
.section .text

.func    mpn_mul
.global  mpn_mul

// void mpn_mul( limb_t* r, const limb_t* x, int l_x, const limb_t* y, int l_y );
//
// a0 = limb_t *   r
// a1 = limb_t *   x
// a2 = int      l_x
// a3 = limb_t *   y
// a4 = int      l_y
//
// t0 =          l_r
// t1 =            i
// t2 =
// t3 =
//
// t5 =
// t6 =
// t4 =
// a6 =
// a7 =

#if ( LIBSCARV_CONF_MPN_MUL_OPERAND_SCANNING )	
mpn_mul: # Auxilliary storage on the stack.
         addi        sp, sp, -4          # sp = end of aux array R

         # How long will the result be?
         add     t0, a2, a4              # t0 = l_x + l_y
         beqz    t0, .mpn_mul_finish     # if len=0, finish
    
         # Clear the auxiliary result array
         slli    t1, t0, 2               # t1 = size of R
         sub     t2, sp, t1              # t2 = start of R
.clear_r:
         sw      zero, 0(t2)         # r[t2] = 0
         addi    t2, t2, 4           # r ++
         blt     t2, sp, .clear_r
         sub     t2, sp, t1              # t2 = start of aux array R

         # Start computation loop
         beqz    a4, .mpn_mul_finish
         mv      t0, zero                # t0 = outer loop counter

.mpn_mul_outer:
        
         beqz a2, .mpn_mul_outer_finish
         mv          t1, zero                # t1 = inner loop counter
         mv          a7, zero                # C  = 0
            
         # Load inputs to MUL function
         xc.ldr.w t5, a3(t0)                 # t5 = y[j]
        
.mpn_mul_inner:

         # Load inputs to MUL function
         xc.ldr.w t6, a1(t1)             # t6 = x[i]

         add     t3, t0, t1              # t3 = i+j = t0+t1
         xc.ldr.w t4, t2(t3)             # t4 = R[j+i]

         # Compute (y[i] * x[i]) + R[i+j] + C
         xc.mmul.3 (a7,a6), t5, t6, a7
         xc.macc.1 (a7,a6), a7, a6, t4

         # Store results back to carry and aux Result array
         xc.str.w a6, t2(t3)             # R[j+i] = low word 

         addi    t1, t1, 1
         blt     t1, a2, .mpn_mul_inner  # if(i(t1) < l_x) goto inner loop

.mpn_mul_outer_finish:

         # R[j+l_x] = c
         add     t3, t0, a2
         xc.str.w a7, t2(t3)                 # R[j+l_x] = C

         addi    t0, t0, 1
         blt     t0, a4, .mpn_mul_outer      # if(j(t0) < l_y) goto outer loop

.mpn_mul_finish:

         # Copy aux R array into result array
         mv  t0, t2          # src
         mv  t1, a0          # dst
         add t3, a2, a4
         mv  t4, zero

.mpn_cpy_back:

         xc.ldr.w  t6, t0(t4)
         xc.str.w  t6, t1(t4)
        
         addi t4, t4, 1

         blt  t4, t3, .mpn_cpy_back
    
         addi        sp, sp, 4
         ret
#endif

#if ( LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING )
#error "no implementation for !LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING"
#endif
	
.endfunc
#endif

// ============================================================================	
