/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_CHACHA20_H
#define __LIBSCARV_CHACHA20_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define CHACHA20_SIZEOF_KEY     ( 32 ) /* 256-bit = 32 byte = 8 word key     */
#define CHACHA20_SIZEOF_COUNTER (  4 ) /*  32-bit =  4 byte = 1 word counter */
#define CHACHA20_SIZEOF_NONCE   ( 12 ) /*  96-bit = 12 byte = 3 word nonce   */

typedef union {
  uint32_t w[ 16 ]; uint8_t b[ 64 ]; 
} chacha20_ctx_t;

extern void chacha20_init( chacha20_ctx_t* ctx, uint8_t* k, uint8_t* counter, uint8_t* nonce );

extern void chacha20_enc( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* m, int l );
extern void chacha20_dec( chacha20_ctx_t* ctx, uint8_t* r, uint8_t* c, int l );

#endif
