/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_SM4_DEC_H
#define __LIBSCARV_SM4_DEC_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/block/sm4/sm4_share.h>

#include <scarv/block/sm4/sm4_enc.h>

#if ( LIBSCARV_CONF_SM4_KEY_PRECOMP )
extern void     sm4_dec_exp( uint32_t* r, const uint8_t* k );
#endif
extern uint32_t sm4_dec_exp_step( uint32_t* r, const uint32_t* k, uint32_t ck );

extern void     sm4_dec( uint8_t* r, uint8_t* m, uint8_t* k );

#endif
