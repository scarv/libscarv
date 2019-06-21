#include "scarv/mp/mpn_sqr.h"

#if !( CONF_MP_MPN_SQR_EXTERN ) && ( CONF_MP_MPN_SQR_OPERAND_SCANNING )
void mpn_sqr( limb_t* r, const limb_t* x, int l_x ) {
    mpn_mul(r, x, l_x, x, l_x);
}
#endif

#if !( CONF_MP_MPN_SQR_EXTERN ) && ( CONF_MP_MPN_SQR_PRODUCT_SCANNING )
void mpn_sqr( limb_t* r, const limb_t* x, int l_x ) {
    mpn_mul(r, x, l_x, x, l_x);
}
#endif

void mpn_sqr_1( limb_t* r, const limb_t  x        ) {
  mpn_sqr( r, &x, 1 );
}

void mpn_sqr_n( limb_t* r, const limb_t* x, int l ) {
  mpn_sqr( r,  x, l );
}
