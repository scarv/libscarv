#include <scarv/mp/mpn/mpn.h>

int mpn_lop( const limb_t* x, int l_x ) {
  while( ( l_x > 1 ) && ( x[ l_x - 1 ] == 0 ) ) {
    l_x--;
  }

  return l_x;
}
