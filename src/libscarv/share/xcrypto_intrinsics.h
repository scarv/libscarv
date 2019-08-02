
#include <stdint.h>
#include <stddef.h>

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
static inline  int32_t _xc_ldr_h ( int16_t* rs1, size_t rs2) { int32_t rd; __asm__ ("xc.ldr.h  %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
static inline uint32_t _xc_ldr_hu(uint16_t* rs1, size_t rs2) {uint32_t rd; __asm__ ("xc.ldr.hu %0, %1(%2)" : "=r"(rd) : "r"(rs1) , "r"(rs2)); return rd;}
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

//
// SHA3
//

#if defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)
static inline int _xc_sha3_xy (int rs1, int rs2, char sh) {uint32_t rd; __asm__ ("xc.sha3.xy %0,%1,%2,%3" : "=r"(rd) : "r"(rs1),"r"(rs2),"i"(sh)); return rd;}
static inline int _xc_sha3_x1 (int rs1, int rs2, char sh) {uint32_t rd; __asm__ ("xc.sha3.x1 %0,%1,%2,%3" : "=r"(rd) : "r"(rs1),"r"(rs2),"i"(sh)); return rd;}
static inline int _xc_sha3_x2 (int rs1, int rs2, char sh) {uint32_t rd; __asm__ ("xc.sha3.x2 %0,%1,%2,%3" : "=r"(rd) : "r"(rs1),"r"(rs2),"i"(sh)); return rd;}
static inline int _xc_sha3_x4 (int rs1, int rs2, char sh) {uint32_t rd; __asm__ ("xc.sha3.x4 %0,%1,%2,%3" : "=r"(rd) : "r"(rs1),"r"(rs2),"i"(sh)); return rd;}
static inline int _xc_sha3_yx (int rs1, int rs2, char sh) {uint32_t rd; __asm__ ("xc.sha3.yx %0,%1,%2,%3" : "=r"(rd) : "r"(rs1),"r"(rs2),"i"(sh)); return rd;}
#endif // defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)

//
// Packed
//

#if defined(XCRYPTO_RV32)
static inline uint32_t _xc_padd_h   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.padd   h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_padd_b   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.padd   b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_padd_n   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.padd   n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_padd_c   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.padd   c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_psub_h   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.psub   h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_psub_b   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.psub   b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_psub_n   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.psub   n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_psub_c   (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.psub   c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_pmul_l_h (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.l h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_l_b (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.l b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_l_n (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.l n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_l_c (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.l c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_pmul_h_h (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.h h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_h_b (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.h b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_h_n (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.h n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pmul_h_c (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pmul.h c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_pclmul_l_h (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.l h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_l_b (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.l b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_l_n (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.l n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_l_c (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.l c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_pclmul_h_h (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.h h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_h_b (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.h b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_h_n (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.h n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}
static inline uint32_t _xc_pclmul_h_c (int rs1, int rs2) {uint32_t rd; __asm__ ("xc.pclmul.h c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); return rd;}

static inline uint32_t _xc_psll_h (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psll h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psll.i h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psll_b (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psll b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psll.i b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psll_n (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psll n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psll.i n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psll_c (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psll c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psll.i c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}

static inline uint32_t _xc_psrl_h (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psrl h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psrl.i h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psrl_b (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psrl b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psrl.i b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psrl_n (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psrl n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psrl.i n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_psrl_c (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.psrl c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.psrl.i c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}

static inline uint32_t _xc_pror_h (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.pror h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.pror.i h, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_pror_b (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.pror b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.pror.i b, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_pror_n (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.pror n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.pror.i n, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
static inline uint32_t _xc_pror_c (uint32_t rs1, uint32_t rs2) {uint32_t rd; if(!__builtin_constant_p(rs2)) __asm__ ("xc.pror c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"r"(rs2)); else __asm__ ("xc.pror.i c, %0,%1,%2" : "=r"(rd) : "r"(rs1),"i"(rs2)); return rd;}
#endif // defined(XCRYPTO_RV32) || defined(XCRYPTO_RV64)

#endif // XCRYPTO_EMULATE

#endif // __XCRYPTO_INTRINSICS__
