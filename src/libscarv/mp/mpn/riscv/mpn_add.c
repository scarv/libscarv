#include "scarv/mp/mpn_add.h"

#if !( CONF_MP_MPN_ADD_EXTERN ) && ( CONF_MP_MPN_ADD_GUARD  )
limb_t mpn_add( limb_t* r, const limb_t* x, int l_x, 
                           const limb_t* y, int l_y ) {

  int l_r = MAX( l_x, l_y );

  limb_t c = 0;

  for( int i = 0; i < l_r; i++ ) {
    limb_t d_x = ( i < l_x ) ? x[ i ] : 0;
    limb_t d_y = ( i < l_y ) ? y[ i ] : 0;

    LIMB_ADD1( c, r[ i ], d_x, d_y, c );
  }
        
  return c;
}
#endif

#if !( CONF_MP_MPN_ADD_EXTERN ) && ( CONF_MP_MPN_ADD_UNROLL )
limb_t mpn_add( limb_t* r, const limb_t* x, int l_x, 
                           const limb_t* y, int l_y ) {

  int l_r = MIN( l_x, l_y ), i = 0;

  limb_t c = 0;

  while( i < l_r ) {
    limb_t d_x = x[ i ];
    limb_t d_y = y[ i ];

    LIMB_ADD1( c, r[ i ], d_x, d_y, c ); i++;
  }
  while( i < l_x ) {
    limb_t d_x = x[ i ];

    LIMB_ADD0( c, r[ i ], d_x,      c ); i++;
  }
  while( i < l_y ) {
    limb_t d_y = y[ i ];

    LIMB_ADD0( c, r[ i ],      d_y, c ); i++;
  }
        
  return c;                                                          
}
#endif

limb_t mpn_add_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  return mpn_add( r, x, l_x, &y, 1 );
}

limb_t mpn_add_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  return mpn_add( r, x, l,    y, l );
}

