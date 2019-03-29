#include "util.h"

int opt_debug           =     1;

int opt_trials          = 10000;

int opt_mp_mpn_min_limb =     4;
int opt_mp_mpn_max_limb =    32;
int opt_mp_mpz_min_limb =     4;
int opt_mp_mpz_max_limb =    32;
int opt_mp_mrz_min_limb =     4;
int opt_mp_mrz_max_limb =    32;

void opt_usage( int argc, char* argv[] ) {
  fprintf( stderr, "usage: %s [options]                                     " "\n", argv[ 0 ] );
  fprintf( stderr, "                                                        " "\n"            );
  fprintf( stderr, "--help                   print usage information        " "\n"            );
  fprintf( stderr, "--debug           <int>  verbosity of debug output      " "\n"            );
  fprintf( stderr, "                                                        " "\n"            );
  fprintf( stderr, "--trials          <int>  number of (randomised) trials  " "\n"            );
  fprintf( stderr, "                                                        " "\n"            );
  fprintf( stderr, "--mp-mpn-min-limb <int>  minimum number of limbs for mpn" "\n"            );
  fprintf( stderr, "--mp-mpn-max-limb <int>  maximum number of limbs for mpn" "\n"            );
  fprintf( stderr, "--mp-mpz-min-limb <int>  minimum number of limbs for mpz" "\n"            );
  fprintf( stderr, "--mp-mpz-max-limb <int>  maximum number of limbs for mpz" "\n"            );
  fprintf( stderr, "--mp-mrz-min-limb <int>  minimum number of limbs for mrz" "\n"            );
  fprintf( stderr, "--mp-mrz-max-limb <int>  maximum number of limbs for mrz" "\n"            );

  exit( EXIT_SUCCESS ); 
}

void opt_parse( int argc, char* argv[] ) {
  int opt;

  struct option optspec[] = {
    { "help",            no_argument,       NULL, OPT_HELP            },
    { "debug",           required_argument, NULL, OPT_DEBUG           },

    { "trials",          required_argument, NULL, OPT_TRIALS          },

    { "mp-mpn-min-limb", required_argument, NULL, OPT_MP_MPN_MIN_LIMB },
    { "mp-mpn-max-limb", required_argument, NULL, OPT_MP_MPN_MAX_LIMB },
    { "mp-mpz-min-limb", required_argument, NULL, OPT_MP_MPZ_MIN_LIMB },
    { "mp-mpz-max-limb", required_argument, NULL, OPT_MP_MPZ_MAX_LIMB },
    { "mp-mrz-min-limb", required_argument, NULL, OPT_MP_MRZ_MIN_LIMB },
    { "mp-mrz-max-limb", required_argument, NULL, OPT_MP_MRZ_MAX_LIMB },

    { NULL,           0,                 NULL, 0                      }
  };

  while( -1 != ( opt = getopt_long( argc, argv, "+", optspec, NULL ) ) ) {
    switch( opt ) {
      case OPT_HELP            : opt_usage( argc, argv );
                                 break;
      case OPT_DEBUG           : opt_debug           = strtoul( optarg, NULL, 10 );
                                 break;

      case OPT_TRIALS          : opt_trials          = strtoul( optarg, NULL, 10 );
                                 break;

      case OPT_MP_MPN_MIN_LIMB : opt_mp_mpn_min_limb = strtoul( optarg, NULL, 10 );
                                 break;
      case OPT_MP_MPN_MAX_LIMB : opt_mp_mpn_max_limb = strtoul( optarg, NULL, 10 );
                                 break;
      case OPT_MP_MPZ_MIN_LIMB : opt_mp_mpz_min_limb = strtoul( optarg, NULL, 10 );
                                 break;
      case OPT_MP_MPZ_MAX_LIMB : opt_mp_mpz_max_limb = strtoul( optarg, NULL, 10 );
                                 break;
      case OPT_MP_MRZ_MIN_LIMB : opt_mp_mrz_min_limb = strtoul( optarg, NULL, 10 );
                                 break;
      case OPT_MP_MRZ_MAX_LIMB : opt_mp_mrz_max_limb = strtoul( optarg, NULL, 10 );
                                 break;

      default                  : exit( EXIT_FAILURE ); 
                                 break;
    }
  }
}
