#include "test_mpn.h"

// ============================================================================

void test_mpn_dump( char* id, limb_t* x, int l_x ) {
  printf( "%s = int( '", id ); test_dump_msb( ( uint8_t* )( x ), l_x * sizeof( limb_t ) ); printf( "', 16 )\n" );
}

int test_mpn_rand( limb_t* r, int l_r_min, int l_r_max ) {
  return test_rand_seq( ( uint8_t* )( r ), l_r_min, l_r_max, sizeof( limb_t ) );
}

// ============================================================================

void test_mpn_add( int n, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= n; i++ ) {
    test_id( "test_mpn", "add", i, n );

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );

    l_r = MAX( l_x, l_y ) + 1; 
    TEST_MEASURE( r[ l_r - 1 ] = mpn_add( r, x, l_x, y, l_y ) );
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "r", r, l_r );

      printf( "t = x + y                            " "\n"   );
    
      printf( "if ( r != t ) :                      " "\n"   );
      printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }

  free( x );
  free( y );
  free( r );
}

void test_mpn_sub( int n, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= n; i++ ) {
    test_id( "test_mpn", "sub", i, n );

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );
  
    if( mpn_cmp( x, l_x, y, l_y ) >= 0 ) {
      l_r = MAX( l_x, l_y ) + 1; 
      TEST_MEASURE( r[ l_r - 1 ] = mpn_sub( r, x, l_x, y, l_y ) );
      l_r = mpn_lop( r, l_r );
    } 
    else {
      l_r = MAX( l_y, l_x ) + 1; 
      TEST_MEASURE( r[ l_r - 1 ] = mpn_sub( r, y, l_y, x, l_x ) );
      l_r = mpn_lop( r, l_r );
    }

    test_mpn_dump( "r", r, l_r );

    if( mpn_cmp( x, l_x, y, l_y ) >= 0 ) {
      printf( "t = x - y                            " "\n"   );
    }
    else {
      printf( "t = y - x                            " "\n"   );
    }

      printf( "if ( r != t ) :                      " "\n"   );
      printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }

  free( x );
  free( y );
  free( r );
}

void test_mpn_mul( int n, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= n; i++ ) {
    test_id( "test_mpn", "mul", i, n );

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );

    l_r = l_x + l_y;
    TEST_MEASURE( mpn_mul( r, x, l_x, y, l_y ) );
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "r", r, l_r );
    
      printf( "t = x * y                            " "\n"   );

      printf( "if ( r != t ) :                      " "\n"   );
      printf( "  print( 'fail %%s' %% ( id       ) )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }

  free( x );
  free( y );
  free( r );
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys" );

  test_mpn_add( opt_trials, opt_mp_mpn_min_limb, opt_mp_mpn_max_limb );
  test_mpn_sub( opt_trials, opt_mp_mpn_min_limb, opt_mp_mpn_max_limb );
  test_mpn_mul( opt_trials, opt_mp_mpn_min_limb, opt_mp_mpn_max_limb );

  test_fini();

  return 0;
}

// ============================================================================
