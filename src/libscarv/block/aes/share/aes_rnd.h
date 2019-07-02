/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_AES_RND_H
#define __LIBSCARV_AES_RND_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#define AES_ENC_RND_KEY_STEP(a,b,c,d        ) {   \
  s[ a ] = s[ a ] ^ rk[ a ];                      \
  s[ b ] = s[ b ] ^ rk[ b ];                      \
  s[ c ] = s[ c ] ^ rk[ c ];                      \
  s[ d ] = s[ d ] ^ rk[ d ];                      \
}
#define AES_ENC_RND_SUB_STEP(a,b,c,d        ) {   \
  s[ a ] = AES_ENC_SBOX[ s[ a ] ];                \
  s[ b ] = AES_ENC_SBOX[ s[ b ] ];                \
  s[ c ] = AES_ENC_SBOX[ s[ c ] ];                \
  s[ d ] = AES_ENC_SBOX[ s[ d ] ];                \
}
#define AES_ENC_RND_ROW_STEP(a,b,c,d,e,f,g,h) {   \
  uint8_t __a1 = s[ a ];                          \
  uint8_t __b1 = s[ b ];                          \
  uint8_t __c1 = s[ c ];                          \
  uint8_t __d1 = s[ d ];                          \
                                                  \
  s[ e ] = __a1;                                  \
  s[ f ] = __b1;                                  \
  s[ g ] = __c1;                                  \
  s[ h ] = __d1;                                  \
}
#define AES_ENC_RND_MIX_STEP(a,b,c,d        ) {   \
  uint8_t __a1 = s[ a ], __a2 = AES_MULX[ __a1 ]; \
  uint8_t __b1 = s[ b ], __b2 = AES_MULX[ __b1 ]; \
  uint8_t __c1 = s[ c ], __c2 = AES_MULX[ __c1 ]; \
  uint8_t __d1 = s[ d ], __d2 = AES_MULX[ __d1 ]; \
                                                  \
  uint8_t __a3 = __a1 ^ __a2;                     \
  uint8_t __b3 = __b1 ^ __b2;                     \
  uint8_t __c3 = __c1 ^ __c2;                     \
  uint8_t __d3 = __d1 ^ __d2;                     \
                                                  \
  s[ a ] = __a2 ^ __b3 ^ __c1 ^ __d1;             \
  s[ b ] = __a1 ^ __b2 ^ __c3 ^ __d1;             \
  s[ c ] = __a1 ^ __b1 ^ __c2 ^ __d3;             \
  s[ d ] = __a3 ^ __b1 ^ __c1 ^ __d2;             \
}

#define AES_DEC_RND_KEY_STEP(a,b,c,d        ) {   \
  s[ a ] = s[ a ] ^ rk[ a ];                      \
  s[ b ] = s[ b ] ^ rk[ b ];                      \
  s[ c ] = s[ c ] ^ rk[ c ];                      \
  s[ d ] = s[ d ] ^ rk[ d ];                      \
}
#define AES_DEC_RND_SUB_STEP(a,b,c,d        ) {   \
  s[ a ] = AES_DEC_SBOX[ s[ a ] ];                \
  s[ b ] = AES_DEC_SBOX[ s[ b ] ];                \
  s[ c ] = AES_DEC_SBOX[ s[ c ] ];                \
  s[ d ] = AES_DEC_SBOX[ s[ d ] ];                \
}
#define AES_DEC_RND_ROW_STEP(a,b,c,d,e,f,g,h) {   \
  uint8_t __a1 = s[ a ];                          \
  uint8_t __b1 = s[ b ];                          \
  uint8_t __c1 = s[ c ];                          \
  uint8_t __d1 = s[ d ];                          \
                                                  \
  s[ e ] = __a1;                                  \
  s[ f ] = __b1;                                  \
  s[ g ] = __c1;                                  \
  s[ h ] = __d1;                                  \
}
#define AES_DEC_RND_MIX_STEP(a,b,c,d        ) {   \
  uint8_t __a1 = s[ a ], __a2 = AES_MULX[ __a1 ]; \
  uint8_t __b1 = s[ b ], __b2 = AES_MULX[ __b1 ]; \
  uint8_t __c1 = s[ c ], __c2 = AES_MULX[ __c1 ]; \
  uint8_t __d1 = s[ d ], __d2 = AES_MULX[ __d1 ]; \
                                                  \
  uint8_t                __a4 = AES_MULX[ __a2 ]; \
  uint8_t                __b4 = AES_MULX[ __b2 ]; \
  uint8_t                __c4 = AES_MULX[ __c2 ]; \
  uint8_t                __d4 = AES_MULX[ __d2 ]; \
                                                  \
  uint8_t                __a8 = AES_MULX[ __a4 ]; \
  uint8_t                __b8 = AES_MULX[ __b4 ]; \
  uint8_t                __c8 = AES_MULX[ __c4 ]; \
  uint8_t                __d8 = AES_MULX[ __d4 ]; \
                                                  \
  uint8_t __aA = __a2 ^ __a8;                     \
  uint8_t __bA = __b2 ^ __b8;                     \
  uint8_t __cA = __c2 ^ __c8;                     \
  uint8_t __dA = __d2 ^ __d8;                     \
                                                  \
  uint8_t __aC = __a4 ^ __a8;                     \
  uint8_t __bC = __b4 ^ __b8;                     \
  uint8_t __cC = __c4 ^ __c8;                     \
  uint8_t __dC = __d4 ^ __d8;                     \
                                                  \
  s[ a ] = __aC ^ __a2 ^ __bA ^ __b1 ^            \
           __cC ^ __c1 ^ __d8 ^ __d1 ;            \
  s[ b ] = __a8 ^ __a1 ^ __bC ^ __b2 ^            \
           __cA ^ __c1 ^ __dC ^ __d1 ;            \
  s[ c ] = __aC ^ __a1 ^ __b8 ^ __b1 ^            \
           __cC ^ __c2 ^ __dA ^ __d1 ;            \
  s[ d ] = __aA ^ __a1 ^ __bC ^ __b1 ^            \
           __c8 ^ __c1 ^ __dC ^ __d2 ;            \
}

#endif
