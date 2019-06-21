#include <scarv/mp/mpn/mpn_mul.h>

#if !( CONF_MP_MPN_MUL_EXTERN ) && ( CONF_MP_MPN_MUL_OPERAND_SCANNING )
void mpn_mul( limb_t* r, const limb_t* x, int l_x, 
                         const limb_t* y, int l_y ) {

  int l_r = l_x + l_y;

  limb_t R[ l_r ], c;

  memset( R, 0, l_r * SIZEOF( limb_t ) );

  for( int j = 0; j < l_y; j++ ) {
    c = 0;

    for( int i = 0; i < l_x; i++ ) {
      limb_t d_y = y[ j     ];
      limb_t d_x = x[     i ];
      limb_t d_R = R[ j + i ];

      LIMB_MUL2( c, R[ j + i ], d_y, d_x, d_R, c );
    }

    R[ j + l_x ] = c;
  }

  memcpy( r, R, l_r * SIZEOF( limb_t ) );
}
#endif

#if !( CONF_MP_MPN_MUL_EXTERN ) && ( CONF_MP_MPN_MUL_PRODUCT_SCANNING )
void mpn_mul( limb_t* r, const limb_t* x, int l_x, 
                         const limb_t* y, int l_y ) {

  int l_r = l_x + l_y;

  limb_t R[ l_r ], c, u, v, c_0 = 0, c_1 = 0, c_2 = 0;

  for( int k = 0; k < ( l_r - 1 ); k++ ) {
    for( int j = 0; j < l_y; j++ ) {
      for( int i = 0; i < l_x; i++ ) {
        if( ( i + j ) == k ) {
          limb_t d_y = y[ j ];
          limb_t d_x = x[ i ];

          LIMB_MUL0( u,   v, d_y, d_x    );

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

void mpn_mul_1( limb_t* r, const limb_t* x, int l_x,  const limb_t  y        ) {
  mpn_mul( r, x, l_x, &y, 1 );
}

void mpn_mul_n( limb_t* r, const limb_t* x,           const limb_t* y, int l ) {
  mpn_mul( r, x, l,    y, l );
}
