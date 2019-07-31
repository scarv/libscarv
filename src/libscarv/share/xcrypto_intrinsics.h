
#include <stdint.h>

#ifndef __XCRYPTO_INTRINSICS__
#define __XCRYPTO_INTRINSICS__

#if !defined(__riscv_xlen)
    #define XCRYPTO_EMULATE 1
#endif

#ifndef XCRYPTO_EMULATE

#if __riscv_xlen == 32
#  define XCRYPTO_RV32
#endif

#if __riscv_xlen == 64
#  define XCRYPTO_RV64
#endif

//
// Indexed Load and Store
//

#if defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)
static inline   int8_t _xc_ldr_b (  int8_t* rs1, size_t rs2) {  int8_t rd; __asm__ ("xc.ldr.b  %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline  uint8_t _xc_ldr_bu( uint8_t* rs1, size_t rs2) { uint8_t rd; __asm__ ("xc.ldr.bu %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline  int16_t _xc_ldr_h ( int16_t* rs1, size_t rs2) { int16_t rd; __asm__ ("xc.ldr.h  %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline uint16_t _xc_ldr_hu(uint16_t* rs1, size_t rs2) {uint16_t rd; __asm__ ("xc.ldr.hu %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline  int32_t _xc_ldr_w ( int32_t* rs1, size_t rs2) { int32_t rd; __asm__ ("xc.ldr.w  %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}

static inline void     _xc_str_b (  int8_t* rs1, size_t rs2,  int8_t rs3) {__asm__ ("xc.str.b  %0, %1(%2)" : : "r"(rs3), "r"(rs1) , "r"(rs2));}
static inline void     _xc_str_h ( int16_t* rs1, size_t rs2, int16_t rs3) {__asm__ ("xc.str.h  %0, %1(%2)" : : "r"(rs3), "r"(rs1) , "r"(rs2));}
static inline void     _xc_str_w ( int32_t* rs1, size_t rs2, int32_t rs3) {__asm__ ("xc.str.w  %0, %1(%2)" : : "r"(rs3), "r"(rs1) , "r"(rs2));}
#endif // defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)

#if defined(XCRYPTO_RV64)
static inline uint32_t _xc_ldr_wu(uint32_t* rs1, size_t rs2) {uint32_t rd; __asm__ ("xc.ldr.wu %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline  int64_t _xc_ldr_d ( int64_t* rs1, size_t rs2) { int64_t rd; __asm__ ("xc.ldr.d  %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}

static inline void     _xc_str_d ( int64_t* rs1, size_t rs2, int64_t rs3) {__asm__ ("xc.str.d  %0, %1(%2)" : : "r"(rs3), "r"(rs1) , "r"(rs2));}
#endif // defined(XCRYPTO_RV64)


//
// SHA2
//

#if defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)
static inline uint32_t _xc_sha256_s0 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha256.s0  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha256_s1 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha256.s1  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha256_s2 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha256.s2  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha256_s3 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha256.s3  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
#endif // defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)

#if defined(XCRYPTO_RV64)
static inline uint32_t _xc_sha512_s0 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha512.s0  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha512_s1 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha512.s1  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha512_s2 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha512.s2  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
static inline uint32_t _xc_sha512_s3 (uint32_t rs1) {uint32_t rd; __asm__ ("xc.sha512.s3  %0, %1" : "=r"(rd) : "r"(rs1)); return rd;}
#endif // defined(XCRYPTO_RV64)


#endif // XCRYPTO_EMULATE

#endif // __XCRYPTO_INTRINSICS__
