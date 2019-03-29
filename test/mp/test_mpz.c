#include "test_mpz.h"

FILE* urandom = NULL;

// ============================================================================

void test_mpz_rand( mpz_t* r, int l_min, int l_max ) {
  uint8_t t;

  fread( &t, sizeof( uint8_t ), 1, urandom );

  r->l = ( t % ( l_max + 1 - l_min) ) + l_min;

  fread( &t, sizeof( uint8_t ), 1, urandom );

  r->s = ( t & 1 ) ? MPZ_SIGN_POS : MPZ_SIGN_NEG;

  fread( r->d, sizeof( limb_t ), r->l, urandom );
}

void test_mpz_dump( char* id, mpz_t* x ) {
  printf( "%s = %cint( '", id, ( x->s == MPZ_SIGN_POS ) ? '+' : '-' );

  for( int i = x->l - 1; i >= 0; i-- ) {
    printf( "%08lX", x->d[ i ] );
  }

  printf( "', 16 )\n" );
}

// ============================================================================

void test_mpz_add( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf( "# test_mpz:mpz_add[%d/%d]\n", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_add( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x + y                                " "\n"       );

    printf( "if ( r != t ) :                          " "\n"       );
    printf( "  print( 'fail test_mpz:mpz_add[%d/%d]' )" "\n", i, n );
    printf( "  print( 'x == %%s' %% ( hex( x ) )     )" "\n"       );
    printf( "  print( 'y == %%s' %% ( hex( y ) )     )" "\n"       );
    printf( "  print( 'r == %%s' %% ( hex( r ) )     )" "\n"       );
    printf( "  print( '  != %%s' %% ( hex( t ) )     )" "\n"       );

    printf( "  sys.exit( 1 )                          " "\n\n"     );
  }
}

void test_mpz_sub( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf( "# test_mpz:mpz_sub[%d/%d]\n", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_sub( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x - y                                " "\n"       );

    printf( "if ( r != t ) :                          " "\n"       );
    printf( "  print( 'fail test_mpz:mpz_sub[%d/%d]' )" "\n", i, n );
    printf( "  print( 'x == %%s' %% ( hex( x ) )     )" "\n"       );
    printf( "  print( 'y == %%s' %% ( hex( y ) )     )" "\n"       );
    printf( "  print( 'r == %%s' %% ( hex( r ) )     )" "\n"       );
    printf( "  print( '  != %%s' %% ( hex( t ) )     )" "\n"       );

    printf( "  sys.exit( 1 )                          " "\n\n"     );
  }
}

void test_mpz_mul( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf( "# test_mpz:mpz_mul[%d/%d]\n", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    MEASURE( mpz_mul( &r, &x, &y ) );

    test_mpz_dump( "r", &r );

    printf( "t = x * y                                " "\n"       );

    printf( "if ( r != t ) :                          " "\n"       );
    printf( "  print( 'fail test_mpz:mpz_mul[%d/%d]' )" "\n", i, n );
    printf( "  print( 'x == %%s' %% ( hex( x ) )     )" "\n"       );
    printf( "  print( 'y == %%s' %% ( hex( y ) )     )" "\n"       );
    printf( "  print( 'r == %%s' %% ( hex( r ) )     )" "\n"       );
    printf( "  print( '  != %%s' %% ( hex( t ) )     )" "\n"       );

    printf( "  sys.exit( 1 )                          " "\n\n"     );
  }
}

// ============================================================================

int main( int argc, char* argv[] ) {
  opt_parse( argc, argv );

  if( NULL == ( urandom = fopen( "/dev/urandom", "rb" ) ) ) {
    abort();
  }

  printf( "import sys\n" );

  int l_min = MIN( opt_mp_mpz_min_limb, CONF_MP_MPZ_MAX_LIMBS );
  int l_max = MIN( opt_mp_mpz_max_limb, CONF_MP_MPZ_MAX_LIMBS );

  test_mpz_add( opt_trials, l_min, l_max );
  test_mpz_sub( opt_trials, l_min, l_max );
  test_mpz_mul( opt_trials, l_min, l_max );

  fclose( urandom );

  return 0;
}

// ============================================================================
