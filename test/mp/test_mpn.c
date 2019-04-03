#include "test_mpn.h"

// ============================================================================

int test_mpn_rand( limb_t* r, int l_r_min, int l_r_max ) {
  return test_rand_byte( ( uint8_t* )( r ), sizeof( limb_t ), l_r_min, l_r_max );
}

void test_mpn_dump( char* id, limb_t* x, int l_x ) {
  printf( "%s = int( '", id ); test_dump_msb( ( uint8_t* )( x ), l_x * sizeof( limb_t ) ); printf( "', 16 )\n" );
}

// ============================================================================

void test_mpn_add( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpn", "add", i, n );

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

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
}

void test_mpn_sub( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpn", "sub", i, n );

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

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
}

void test_mpn_mul( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    test_id( "test_mpn", "mul", i, n );

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

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
}

// ============================================================================

int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys" );

  int l_min = opt_mp_mpn_min_limb;
  int l_max = opt_mp_mpn_max_limb;

  test_mpn_add( opt_trials, l_min, l_max );
  test_mpn_sub( opt_trials, l_min, l_max );
  test_mpn_mul( opt_trials, l_min, l_max );

  test_fini();

  return 0;
}

// ============================================================================
