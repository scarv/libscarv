#include <scarv/mp/mpn/mpn_sqr.h>

#if !( CONF_MP_MPN_SQR_EXTERN ) && ( CONF_MP_MPN_SQR_OPERAND_SCANNING )
void mpn_sqr( limb_t* r, const limb_t* x, int l_x ) {

}
#endif

#if !( CONF_MP_MPN_SQR_EXTERN ) && ( CONF_MP_MPN_SQR_PRODUCT_SCANNING )
void mpn_sqr( limb_t* r, const limb_t* x, int l_x ) {
  int l_r = l_x + l_x, l = BITSOF( limb_t ) - 1;

  limb_t R[ l_r ], c, u, v, c_0 = 0, c_1 = 0, c_2 = 0;

  for( int k = 0; k < ( l_r - 1 ); k++ ) {
    for( int j = 0; j < l_x; j++ ) {
      for( int i = j; i < l_x; i++ ) {
        if( ( i + j ) == k ) {
          limb_t d_y = x[ j ];
          limb_t d_x = x[ i ];

          LIMB_MUL0( u,   v, d_y, d_x    );
          if( j < i ) {            
            limb_t t  = 1 & ( v >> l );
                   v  =     ( v << 1 );
                   c  = 1 & ( u >> l );
                   u  = t | ( u << 1 );     c_2 += c;
          }
          LIMB_ADD0( c, c_0, c_0,   v    );
          LIMB_ADD1( c, c_1, c_1,   u, c ); c_2 += c;
        }
      }
    }

    R[ k ] = c_0; c_0 = c_1; c_1 = c_2; c_2 = 0;
  }

  R[ l_r - 1 ] = c_0;

  memcpy( r, R, l_r * SIZEOF( limb_t ) );
}
#endif

void mpn_sqr_1( limb_t* r, const limb_t  x        ) {
  mpn_sqr( r, &x, 1 );
}

void mpn_sqr_n( limb_t* r, const limb_t* x, int l ) {
  mpn_sqr( r,  x, l );
}
