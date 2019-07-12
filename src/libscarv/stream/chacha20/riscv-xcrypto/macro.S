// Copyright (C) 2019 SCARV project <info@scarv.org>
//
// Use of this source code is restricted per the MIT license, a copy of which 
// can be found at https://opensource.org/licenses/MIT (or should be included 
// as LICENSE.txt within the associated archive or repository).
	
.macro CHACHA20_QR a,b,c,d
  xc.padd     w, \a, \a, \b               // a += b
  xc.bop         \d, \d, \a, 0b01100110   // d ^= a
  xc.prot.i   w, \d, \d, 32-16            // d <<< 16

  xc.padd     w, \c, \c, \d               // c += d
  xc.bop         \b, \b, \c, 0b01100110   // b ^= c
  xc.prot.i   w, \b, \b, 32-12            // b <<< 12

  xc.padd     w, \a, \a, \b               // a += b
  xc.bop         \d, \d, \a, 0b01100110   // d ^= a
  xc.prot.i   w, \d, \d, 32-8             // d <<< 8

  xc.padd     w, \c, \c, \d               // c += d
  xc.bop         \b, \b, \c, 0b01100110   // b ^= c
  xc.prot.i   w, \b, \b, 32-7             // b <<< 7
.endm

.macro CHACHA20_LD a,  x,  o
    xc.ld.w     \a , \o(\x)               // t[ i ] = x[ i ]
.endm
	
.macro CHACHA20_ST a,b,x,r,o
    xc.ld.w     \a , \o(\x)
    xc.padd  w, \b , \b, \a
    xc.st.w     \b , \o(\r)               // r[ i ] = x[ i ] + t[ i ]
.endm
