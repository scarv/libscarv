/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "util.h"

int   opt_debug    =    1;
int   opt_trials   = 1000;

int   opt_data_min =    0;
int   opt_data_max = 1024;
int   opt_limb_min =    4;
int   opt_limb_max =   16;

FILE* prg          = NULL;

void opt_parse( int argc, char* argv[] ) {
  int opt;

  struct option optspec[] = {
    { "help",     no_argument,       NULL, OPT_HELP     },

    { "debug",    required_argument, NULL, OPT_DEBUG    },
    { "trials",   required_argument, NULL, OPT_TRIALS   },

    { "data-min", required_argument, NULL, OPT_DATA_MIN },
    { "data-max", required_argument, NULL, OPT_DATA_MAX },
    { "limb-min", required_argument, NULL, OPT_LIMB_MIN },
    { "limb-max", required_argument, NULL, OPT_LIMB_MAX },

    { NULL,       0,                 NULL, 0            }
  };

  while( -1 != ( opt = getopt_long( argc, argv, "+", optspec, NULL ) ) ) {
    switch( opt ) {
      case OPT_HELP     : fprintf( stderr, "usage: %s [options]                                         " "\n", argv[ 0 ] );
                          fprintf( stderr, "                                                            " "\n"            );
                          fprintf( stderr, "--help             print usage information                  " "\n"            );
                          fprintf( stderr, "                                                            " "\n"            );
                          fprintf( stderr, "--debug    <int>   verbosity of debug output                " "\n"            );
                          fprintf( stderr, "--trials   <int>   number of (randomised) trials            " "\n"            );
                          fprintf( stderr, "                                                            " "\n"            );
                          fprintf( stderr, "--data-min <int>   minimum bytes of data (where appropriate)" "\n"            );
                          fprintf( stderr, "--data-max <int>   maximum bytes of data (where appropriate)" "\n"            );
                          fprintf( stderr, "--limb-min <int>   minimum limbs         (where appropriate)" "\n"            );
                          fprintf( stderr, "--limb-max <int>   maximum limbs         (where appropriate)" "\n"            );
                             
                          exit( EXIT_SUCCESS ); 
                          break;

      case OPT_DEBUG    : opt_debug    = strtoul( optarg, NULL, 10 );
                          break;
      case OPT_TRIALS   : opt_trials   = strtoul( optarg, NULL, 10 );
                          break;

      case OPT_DATA_MIN : opt_data_min = strtoul( optarg, NULL, 10 );
                          break;
      case OPT_DATA_MAX : opt_data_max = strtoul( optarg, NULL, 10 );
                          break;
      case OPT_LIMB_MIN : opt_limb_min = strtoul( optarg, NULL, 10 );
                          break;
      case OPT_LIMB_MAX : opt_limb_max = strtoul( optarg, NULL, 10 );
                          break;

      default           : exit( EXIT_FAILURE ); 
                          break;
    }
  }
}

void test_dump_seq( uint8_t* x, int l_x, int mode ) {
  switch( mode ) {
    case DUMP_LSB: for( int i = 0; i <= ( l_x - 1 ); i++ ) {
                     printf( "%02X", x[ i ] );
                   }
                   break;

    case DUMP_MSB: for( int i = ( l_x - 1 ); i >= 0; i-- ) {
                     printf( "%02X", x[ i ] );
                   }
                   break;
  }
}

int test_rand_seq( uint8_t* x, int l_x_min, int l_x_max, int size ) {
  return fread( x, size, ( l_x_min >= l_x_max ) ? ( l_x_min ) : ( ( abs( test_rand_int() ) % ( l_x_max + 1 - l_x_min ) ) + l_x_min ), prg );
}

int test_rand_int() {
  int t;

  while( !fread( &t, sizeof( int ), 1, prg ) ) {
    /* spin */
  }

  return t;
}

void test_id( char* x, char* y, int i, int n ) {
  printf( "id = '%s:%s[%d/%d]'\n", x, y, i, n );
}

void test_init( int argc, char* argv[], char* import ) {
  opt_parse( argc, argv );

  if( NULL == ( prg = fopen( "/dev/urandom", "rb" ) ) ) {
    abort();
  }

  printf( "import %s\n", import );
}

void test_fini() {
  fclose( prg );
}


