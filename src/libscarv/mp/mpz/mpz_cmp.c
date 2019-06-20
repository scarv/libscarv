#include "scarv/mp/mpz.h"

int mpz_cmp( const mpz_t* x, const mpz_t* y ) {
  if     ( ( x->s <  0 ) && ( y->s >= 0 ) ) {
    return -1;
  }
  else if( ( x->s >= 0 ) && ( y->s <  0 ) ) {
    return +1;
  }
  else if( ( x->s >= 0 ) && ( y->s >= 0 ) ) {
    return +mpn_cmp( x->d, x->l, y->d, y->l );
  }
  else if( ( x->s <  0 ) && ( y->s <  0 ) ) {
    return -mpn_cmp( x->d, x->l, y->d, y->l );
  }

  return 0;
}
