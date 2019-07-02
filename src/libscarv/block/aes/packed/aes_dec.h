/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_AES_DEC_H
#define __LIBSCARV_AES_DEC_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/block/aes/aes_conf.h>
#include <scarv/block/aes/aes_divx.h>
#include <scarv/block/aes/aes_mulx.h>
#include <scarv/block/aes/aes_rcon.h>
#include <scarv/block/aes/aes_sbox.h>

#include <scarv/block/aes/aes_enc.h>

#if ( LIBSCARV_CONF_AES_KEY_PRECOMP )
extern void aes_dec_exp     ( uint8_t* r, const uint8_t*  k               );
#endif
extern void aes_dec_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rcon );

extern void aes_dec( uint8_t* r, uint8_t* m, uint8_t* k );

#endif
