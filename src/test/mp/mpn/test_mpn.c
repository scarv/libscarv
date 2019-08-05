/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "test_mpn.h"

// ============================================================================

void test_mpn_dump( char* id, limb_t* x, int l_x ) {
  printf( "%s = int( '", id ); test_dump_seq( ( uint8_t* )( x ), l_x * sizeof( limb_t ), DUMP_MSB ); printf( "', 16 )\n" );
}

// ============================================================================

void test_mpn_add( int trials, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpn", "add", i, trials );

    l_x = test_rand_seq( ( uint8_t* )( x ), l_min, l_max, sizeof( limb_t ) );
    l_y = test_rand_seq( ( uint8_t* )( y ), l_min, l_max, sizeof( limb_t ) );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );

    l_r = MAX( l_x, l_y ) + 1; 
    MEASURE( r[ l_r - 1 ] = mpn_add( r, x, l_x, y, l_y ) );
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "r", r, l_r );

      printf( "l_x = %d\n", l_x);
      printf( "l_y = %d\n", l_y);
      printf( "l_r = %d\n", l_r);
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

void test_mpn_sub( int trials, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpn", "sub", i, trials );

    l_x = test_rand_seq( ( uint8_t* )( x ), l_min, l_max, sizeof( limb_t ) );
    l_y = test_rand_seq( ( uint8_t* )( y ), l_min, l_max, sizeof( limb_t ) );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );
  
    if( mpn_cmp( x, l_x, y, l_y ) >= 0 ) {
      l_r = MAX( l_x, l_y ) + 1; 
      MEASURE( r[ l_r - 1 ] = mpn_sub( r, x, l_x, y, l_y ) );
      l_r = mpn_lop( r, l_r );
    } 
    else {
      l_r = MAX( l_y, l_x ) + 1; 
      MEASURE( r[ l_r - 1 ] = mpn_sub( r, y, l_y, x, l_x ) );
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

void test_mpn_mul( int trials, int l_min, int l_max ) {
  limb_t* x = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_x;
  limb_t* y = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_y;
  limb_t* r = ( limb_t* )( malloc( ( 2 * l_max + 2 ) * sizeof( limb_t ) ) ); int l_r;

  for( int i = 1; i <= trials; i++ ) {
    test_id( "test_mpn", "mul", i, trials );

    l_x = test_rand_seq( ( uint8_t* )( x ), l_min, l_max, sizeof( limb_t ) );
    l_y = test_rand_seq( ( uint8_t* )( y ), l_min, l_max, sizeof( limb_t ) );

    test_mpn_dump( "x", x, l_x );
    test_mpn_dump( "y", y, l_y );

    l_r = l_x + l_y;
    MEASURE( mpn_mul( r, x, l_x, y, l_y ) );
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

  test_mpn_add( opt_trials, opt_limb_min, opt_limb_max );
  test_mpn_sub( opt_trials, opt_limb_min, opt_limb_max );
  test_mpn_mul( opt_trials, opt_limb_min, opt_limb_max );

  test_fini();

  return 0;
}

// ============================================================================
