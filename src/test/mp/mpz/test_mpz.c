/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_mpz.h"

// ============================================================================

void test_mpz_dump( char* id, mpz_t* x ) {
  printf( "%s = %cint( '", id, ( x->s == MPZ_SIGN_POS ) ? ( '+' ) : ( '-' ) ); test_dump_seq( ( uint8_t* )( x->d ), x->l * sizeof( limb_t ), DUMP_MSB ); printf( "', 16 )\n" );
}

void test_mpz_rand( mpz_t* r, int l_r_min, int l_r_max ) {
  r->l = test_rand_seq( ( uint8_t* )( r->d ), l_r_min, l_r_max, sizeof( limb_t ) ); 

  if( test_rand_int() & 1 ) {
    r->s = MPZ_SIGN_POS;
  } 
  else {
    r->s = MPZ_SIGN_NEG;
  }
}

// ============================================================================

void test_mpz_add( int trials, int l_min, int l_max ) {
  mpz_t x;
  mpz_t y;
  mpz_t r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpz", "add", i, trials );

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_add( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x + y                            " "\n"   );

    printf( "if ( r != t ) :                      " "\n"   );
    printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
    printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

void test_mpz_sub( int trials, int l_min, int l_max ) {
  mpz_t x;
  mpz_t y;
  mpz_t r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpz", "sub", i, trials );

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_sub( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x - y                            " "\n"   );

    printf( "if ( r != t ) :                      " "\n"   );
    printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
    printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

void test_mpz_mul( int trials, int l_min, int l_max ) {
  mpz_t x;
  mpz_t y;
  mpz_t r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpz", "mul", i, trials );

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_mul( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x * y                            " "\n"   );

    printf( "if ( r != t ) :                      " "\n"   );
    printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
    printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
    printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
    printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
    printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

    printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys" );

  test_mpz_add( opt_trials, opt_limb_min, opt_limb_max );
  test_mpz_sub( opt_trials, opt_limb_min, opt_limb_max );
  test_mpz_mul( opt_trials, opt_limb_min, opt_limb_max );

  test_fini();

  return 0;
}

// ============================================================================
