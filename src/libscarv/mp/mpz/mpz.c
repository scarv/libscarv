#include <scarv/mp/mpz/mpz.h>

int mpz_size( const mpz_t* x ) {
  return x->l;
}

limb_t mpz_getlimbn( const mpz_t* x, int n ) {
  return ( ( n >= 0 ) && ( n < x->l ) ) ? x->d[ n ] : 0;
}
