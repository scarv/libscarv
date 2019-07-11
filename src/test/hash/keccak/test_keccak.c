/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_keccak.h"

// ============================================================================

void test_keccak_p400 ( int n, int l_min, int l_max ) {

}

void test_keccak_p1600( int n, int l_min, int l_max ) {

}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii, Crypto.Hash.SHA as SHA1" );

  test_keccak_p400 ( opt_trials, opt_keccak_min_data, opt_keccak_max_data );
  test_keccak_p1600( opt_trials, opt_keccak_min_data, opt_keccak_max_data );

  test_fini();

  return 0;
}

// ============================================================================
