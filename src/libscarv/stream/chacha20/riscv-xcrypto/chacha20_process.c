
#include <scarv/stream/chacha20/chacha20.h>
#include <scarv/share/xcrypto_intrinsics.h>

#if ( LIBSCARV_CONF_CHACHA20_PROCESS_EXTERN )

extern void chacha20_block( uint32_t* r, uint32_t* x );

void chacha20_process( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* x, int l ) {
  chacha20_ctx_t t;

  for( int i = 0; i < ( l / 64 ); i++ ) {
    chacha20_block( t.w, ctx->w );
    ctx->w[ 12 ]++; // inc. counter in word 12 of state

    for( int j = 0; j < (          64 ); j++ ) {
        uint8_t l_x = _xc_ldr_bu(x  , 64*i+j);
        uint8_t l_b = _xc_ldr_bu(t.b,      j);
        _xc_str_b(r, 64*i+j, l_x ^ l_b);
    }
  }

  if( ( l % 64 ) != 0 ) {
    int i = l / 64;

    chacha20_block( t.w, ctx->w );
    ctx->w[ 12 ]++; // inc. counter in word 12 of state

    for( int j = 0; j < ( l % 64 ); j++ ) {
      uint8_t l_x = _xc_ldr_bu(x  , 64*i+j);
      uint8_t l_b = _xc_ldr_bu(t.b,      j);
      _xc_str_b(r, 64*i+j, l_x ^ l_b);
    }
  }
}
#endif //( LIBSCARV_CONF_CHACHA20_PROCESS_EXTERN )
