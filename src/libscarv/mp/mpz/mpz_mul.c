#include <scarv/mp/mpz/mpz_mul.h>

void mpz_mul( mpz_t* r, const mpz_t* x, const mpz_t* y ) {
  if( x->s == y->s ) {
    // r = +( abs(x) * abs(y) )
    MPZ_MUL( r, x, y, MPZ_SIGN_POS );
  }
  else {
    // r = -( abs(x) * abs(y) )
    MPZ_MUL( r, x, y, MPZ_SIGN_NEG );
  }
}
