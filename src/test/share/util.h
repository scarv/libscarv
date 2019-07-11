/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __UTIL_H
#define __UTIL_H

#include <stdbool.h>
#include  <stdint.h>
#include   <stdio.h>
#include  <stdlib.h>

#include  <getopt.h>
#include  <string.h>
#include    <math.h>

#include <scarv/scarv.h>

#define DUMP_LSB      (  0 )
#define DUMP_MSB      (  1 )

#define DEBUG_LEVEL_1 (  1 )
#define DEBUG_LEVEL_2 (  2 )
#define DEBUG_LEVEL_3 (  3 )

#define OPT_HELP      (  2 )
#define OPT_DEBUG     (  3 )
#define OPT_TRIALS    (  4 )
#define OPT_DATA_MIN  (  5 )
#define OPT_DATA_MAX  (  6 )
#define OPT_LIMB_MIN  (  7 )
#define OPT_LIMB_MAX  (  8 )

#if   ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_NATIVE        )
  #define MEASURE(stmt) {                                     \
    stmt;                                                     \
  }
#elif ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV         )
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
#elif ( LIBSCARV_CONF_ARCH == LIBSCARV_CONF_ARCH_RISCV_XCRYPTO )
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
  #define TEST_MEASURE(stmt) {                                \
    stmt;                                                     \
  }
#endif

extern int opt_debug;

extern int opt_trials;

extern int opt_data_min;
extern int opt_data_max;
extern int opt_limb_min;
extern int opt_limb_max;

void test_dump_seq( uint8_t* x, int l_x, int mode );

int  test_rand_int();
int  test_rand_seq( uint8_t* x, int l_x_min, int l_x_max, int size );

void test_id( char* x, char* y, int i, int n );

void test_init( int argc, char* argv[], char* import );
void test_fini();

#endif
