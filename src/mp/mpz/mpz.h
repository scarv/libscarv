#ifndef __MPZ_H
#define __MPZ_H

#include "util.h"
#include "limb.h"
#include  "mpn.h"

#define MPZ_SIGN_POS ( +1 )
#define MPZ_SIGN_NEG ( -1 )

#define MPZ_SQR(r,x,  s_r) {                             \
  int l_r  = (x)->l + (x)->l;                            \
                                                         \
                      mpn_sqr( (r)->d, (x)->d, (x)->l ); \
                                                         \
  (r)->l            = mpn_lop( (r)->d, l_r );            \
  (r)->s            = s_r;                               \
}
#define MPZ_ADD(r,x,y,s_r) {                             \
  int l_r = MAX( (x)->l, (y)->l ) + 1;                   \
                                                         \
  (r)->d[ l_r - 1 ] = mpn_add( (r)->d, (x)->d, (x)->l,   \
                                       (y)->d, (y)->l ); \
                                                         \
  (r)->l            = mpn_lop( (r)->d, l_r );            \
  (r)->s            = s_r;                               \
}
#define MPZ_SUB(r,x,y,s_r) {                             \
  int l_r = MAX( (x)->l, (y)->l ) + 1;                   \
                                                         \
  (r)->d[ l_r - 1 ] = mpn_sub( (r)->d, (x)->d, (x)->l,   \
                                       (y)->d, (y)->l ); \
                                                         \
  (r)->l            = mpn_lop( (r)->d, l_r );            \
  (r)->s            = s_r;                               \
}
#define MPZ_MUL(r,x,y,s_r) {                             \
  int l_r = (x)->l + (y)->l;                             \
                                                         \
                      mpn_mul( (r)->d, (x)->d, (x)->l,   \
                                       (y)->d, (y)->l ); \
                                                         \
  (r)->l            = mpn_lop( (r)->d, l_r );            \
  (r)->s            = s_r;                               \
}

typedef struct __mpz_t {
  limb_t d[ CONF_MP_MPZ_MAX_LIMBS ];

  int    l;
  int    s;
} mpz_t;

// get      limbs in x
extern int    mpz_size( const mpz_t* x );
// get n-th limb  in x
extern limb_t mpz_getlimbn( const mpz_t* x, int n );

#include "mpz_cmp.h"

#include "mpz_add.h"
#include "mpz_sub.h"
#include "mpz_mul.h"

#endif
