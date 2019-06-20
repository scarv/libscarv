#include "scarv/mp/mpn.h"

int mpn_lop( const limb_t* x, int l_x ) {
  while( ( l_x > 1 ) && ( x[ l_x - 1 ] == 0 ) ) {
    l_x--;
  }

  return l_x;
}

limb_t mpn_add_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  return mpn_add( r, x, l_x, &y, 1 );
}

limb_t mpn_add_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  return mpn_add( r, x, l,    y, l );
}


limb_t mpn_sub_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  return mpn_sub( r, x, l_x, &y, 1 );
}

limb_t mpn_sub_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  return mpn_sub( r, x, l,    y, l );
}

void mpn_mul_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  mpn_mul( r, x, l_x, &y, 1 );
}

void mpn_mul_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  mpn_mul( r, x, l,    y, l );
}

