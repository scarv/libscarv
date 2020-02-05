/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_CONF_H
#define __LIBSCARV_CONF_H

/* ========================================================================= */

/** Define a numeric identifier (allowing pre-processor condition) for native        target architecture.
  */
#define LIBSCARV_CONF_ARCH_NATIVE                ( 0 )
/** Define a numeric identifier (allowing pre-processor condition) for riscv         target architecture.
  */
#define LIBSCARV_CONF_ARCH_RISCV                 ( 1 )
/** Define a numeric identifier (allowing pre-processor condition) for riscv-xcrypto target architecture.
  */
#define LIBSCARV_CONF_ARCH_RISCV_XCRYPTO         ( 2 )

/** Specify the target architecture.
  */
#define LIBSCARV_CONF_ARCH                       LIBSCARV_CONF_ARCH_${LIBSCARV_CONF_ARCH}

/* ------------------------------------------------------------------------- */

/** Capture whether or not block/aes       kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_AES_ENABLE                 ${LIBSCARV_CONF_AES_ENABLE}
/** Capture whether or not block/sm4       kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SM4_ENABLE                 ${LIBSCARV_CONF_SM4_ENABLE}
/** Capture whether or not block/sm4       kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_PRINCE_ENABLE              ${LIBSCARV_CONF_PRINCE_ENABLE}
/** Capture whether or not block/prince    kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SPARX_ENABLE               ${LIBSCARV_CONF_SPARX_ENABLE}

/** Capture whether or not hash/sha1       kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SHA1_ENABLE                ${LIBSCARV_CONF_SHA1_ENABLE}
/** Capture whether or not hash/sha2       kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SHA2_ENABLE                ${LIBSCARV_CONF_SHA2_ENABLE}
/** Capture whether or not hash/keccak     kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_KECCAK_ENABLE              ${LIBSCARV_CONF_KECCAK_ENABLE}

/** Capture whether or not mp/limb         kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_LIMB_ENABLE                ${LIBSCARV_CONF_LIMB_ENABLE}
/** Capture whether or not mp/mpn          kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MPN_ENABLE                 ${LIBSCARV_CONF_MPN_ENABLE}
/** Capture whether or not mp/mpz          kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MPZ_ENABLE                 ${LIBSCARV_CONF_MPZ_ENABLE}
/** Capture whether or not mp/mrz          kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MRZ_ENABLE                 ${LIBSCARV_CONF_MRZ_ENABLE}

/** Capture whether or not stream/chacha20 kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_CHACHA20_ENABLE            ${LIBSCARV_CONF_CHACHA20_ENABLE}

/* ------------------------------------------------------------------------- */

/** Specify the implementation type (or strategy): options are
  * 
  * - @p sbox:   see [Sec. 4.1, 1]; use  8-bit datapath                                  
  * - @p packed: see [Sec. 4.2, 1]; use 32-bit datapath, with row-wise packing           
  * - @p ttable: see           [2]; use 32-bit datapath, with aggressive pre-computation 
  *
  * 1. J. Daemen and V. Rijmen. 
  *    The Design of Rijndael. 
  *    Springer, 2002.
  *
  * 2. G. Bertoni, L. Breveglieri, P. Fragneto, M. Macchetti, and S. Marchesin. 
  *    Efficient Software Implementation of AES on 32-Bit Platforms. 
  *    Cryptographic Hardware and Embedded Systems (CHES), Springer-Verlag LNCS 2523, 159--171, 2002.
  */
#define LIBSCARV_CONF_AES_TYPE                   ${LIBSCARV_CONF_AES_TYPE}

/** Use an external, architecture-specific implementation of @p aes_enc.
  */
#define LIBSCARV_CONF_AES_ENC_EXTERN             ${LIBSCARV_CONF_AES_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec.
  */
#define LIBSCARV_CONF_AES_DEC_EXTERN             ${LIBSCARV_CONF_AES_DEC_EXTERN}

/** Decryption is structured per the "equivalent inverse cipher" algorithm [Fig. 15, 1], e.g., implying a need to fix-up the round keys appropriately [Sec. 5.3.5, 1].
  *
  * 1. Advanced Encryption Standard (AES).
  *    National Institute of Standards and Technology (NIST),
  *    Federal Information Processing Standards (FIPS) 197,
  *    2001.
  */
#define LIBSCARV_CONF_AES_DEC_EQUIV              ${LIBSCARV_CONF_AES_DEC_EQUIV}

/** Pre-compute a table for field division       by the indeterminate (i.e., a / x).
  */
#define LIBSCARV_CONF_AES_DIVX_PRECOMP           ${LIBSCARV_CONF_AES_DIVX_PRECOMP}
/** Pre-compute a table for field multiplication by the indeterminate (i.e., a * x).
  */
#define LIBSCARV_CONF_AES_MULX_PRECOMP           ${LIBSCARV_CONF_AES_MULX_PRECOMP}
/** Pre-compute round constants (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_RCON_PRECOMP           ${LIBSCARV_CONF_AES_RCON_PRECOMP}
/** Pre-compute a set of AES S-boxes  (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_SBOX_PRECOMP           ${LIBSCARV_CONF_AES_SBOX_PRECOMP}
/** Pre-compute a set of AES T-tables (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_TBOX_PRECOMP           ${LIBSCARV_CONF_AES_TBOX_PRECOMP}

/** Evolve round key in a forward direction (i.e., the starting point is the first round key).
  */
#define LIBSCARV_CONF_AES_KEY_EVOLVE_FWD         ${LIBSCARV_CONF_AES_KEY_EVOLVE_FWD}
/** Evolve round key in a reverse direction (i.e., the starting point is the last  round key).
  */
#define LIBSCARV_CONF_AES_KEY_EVOLVE_REV         ${LIBSCARV_CONF_AES_KEY_EVOLVE_REV}
/** Pre-compute round      keys (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_KEY_PRECOMP            ${LIBSCARV_CONF_AES_KEY_PRECOMP}

/** If/where possible, apply inter- or intra-round unrolling.
  */
#define LIBSCARV_CONF_AES_RND_INLINE             ${LIBSCARV_CONF_AES_RND_INLINE}
/** If/where possible, apply inter- or intra-round  inlining.
  */
#define LIBSCARV_CONF_AES_RND_UNROLL             ${LIBSCARV_CONF_AES_RND_UNROLL}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p sm4_enc.
  */
#define LIBSCARV_CONF_SM4_ENC_EXTERN             ${LIBSCARV_CONF_SM4_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p sm4_dec.
  */
#define LIBSCARV_CONF_SM4_DEC_EXTERN             ${LIBSCARV_CONF_SM4_DEC_EXTERN}

/** Evolve round key in a forward direction (i.e., the starting point is the first round key).
  */
#define LIBSCARV_CONF_SM4_KEY_EVOLVE_FWD         ${LIBSCARV_CONF_SM4_KEY_EVOLVE_FWD}
/** Evolve round key in a reverse direction (i.e., the starting point is the last  round key).
  */
#define LIBSCARV_CONF_SM4_KEY_EVOLVE_REV         ${LIBSCARV_CONF_SM4_KEY_EVOLVE_REV}
/** Pre-compute round      keys (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_SM4_KEY_PRECOMP            ${LIBSCARV_CONF_SM4_KEY_PRECOMP}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p prince_sbox.
  */
#define LIBSCARV_CONF_PRINCE_SBOX_EXTERN         ${LIBSCARV_CONF_PRINCE_SBOX_EXTERN}

/** Use an external, architecture-specific implementation of @p prince_isbox.
  */
#define LIBSCARV_CONF_PRINCE_ISBOX_EXTERN        ${LIBSCARV_CONF_PRINCE_ISBOX_EXTERN}

/** Use an external, architecture-specific implementation of @p prince_shift_rows.
  */
#define LIBSCARV_CONF_PRINCE_SHIFTROWS_EXTERN    ${LIBSCARV_CONF_PRINCE_SHIFTROWS_EXTERN}

/** Use an external, architecture-specific implementation of @p prince_gf_mul.
  */
#define LIBSCARV_CONF_PRINCE_GF_MUL_EXTERN       ${LIBSCARV_CONF_PRINCE_GF_MUL_EXTERN}

/** Use an external, architecture-specific implementation of @p prince_m_prime_layer.
  */
#define LIBSCARV_CONF_PRINCE_MPRIME_EXTERN       ${LIBSCARV_CONF_PRINCE_MPRIME_EXTERN}


/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of the sparx L* functions.
  */
#define LIBSCARV_CONF_SPARX_L_EXTERN             ${LIBSCARV_CONF_SPARX_L_EXTERN}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p sha1_comp.
  */
#define LIBSCARV_CONF_SHA1_COMP_EXTERN           ${LIBSCARV_CONF_SHA1_COMP_EXTERN}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p sha2_256_comp.
  */
#define LIBSCARV_CONF_SHA2_256_COMP_EXTERN       ${LIBSCARV_CONF_SHA2_256_COMP_EXTERN}
/** Use an external, architecture-specific implementation of @p sha2_512_comp.
  */
#define LIBSCARV_CONF_SHA2_512_COMP_EXTERN       ${LIBSCARV_CONF_SHA2_512_COMP_EXTERN}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p KeccakP400Round.
  */
#define LIBSCARV_CONF_KECCAK_P400_ROUND_EXTERN   ${LIBSCARV_CONF_KECCAK_P400_ROUND_EXTERN}
/** Pre-compute a table allowing look-up (vs. computation) of index-related functions.
  */
#define LIBSCARV_CONF_KECCAK_P400_INDEX_PRECOMP  ${LIBSCARV_CONF_KECCAK_P400_INDEX_PRECOMP}

/** Use an external, architecture-specific implementation of @p KeccakP1600Round.
  */
#define LIBSCARV_CONF_KECCAK_P1600_ROUND_EXTERN  ${LIBSCARV_CONF_KECCAK_P1600_ROUND_EXTERN}
/** Pre-compute a table allowing look-up (vs. computation) of index-related functions.
  */
#define LIBSCARV_CONF_KECCAK_P1600_INDEX_PRECOMP ${LIBSCARV_CONF_KECCAK_P1600_INDEX_PRECOMP}

/* ------------------------------------------------------------------------- */

/** Set maximum number of limbs in an instance of @p mpz_t.
  */
#define LIBSCARV_CONF_MPZ_MAX_LIMBS              ${LIBSCARV_CONF_MPZ_MAX_LIMBS}
/** Set maximum number of limbs in an instance of @p mrz_t.
  */
#define LIBSCARV_CONF_MRZ_MAX_LIMBS              ${LIBSCARV_CONF_MRZ_MAX_LIMBS}
  
/** Use an external, architecture-specific implementation of @p mpn_add.
  */
#define LIBSCARV_CONF_MPN_ADD_EXTERN             ${LIBSCARV_CONF_MPN_ADD_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_sub.
  */
#define LIBSCARV_CONF_MPN_SUB_EXTERN             ${LIBSCARV_CONF_MPN_SUB_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_mul.
  */
#define LIBSCARV_CONF_MPN_MUL_EXTERN             ${LIBSCARV_CONF_MPN_MUL_EXTERN}

/** Use an external, architecture-specific implementation of @p mrn_red.
  */
#define LIBSCARV_CONF_MRZ_RED_EXTERN             ${LIBSCARV_CONF_MRZ_RED_EXTERN}
/** Use an external, architecture-specific implementation of @p mrn_mul.
  */
#define LIBSCARV_CONF_MRZ_MUL_EXTERN             ${LIBSCARV_CONF_MRZ_MUL_EXTERN}

/** Use a   guarded         integer addition                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_ADD_GUARD              ${LIBSCARV_CONF_MPN_ADD_GUARD}
/** Use an unrolled         integer addition                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_ADD_UNROLL             ${LIBSCARV_CONF_MPN_ADD_UNROLL}
/** Use a   guarded         integer subtraction                                                          implementation.
  */
#define LIBSCARV_CONF_MPN_SUB_GUARD              ${LIBSCARV_CONF_MPN_SUB_GUARD}
/** Use an unrolled         integer subtraction                                                          implementation.
  */
#define LIBSCARV_CONF_MPN_SUB_UNROLL             ${LIBSCARV_CONF_MPN_SUB_UNROLL}
/** Use an operand scanning integer multiplication                                                       implementation.
  */
#define LIBSCARV_CONF_MPN_MUL_OPERAND_SCANNING   ${LIBSCARV_CONF_MPN_MUL_OPERAND_SCANNING}
/** Use a  product scanning integer multiplication                                                       implementation.
  */
#define LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING   ${LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING}

/** Use a         Un-integrated (i.e.. separate multiplication then reduction) Montgomery multiplication implementation.
  */
#define LIBSCARV_CONF_MRZ_MUL_REDC               ${LIBSCARV_CONF_MRZ_MUL_REDC}
/** Use a  Coarsely Integrated Operand Scanning (CIOS)                         Montgomery multiplication implementation.
  */
#define LIBSCARV_CONF_MRZ_MUL_CIOS               ${LIBSCARV_CONF_MRZ_MUL_CIOS}

/* ------------------------------------------------------------------------- */

/** Use an external, architecture-specific implementation of @p chacha20_process.
  */
#define LIBSCARV_CONF_CHACHA20_PROCESS_EXTERN    ${LIBSCARV_CONF_CHACHA20_PROCESS_EXTERN}

/** Use an external, architecture-specific implementation of @p chacha20_block.
  */
#define LIBSCARV_CONF_CHACHA20_BLOCK_EXTERN      ${LIBSCARV_CONF_CHACHA20_BLOCK_EXTERN}

/* ========================================================================= */

/** Capture whether or not XCrypto implementation supports class 1   instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_1            ${LIBSCARV_CONF_XCRYPTO_CLASS_1}
/** Capture whether or not XCrypto implementation supports class 2.1 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_2_1          ${LIBSCARV_CONF_XCRYPTO_CLASS_2_1}
/** Capture whether or not XCrypto implementation supports class 2.2 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_2_2          ${LIBSCARV_CONF_XCRYPTO_CLASS_2_2}
/** Capture whether or not XCrypto implementation supports class 2.3 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_2_3          ${LIBSCARV_CONF_XCRYPTO_CLASS_2_3}
/** Capture whether or not XCrypto implementation supports class 2.4 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_2_4          ${LIBSCARV_CONF_XCRYPTO_CLASS_2_4}
/** Capture whether or not XCrypto implementation supports class 2.5 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_2_5          ${LIBSCARV_CONF_XCRYPTO_CLASS_2_5}
/** Capture whether or not XCrypto implementation supports class 3.1 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_3_1          ${LIBSCARV_CONF_XCRYPTO_CLASS_3_1}
/** Capture whether or not XCrypto implementation supports class 3.2 instructions.
  */
#define LIBSCARV_CONF_XCRYPTO_CLASS_3_2          ${LIBSCARV_CONF_XCRYPTO_CLASS_3_2}

/* ========================================================================= */

#endif
