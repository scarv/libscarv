#include "test_mrz.h"

// ============================================================================

void test_mrz_dump( char* id, mrz_t x, int l_x ) {
  printf( "%s = int( '", id ); test_dump_msb( ( uint8_t* )( x ), l_x * sizeof( limb_t ) ); printf( "', 16 )\n" );
}

int test_mrz_rand_modulus( mrz_t r, int l_min, int l_max ) {
  int l_r;

  do {
    l_r = test_rand_seq( ( uint8_t* )( r ), l_min, l_max, sizeof( limb_t ) );
  } while( !( r[ 0 ] & 1 ) );

  return l_r;
}

int test_mrz_rand_operand( mrz_t r, mrz_t x, int l_x ) {
  int l_r = l_x;

  do {
    l_r = test_rand_seq( ( uint8_t* )( r ), l_r,   l_r,   sizeof( limb_t ) );
  }
  while( mpn_cmp( r, l_r, x, l_x ) >= 0 );

  return l_r;
}

// ============================================================================

void test_mrz_exp( int n, int l_min, int l_max ) {
  mrz_ctx_t ctx;  
  
  mrz_t N; int l_N;
  mrz_t x; int l_x;
  mrz_t y; int l_y;
  mrz_t r; int l_r;

  for( int i = 1; i <= n; i++ ) {
    test_id( "test_mrz", "exp", i, n );
    l_N = l_r = test_mrz_rand_modulus( N, l_min, l_max );

          l_x = test_mrz_rand_operand( x, N, l_N );
          l_y = test_mrz_rand_operand( y, N, l_N );

    test_mrz_dump( "N", N, l_N );
    test_mrz_dump( "x", x, l_x );
    test_mrz_dump( "y", y, l_y );

    mrz_precomp( &ctx, N, l_N );

    mrz_mul( &ctx, r, x, ctx.rho_2 );
    TEST_MEASURE( mrz_exp( &ctx, r, r, y, l_y ) );
    mrz_mul( &ctx, r, r, ctx.rho_0 );

    test_mrz_dump( "r", r, l_r );

    printf( "t = pow( x, y, N )                   " "\n"   );

    printf( "if ( r != t ) :                      " "\n"   );
    printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
    printf( "  print( 'N == %%s' %% ( hex( N ) ) )" "\n"   );
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

  test_mrz_exp( opt_trials, opt_mp_mrz_min_limb, opt_mp_mrz_max_limb );

  test_fini();

  return 0;
}

// ============================================================================
