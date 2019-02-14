#include "scarv/mp/mpn.h"

int mpn_lop( const limb_t* x, int l_x ) {
  while( ( l_x > 1 ) && ( x[ l_x - 1 ] == 0 ) ) {
    l_x--;
  }

  return l_x;
}

void mpn_mul_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  mpn_mul( r, x, l_x, &y, 1 );
}

void mpn_mul_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  mpn_mul( r, x, l,    y, l );
}

