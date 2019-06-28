#ifndef __TEST_UTIL_H
#define __TEST_UTIL_H

#include <stdbool.h>
#include  <stdint.h>
#include   <stdio.h>
#include  <stdlib.h>

#include  <getopt.h>
#include  <string.h>
#include    <math.h>

#include <scarv/scarv.h>

#define DEBUG_LEVEL_1     (    1 )
#define DEBUG_LEVEL_2     (    2 )
#define DEBUG_LEVEL_3     (    3 )

#define OPT_HELP          (    2 )
#define OPT_DEBUG         (    3 )

#define OPT_TRIALS        (    4 )
#define OPT_PRG           (    5 )

#define OPT_MPN_MIN_LIMB  (    6 )
#define OPT_MPN_MAX_LIMB  (    7 )
#define OPT_MPZ_MIN_LIMB  (    8 )
#define OPT_MPZ_MAX_LIMB  (    9 )
#define OPT_MRZ_MIN_LIMB  (   10 )
#define OPT_MRZ_MAX_LIMB  (   11 )

#define OPT_SHA1_MIN_DATA (   12 )
#define OPT_SHA1_MAX_DATA (   13 )
#define OPT_SHA2_MIN_DATA (   14 )
#define OPT_SHA2_MAX_DATA (   15 )

#if   ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_NATIVE        )
  #define TEST_MEASURE(stmt) {                                \
    stmt;                                                     \
  }
#elif ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV         )
  #define TEST_MEASURE(stmt) {                                \
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
#elif ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV_XCRYPTO )
  #define TEST_MEASURE(stmt) {                                \
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
  #define TEST_MEASURE(stmt) {                                \
    stmt;                                                     \
  }
#endif

extern int opt_debug;

extern int opt_trials;

extern int opt_mpn_min_limb;
extern int opt_mpn_max_limb;
extern int opt_mpz_min_limb;
extern int opt_mpz_max_limb;
extern int opt_mrz_min_limb;
extern int opt_mrz_max_limb;

extern int opt_sha1_min_data;
extern int opt_sha1_max_data;
extern int opt_sha2_min_data;
extern int opt_sha2_max_data;

void test_dump_lsb( uint8_t* x, int l_x );
void test_dump_msb( uint8_t* x, int l_x );

int test_rand_int();
int test_rand_seq( uint8_t* x, int s, int l_x_min, int l_x_max );

void test_id( char* x, char* y, int i, int n );

void test_init( int argc, char* argv[], char* import );
void test_fini();

#endif
