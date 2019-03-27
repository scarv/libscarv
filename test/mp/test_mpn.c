
#include "test_util.h"

#include "test_mpn.h"

int test_mpn_rand( limb_t* r, int l_min, int l_max ) {
  int l_r = ( rand() % ( l_max + 1 - l_min) ) + l_min;

  FILE* fd = fopen( "/dev/urandom", "rb" );
  fread( r, sizeof( limb_t ), l_r, fd );
  fclose( fd );

  return l_r;
} 

void test_mpn_dump( char* id, limb_t* x, int l_x ) {
  printf( "%s = long( '", id );

  for( int i = l_x - 1; i >= 0; i-- ) {
    printf( "%08X", x[ i ] );
  }

  printf( "', 16 )\n" );
}

void test_mpn( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    
    printf("# mpn add %d / %d\n",i,n);

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

    l_r = MAX( l_x, l_y ) + 1; 

    uint32_t count_c = test_util_rdcycle();
    uint32_t count_i = test_util_rdinstret();

    r[ l_r - 1 ] = mpn_add( r, x, l_x, y, l_y ); 

    count_c = test_util_rdcycle()  - count_c;
    count_i = test_util_rdinstret()- count_i;

    l_r = mpn_lop( r, l_r );

    printf("# cycles = %lu\n", count_c);
    printf("# instrs = %lu\n", count_i);
    printf("# l_r, l_x, l_y = %lu, %lu, %lu\n", l_r, l_x, l_y);
    test_mpn_dump( "x", x, l_x );  
    test_mpn_dump( "y", y, l_y );  
    test_mpn_dump( "r", r, l_r );  

      printf( "t = x + y                         " "\n" );
  
      printf( "if( r != t ) :                    " "\n" );
      printf( "  print 'failed test_mpn: add '   " "\n" );
      printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
      printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
      printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
      printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
      printf( "  sys.exit(1)\n\n");
  }

  for( int i = 0; i < n; i++ ) {
    printf("# mpn cmp %d / %d\n",i,n);

    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );
  
    if( mpn_cmp( x, l_x, y, l_y ) >= 0 ) {
      l_r = MAX( l_x, l_y ) + 1; 
      r[ l_r - 1 ] = mpn_sub( r, x, l_x, y, l_y ); 
      l_r = mpn_lop( r, l_r );
    } 
    else {
      l_r = MAX( l_y, l_x ) + 1; 
      r[ l_r - 1 ] = mpn_sub( r, y, l_y, x, l_x ); 
      l_r = mpn_lop( r, l_r );
    }

    test_mpn_dump( "x", x, l_x );  
    test_mpn_dump( "y", y, l_y );  
    test_mpn_dump( "r", r, l_r );  

    if( mpn_cmp( x, l_x, y, l_y ) >= 0 ) {
      printf( "t = x - y                         " "\n" );
    }
    else {
      printf( "t = y - x                         " "\n" );
    }

      printf( "if( r != t ) :                    " "\n" );
      printf( "  print 'failed test_mpn: sub'    " "\n" );
      printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
      printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
      printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
      printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
      printf( "  sys.exit(1)\n\n");
  }

  for( int i = 0; i < n; i++ ) {
    printf("# mpn mul %d / %d\n",i,n);
    limb_t x[ 2 * l_max + 2 ]; int l_x;
    limb_t y[ 2 * l_max + 2 ]; int l_y;
    limb_t r[ 2 * l_max + 2 ]; int l_r;

    l_x = test_mpn_rand( x, l_min, l_max );
    l_y = test_mpn_rand( y, l_min, l_max );

      l_r = l_x + l_y;
    
    uint32_t count_c = test_util_rdcycle();
    uint32_t count_i = test_util_rdinstret();
    
    mpn_mul( r, x, l_x, y, l_y ); 

    count_c = test_util_rdcycle()  - count_c;
    count_i = test_util_rdinstret()- count_i;

    printf("# cycles = %lu\n", count_c);
    printf("# instrs = %lu\n", count_i);
    printf("# l_r, l_x, l_y = %lu, %lu, %lu\n", l_r, l_x, l_y);
    
    l_r = mpn_lop( r, l_r );

    test_mpn_dump( "x", x, l_x );  
    test_mpn_dump( "y", y, l_y );  
    test_mpn_dump( "r", r, l_r );  

      printf( "t = x * y                         " "\n" );

      printf( "if( r != t ) :                    " "\n" );
      printf( "  print 'failed test_mpn: mul'    " "\n" );
      printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
      printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
      printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
      printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
      printf( "  sys.exit(1)\n\n");
  }
}

int main(int argc, char ** argv) {
    printf("import sys\n");
    test_mpn(10,1,16);
}

