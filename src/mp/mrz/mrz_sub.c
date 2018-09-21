#include "mrz_sub.h"

void mrz_sub( const mrz_ctx_t* ctx, mrz_t r, const mrz_t x, const mrz_t y ) {
  if( mpn_cmp_n( y, x, ctx->l_N ) > 0 ) {
    mpn_sub_n( r,      y, x, ctx->l_N );
    mpn_sub_n( r, ctx->N, r, ctx->l_N ); 
  }
  else {
    mpn_sub_n( r,      x, y, ctx->l_N );
  }
}

