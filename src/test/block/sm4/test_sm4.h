/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __TEST_SM4_H
#define __TEST_SM4_H

#include "util.h"

#include "scarv/block/sm4/sm4_enc.h"
#include "scarv/block/sm4/sm4_dec.h"

#define TEST_SM4_KAT_COUNT ( 1 )

typedef struct {
  uint8_t m[ 16 ], c[ 16 ], k_enc[ 16 ], k_dec[ 16 ];
} test_sm4_kat_t;

#endif
