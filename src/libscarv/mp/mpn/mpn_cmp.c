#include <scarv/mp/mpn/mpn_cmp.h>

#if !( CONF_MP_MPN_CMP_EXTERN )
int mpn_cmp( const limb_t* x, int l_x, 
             const limb_t* y, int l_y ) {

  if     ( l_x > l_y ) {
    return +1;
  }
  else if( l_x < l_y ) {
    return -1;
  }

  for( int i = ( l_x - 1 ); i >= 0; i-- ) {
    limb_t d_x = x[ i ];
    limb_t d_y = y[ i ];
                                 
    if     ( d_x > d_y ) {
      return +1;
    }                                             
    else if( d_x < d_y ) {
      return -1;
    }
  }                                                              
                                                                  
  return 0;
}
#endif

int mpn_cmp_1( const limb_t* x, int l_x, const limb_t  y        ) {
  return mpn_cmp( x, l_x, &y, 1 );
}

int mpn_cmp_n( const limb_t* x,          const limb_t* y, int l ) {
  return mpn_cmp( x, l,    y, l );
}
