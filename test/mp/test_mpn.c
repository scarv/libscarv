#include "test_mpn.h"

FILE* urandom = NULL;

// ----------------------------------------------------------------------------

int  test_mpn_rand( limb_t* r, int l_min, int l_max ) {
  uint8_t t;

  fread( &t, sizeof( uint8_t ), 1, urandom );

  int l_r = ( t % ( l_max + 1 - l_min) ) + l_min;

  fread( r, sizeof( limb_t ), l_r, urandom );

  return l_r;
} 

void test_mpn_dump( char* id, limb_t* x, int l_x ) {
  printf( "%s = int( '", id );

  for( int i = l_x - 1; i >= 0; i-- ) {
    printf( "%08lX", x[ i ] );
  }

  printf( "', 16 )\n" );
}

// ----------------------------------------------------------------------------

void test_mpn_add( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf("# test_mpn:mpn_add %d / %d\n", i, n );

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    test_mpn_dump( "x", x, l_x );  
    test_mpn_dump( "y", y, l_y );  

    l_r = MAX( l_x, l_y ) + 1; 
    MEASURE( r[ l_r - 1 ] = mpn_add( r, x, l_x, y, l_y ) );
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "r", r, l_r );  

      printf( "t = x + y                            " "\n"   );
    
      printf( "if( r != t ) :                       " "\n"   );
      printf( "  print( 'failed test_mpn:mpn_add'  )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

void test_mpn_sub( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf("# test_mpn:mpn_sub %d / %d\n", i, n);

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

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

      printf( "if( r != t ) :                       " "\n"   );
      printf( "  print( 'failed test_mpn:mpn_sub'  )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

void test_mpn_mul( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf("# test_mpn:mpn_mul %d / %d\n", i, n );

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    test_mpn_dump( "x", x, l_x );  
    test_mpn_dump( "y", y, l_y );  

    l_r = l_x + l_y;
    MEASURE( mpn_mul( r, x, l_x, y, l_y ) );
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "r", r, l_r );  
    
      printf( "t = x * y                            " "\n"   );

      printf( "if( r != t ) :                       " "\n"   );
      printf( "  print( 'failed test_mpn:mpn_mul'  )" "\n"   );
      printf( "  print( 'x == %%s' %% ( hex( x ) ) )" "\n"   );
      printf( "  print( 'y == %%s' %% ( hex( y ) ) )" "\n"   );
      printf( "  print( 'r == %%s' %% ( hex( r ) ) )" "\n"   );
      printf( "  print( '  != %%s' %% ( hex( t ) ) )" "\n"   );

      printf( "  sys.exit( 1 )                      " "\n\n" );
  }
}

// ----------------------------------------------------------------------------

int main( int argc, char* argv[] ) {
  printf( "import sys\n" );

  if( NULL == ( urandom = fopen( "/dev/urandom", "rb" ) ) ) {
    abort();
  }

  test_mpn_add( 1000, 1, 16 );
  test_mpn_sub( 1000, 1, 16 );
  test_mpn_mul( 1000, 1, 16 );

  fclose( urandom );

  return 0;
}

// ----------------------------------------------------------------------------
