#include "scarv/mp/mpz.h"

void mpz_sub( mpz_t* r, const mpz_t* x, const mpz_t* y ) {
  if     ( ( x->s <  0 ) && ( y->s >= 0 ) ) {
      MPZ_ADD( r, x, y, MPZ_SIGN_NEG ); // r = -( abs(x) + abs(y) )
  }
  else if( ( x->s >= 0 ) && ( y->s <  0 ) ) {
      MPZ_ADD( r, x, y, MPZ_SIGN_POS ); // r = +( abs(x) + abs(y) )
  }
  else if( ( x->s >= 0 ) && ( y->s >= 0 ) ) {
    if( mpn_cmp( x->d, x->l, y->d, y->l ) >= 0 ) {
      MPZ_SUB( r, x, y, MPZ_SIGN_POS ); // r = +( abs(x) - abs(y) )
    }
    else {
      MPZ_SUB( r, y, x, MPZ_SIGN_NEG ); // r = -( abs(y) - abs(x) )
    }
  }
  else if( ( x->s <  0 ) && ( y->s <  0 ) ) {
    if( mpn_cmp( x->d, x->l, y->d, y->l ) >= 0 ) {
      MPZ_SUB( r, x, y, MPZ_SIGN_NEG ); // r = -( abs(x) - abs(y) )
    }
    else {
      MPZ_SUB( r, y, x, MPZ_SIGN_POS ); // r = +( abs(y) - abs(x) )
    }
  }
}
