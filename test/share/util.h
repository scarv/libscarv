#ifndef __TEST_UTIL_H
#define __TEST_UTIL_H

#include <stdbool.h>
#include  <stdint.h>
#include   <stdio.h>
#include  <stdlib.h>

#include  <getopt.h>
#include  <string.h>
#include    <math.h>

#define DEBUG_LEVEL_1       (    1 )
#define DEBUG_LEVEL_2       (    2 )
#define DEBUG_LEVEL_3       (    3 )

#define OPT_HELP            (    2 )
#define OPT_DEBUG           (    3 )

#define OPT_TRIALS          (    4 )

#define OPT_MP_MPN_MIN_LIMB (    5 )
#define OPT_MP_MPN_MAX_LIMB (    6 )
#define OPT_MP_MPZ_MIN_LIMB (    7 )
#define OPT_MP_MPZ_MAX_LIMB (    8 )
#define OPT_MP_MRZ_MIN_LIMB (    9 )
#define OPT_MP_MRZ_MAX_LIMB (   10 )

extern int opt_debug;

extern int opt_trials;

extern int opt_mp_mpn_min_limb;
extern int opt_mp_mpn_max_limb;
extern int opt_mp_mpz_min_limb;
extern int opt_mp_mpz_max_limb;
extern int opt_mp_mrz_min_limb;
extern int opt_mp_mrz_max_limb;

extern void opt_usage( int argc, char* argv[] );
extern void opt_parse( int argc, char* argv[] );

#if   defined( LIBSCARV_ARCH_GENERIC       )
  #define MEASURE(stmt) {                                     \
    stmt;                                                     \
  }
#elif defined( LIBSCARV_ARCH_RISCV         )
  #define MEASURE(stmt) {                                     \
    uint32_t   cycle_pre,   cycle_post;                       \
    uint32_t instret_pre, instret_post;                       \
                                                              \
    asm volatile( "rdinstret %0" : "=r" (instret_pre)  );     \
    asm volatile( "rdcycle   %0" : "=r"   (cycle_pre)  );     \
    stmt;                                                     \
    asm volatile( "rdcycle   %0" : "=r"   (cycle_post) );     \
    asm volatile( "rdinstret %0" : "=r" (instret_post) );     \
                                                              \
    printf( "# cycles = %lu\n",   cycle_post -   cycle_pre ); \
    printf( "# instrs = %lu\n", instret_post - instret_pre ); \
  }
#elif defined( LIBSCARV_ARCH_RISCV_XCRYPTO )
  #define MEASURE(stmt) {                                     \
    uint32_t   cycle_pre,   cycle_post;                       \
    uint32_t instret_pre, instret_post;                       \
                                                              \
    asm volatile( "rdinstret %0" : "=r" (instret_pre)  );     \
    asm volatile( "rdcycle   %0" : "=r"   (cycle_pre)  );     \
    stmt;                                                     \
    asm volatile( "rdcycle   %0" : "=r"   (cycle_post) );     \
    asm volatile( "rdinstret %0" : "=r" (instret_post) );     \
                                                              \
    printf( "# cycles = %lu\n",   cycle_post -   cycle_pre ); \
    printf( "# instrs = %lu\n", instret_post - instret_pre ); \
  }
#else
  #define MEASURE(stmt) {                                     \
    stmt;                                                     \
  }
#endif

#endif
