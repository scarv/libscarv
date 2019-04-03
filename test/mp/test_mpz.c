#include "test_mpz.h"

// ============================================================================

void test_mpz_rand( mpz_t* r, int l_r_min, int l_r_max ) {
  r->l = test_rand_byte( ( uint8_t* )( r->d ), sizeof( limb_t ), l_r_min, l_r_max ); r->s = ( test_rand_bool() ) ? ( MPZ_SIGN_POS ) : ( MPZ_SIGN_NEG );
}

void test_mpz_dump( char* id, mpz_t* x ) {
  printf( "%s = %cint( '", id, ( x->s == MPZ_SIGN_POS ) ? ( '+' ) : ( '-' ) ); test_dump_msb( ( uint8_t* )( x->d ), x->l * sizeof( limb_t ) ); printf( "', 16 )\n" );
}

// ============================================================================

void test_mpz_add( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpz", "add", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    TEST_MEASURE( mpz_add( &r, &x, &y ) );

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

void test_mpz_sub( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpz", "sub", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    TEST_MEASURE( mpz_sub( &r, &x, &y ) );

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

void test_mpz_mul( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpz", "mul", i, n );

    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    test_mpz_dump( "x", &x );
    test_mpz_dump( "y", &y );

    TEST_MEASURE( mpz_mul( &r, &x, &y ) );

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

  int l_min = MIN( opt_mp_mpz_min_limb, CONF_MP_MPZ_MAX_LIMBS );
  int l_max = MIN( opt_mp_mpz_max_limb, CONF_MP_MPZ_MAX_LIMBS );

  test_mpz_add( opt_trials, l_min, l_max );
  test_mpz_sub( opt_trials, l_min, l_max );
  test_mpz_mul( opt_trials, l_min, l_max );

  test_fini();

  return 0;
}

// ============================================================================
