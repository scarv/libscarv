#include "test.h"

int main( int argc, char* argv[] ) {
  if( argc != 4 ) {
    printf( "usage: %s <trials> <min. limbs> <max. limbs>", argv[ 0 ] ); abort();
  }

  int n     = atoi( argv[ 1 ] );
  int l_min = atoi( argv[ 2 ] );
  int l_max = atoi( argv[ 3 ] );

  printf( "import binascii, Crypto.Cipher.AES as AES\n" );

  test_aes( n );

  test_mpn( n, l_min, l_max );
  test_mpz( n, l_min, l_max );
  test_mrz( n, l_min, l_max );

  return 0;
}
