// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).
	
.macro CHACHA20_QR a,b,c,d
  add    \a, \a, \b               // a += b
  xor    \d, \d, \a               // d ^= a
  rori   \d, \d, 32-16            // d <<< 16

  add    \c, \c, \d               // c += d
  xor    \b, \b, \c               // b ^= c
  rori   \b, \b, 32-12            // b <<< 12

  add    \a, \a, \b               // a += b
  xor    \d, \d, \a               // d ^= a
  rori   \d, \d, 32-8             // d <<< 8

  add    \c, \c, \d               // c += d
  xor    \b, \b, \c               // b ^= c
  rori   \b, \b, 32-7             // b <<< 7
.endm

.macro CHACHA20_LD a,  x,  o
  lw     \a , \o(\x)                 // t[ i ] = x[ i ]
.endm
	
.macro CHACHA20_ST a,b,x,r,o
  lw     \a , \o(\x)
  add    \b , \b, \a
  sw     \b , \o(\r)                 // r[ i ] = x[ i ] + t[ i ]
.endm
