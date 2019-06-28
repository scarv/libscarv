#include "util.h"

int   opt_debug           =    1;

int   opt_trials          = 1000;
char  opt_prg[ 80 ]       = "/dev/urandom";

int   opt_mpn_min_limb =    4;
int   opt_mpn_max_limb =   16;
int   opt_mpz_min_limb =    4;
int   opt_mpz_max_limb =   16;
int   opt_mrz_min_limb =    4;
int   opt_mrz_max_limb =   32;

int   opt_sha1_min_data   =    0;
int   opt_sha1_max_data   = 1024;
int   opt_sha2_min_data   =    0;
int   opt_sha2_max_data   = 1024;

FILE* prg                 = NULL;

void opt_parse( int argc, char* argv[] ) {
  int opt;

  struct option optspec[] = {
    { "help",          no_argument,       NULL, OPT_HELP          },
    { "debug",         required_argument, NULL, OPT_DEBUG         },

    { "trials",        required_argument, NULL, OPT_TRIALS        },
    { "prg",           required_argument, NULL, OPT_PRG           },

    { "mpn-min-limb",  required_argument, NULL, OPT_MPN_MIN_LIMB  },
    { "mpn-max-limb",  required_argument, NULL, OPT_MPN_MAX_LIMB  },
    { "mpz-min-limb",  required_argument, NULL, OPT_MPZ_MIN_LIMB  },
    { "mpz-max-limb",  required_argument, NULL, OPT_MPZ_MAX_LIMB  },
    { "mrz-min-limb",  required_argument, NULL, OPT_MRZ_MIN_LIMB  },
    { "mrz-max-limb",  required_argument, NULL, OPT_MRZ_MAX_LIMB  },

    { "sha1-min-data", required_argument, NULL, OPT_SHA1_MIN_DATA },
    { "sha1-max-data", required_argument, NULL, OPT_SHA1_MAX_DATA },
    { "sha2-min-data", required_argument, NULL, OPT_SHA2_MIN_DATA },
    { "sha2-max-data", required_argument, NULL, OPT_SHA2_MAX_DATA },

    { NULL,            0,                 NULL, 0                 }
  };

  while( -1 != ( opt = getopt_long( argc, argv, "+", optspec, NULL ) ) ) {
    switch( opt ) {
      case OPT_HELP          : fprintf( stderr, "usage: %s [options]                                           " "\n", argv[ 0 ] );
                               fprintf( stderr, "                                                              " "\n"            );
                               fprintf( stderr, "--help                    print usage information             " "\n"            );
                               fprintf( stderr, "--debug           <int>   verbosity of debug output           " "\n"            );
                               fprintf( stderr, "                                                              " "\n"            );
                               fprintf( stderr, "--trials          <int>   number of (randomised) trials       " "\n"            );
                               fprintf( stderr, "--prg             <file>  source of randomness                " "\n"            );
                               fprintf( stderr, "                                                              " "\n"            );
                               fprintf( stderr, "--mpn-min-limb <int>   minimum number of limbs for mpn        " "\n"            );
                               fprintf( stderr, "--mpn-max-limb <int>   maximum number of limbs for mpn        " "\n"            );
                               fprintf( stderr, "--mpz-min-limb <int>   minimum number of limbs for mpz        " "\n"            );
                               fprintf( stderr, "--mpz-max-limb <int>   maximum number of limbs for mpz        " "\n"            );
                               fprintf( stderr, "--mrz-min-limb <int>   minimum number of limbs for mrz        " "\n"            );
                               fprintf( stderr, "--mrz-max-limb <int>   maximum number of limbs for mrz        " "\n"            );
                               fprintf( stderr, "                                                              " "\n"            );
                               fprintf( stderr, "--sha1-min-data   <int>   minimum bytes of input data for SHA1" "\n"            );
                               fprintf( stderr, "--sha1-max-data   <int>   maximum bytes of input data for SHA1" "\n"            );
                               fprintf( stderr, "--sha2-min-data   <int>   minimum bytes of input data for SHA2" "\n"            );
                               fprintf( stderr, "--sha2-max-data   <int>   maximum bytes of input data for SHA2" "\n"            );
                             
                               exit( EXIT_SUCCESS ); 
                               break;

      case OPT_DEBUG         : opt_debug           = strtoul( optarg, NULL, 10 );
                               break;

      case OPT_TRIALS        : opt_trials          = strtoul( optarg, NULL, 10 );
                               break;

      case OPT_MPN_MIN_LIMB  : opt_mpn_min_limb = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_MPN_MAX_LIMB  : opt_mpn_max_limb = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_MPZ_MIN_LIMB  : opt_mpz_min_limb = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_MPZ_MAX_LIMB  : opt_mpz_max_limb = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_MRZ_MIN_LIMB  : opt_mrz_min_limb = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_MRZ_MAX_LIMB  : opt_mrz_max_limb = strtoul( optarg, NULL, 10 );
                               break;

      case OPT_SHA1_MIN_DATA : opt_sha1_min_data   = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_SHA1_MAX_DATA : opt_sha1_max_data   = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_SHA2_MIN_DATA : opt_sha2_min_data   = strtoul( optarg, NULL, 10 );
                               break;
      case OPT_SHA2_MAX_DATA : opt_sha2_max_data   = strtoul( optarg, NULL, 10 );
                               break;

      default                : exit( EXIT_FAILURE ); 
                               break;
    }
  }
}

void test_dump_lsb( uint8_t* x, int l_x ) {
  for( int i = 0; i < l_x; i++ ) {
    printf( "%02X", x[ i ] );
  }
}

void test_dump_msb( uint8_t* x, int l_x ) {
  for( int i = l_x - 1; i >= 0; i-- ) {
    printf( "%02X", x[ i ] );
  }
}

int test_rand_int() {
  int t;

  while( !fread( &t, sizeof( int ), 1, prg ) ) {
    /* spin */
  }

  return t;
}

int test_rand_seq( uint8_t* x, int l_x_min, int l_x_max, int size ) {
  return fread( x, size, ( l_x_min >= l_x_max ) ? ( l_x_min ) : ( ( abs( test_rand_int() ) % ( l_x_max + 1 - l_x_min ) ) + l_x_min ), prg );
}

void test_id( char* x, char* y, int i, int n ) {
  printf( "id = '%s:%s[%d/%d]'\n", x, y, i, n );
}

void test_init( int argc, char* argv[], char* import ) {
  opt_parse( argc, argv );

  if( NULL == ( prg = fopen( opt_prg, "rb" ) ) ) {
    abort();
  }

  printf( "import %s\n", import );
}

void test_fini() {
  fclose( prg );
}


