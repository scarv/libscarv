#include "test_mpz.h"

void test_mpz_rand( mpz_t* r, int l_min, int l_max ) {
  r->l = ( rand() % ( l_max + 1 - l_min) ) + l_min;
  r->s = ( rand() & 1 ) ? MPZ_SIGN_POS : MPZ_SIGN_NEG;

  FILE* fd = fopen( "/dev/urandom", "rb" ); fread( r->d, sizeof( limb_t ), r->l, fd ); fclose( fd );
} 

void test_mpz_dump( char* id, mpz_t* x ) {
  printf( "%s = %c long( '", id, ( x->s == MPZ_SIGN_POS ) ? '+' : '-' );

  for( int i = x->l - 1; i >= 0; i-- ) {
    printf( "%08X", x->d[ i ] );
  }

  printf( "', 16 )\n" );
}

void test_mpz( int n, int l_min, int l_max ) {
  for( int i = 0; i < n; i++ ) {
    printf("# mpz add %d / %d\n",i,n);
    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    mpz_add( &r, &x, &y );

    test_mpz_dump( "x", &x );  
    test_mpz_dump( "y", &y );  
    test_mpz_dump( "r", &r );  

    printf( "t = x + y                         " "\n" );

    printf( "if( r != t ) :                    " "\n" );
    printf( "  print 'failed test_mpz: add '   " "\n" );
    printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
    printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
    printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
    printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
  }

  for( int i = 0; i < n; i++ ) {
    printf("# mpz sub %d / %d\n",i,n);
    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    mpz_sub( &r, &x, &y );

    test_mpz_dump( "x", &x );  
    test_mpz_dump( "y", &y );  
    test_mpz_dump( "r", &r );  

    printf( "t = x - y                         " "\n" );

    printf( "if( r != t ) :                    " "\n" );
    printf( "  print 'failed test_mpz: sub'    " "\n" );
    printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
    printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
    printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
    printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
  }

  for( int i = 0; i < n; i++ ) {
    printf("# mpz mul %d / %d\n",i,n);
    mpz_t x;
    mpz_t y;
    mpz_t r;

    test_mpz_rand( &x, l_min, l_max );
    test_mpz_rand( &y, l_min, l_max );

    mpz_mul( &r, &x, &y );

    test_mpz_dump( "x", &x );  
    test_mpz_dump( "y", &y );  
    test_mpz_dump( "r", &r );  

    printf( "t = x * y                         " "\n" );

    printf( "if( r != t ) :                    " "\n" );
    printf( "  print 'failed test_mpz: mul'    " "\n" );
    printf( "  print 'x == %%s' %% ( hex( x ) )" "\n" );
    printf( "  print 'y == %%s' %% ( hex( y ) )" "\n" );
    printf( "  print 'r == %%s' %% ( hex( r ) )" "\n" );
    printf( "  print '  != %%s' %% ( hex( t ) )" "\n" );
  }
}


int main(int argc, char ** argv) {
    test_mpz(10,1,16);
}
