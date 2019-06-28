/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/mp/mpn/mpn_sub.h>

#if ( !LIBSCARV_CONF_MPN_SUB_EXTERN ) && ( LIBSCARV_CONF_MPN_SUB_GUARD  )
limb_t mpn_sub( limb_t* r, const limb_t* x, int l_x, 
                           const limb_t* y, int l_y ) {

  int l_r = MAX( l_x, l_y );

  limb_t c = 0;

  for( int i = 0; i < l_r; i++ ) {
    limb_t d_x = ( i < l_x ) ? x[ i ] : 0;
    limb_t d_y = ( i < l_y ) ? y[ i ] : 0;

    LIMB_SUB1( c, r[ i ], d_x, d_y, c );
  }
        
  return c;
}
#endif

#if ( !LIBSCARV_CONF_MPN_SUB_EXTERN ) && ( LIBSCARV_CONF_MPN_SUB_UNROLL )
limb_t mpn_sub( limb_t* r, const limb_t* x, int l_x, 
                           const limb_t* y, int l_y ) {

  int l_r = MIN( l_x, l_y ), i = 0;

  limb_t c = 0;

  while( i < l_r ) {
    limb_t d_x = x[ i ];
    limb_t d_y = y[ i ];

    LIMB_SUB1( c, r[ i ], d_x, d_y, c ); i++;
  }
  while( i < l_x ) {
    limb_t d_x = x[ i ];

    LIMB_SUB0( c, r[ i ], d_x,      c ); i++;
  }
        
  return c;                                                          
}
#endif

limb_t mpn_sub_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  return mpn_sub( r, x, l_x, &y, 1 );
}

limb_t mpn_sub_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  return mpn_sub( r, x, l,    y, l );
}
