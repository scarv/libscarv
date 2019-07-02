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
#define LIBSCARV_CONF_ARCH_NATIVE              ( 0 )
/** Define a numeric identifier (allowing pre-processor condition) for riscv         target architecture.
  */
#define LIBSCARV_CONF_ARCH_RISCV               ( 1 )
/** Define a numeric identifier (allowing pre-processor condition) for riscv-xcrypto target architecture.
  */
#define LIBSCARV_CONF_ARCH_RISCV_XCRYPTO       ( 2 )

/** Specify the target architecture.
  */
#define LIBSCARV_CONF_ARCH                     LIBSCARV_CONF_ARCH_${LIBSCARV_CONF_ARCH}

/* ------------------------------------------------------------------------- */

/** Capture whether or not block/aes kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_AES_ENABLE               ${LIBSCARV_CONF_AES_ENABLE}

/** Capture whether or not mp/limb   kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_LIMB_ENABLE              ${LIBSCARV_CONF_LIMB_ENABLE}
/** Capture whether or not mp/mpn    kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MPN_ENABLE               ${LIBSCARV_CONF_MPN_ENABLE}
/** Capture whether or not mp/mpz    kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MPZ_ENABLE               ${LIBSCARV_CONF_MPZ_ENABLE}
/** Capture whether or not mp/mrz    kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_MRZ_ENABLE               ${LIBSCARV_CONF_MRZ_ENABLE}

/** Capture whether or not hash/sha1 kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SHA1_ENABLE              ${LIBSCARV_CONF_SHA1_ENABLE}
/** Capture whether or not hash/sha2 kernel is enabled (i.e., supported).
  */
#define LIBSCARV_CONF_SHA2_ENABLE              ${LIBSCARV_CONF_SHA2_ENABLE}

/* ------------------------------------------------------------------------- */

/** Specify the implementation type (or strategy): options are
  * 
  * - @p sbox:   see [Section 4.1, 1]; use  8-bit datapath                                  
  * - @p packed: see [Section 4.2, 1]; use 32-bit datapath, with row-wise packing           
  * - @p ttable: see              [2]; use 32-bit datapath, with aggressive pre-computation 
  *
  * 1. J. Daemen and V. Rijmen. 
  *    The Design of Rijndael. 
  *    Springer, 2002.
  *
  * 2. G. Bertoni, L. Breveglieri, P. Fragneto, M. Macchetti, and S. Marchesin. 
  *    Efficient Software Implementation of AES on 32-Bit Platforms. 
  *    Cryptographic Hardware and Embedded Systems (CHES), Springer-Verlag LNCS 2523, 159--171, 2002.
  */
#define LIBSCARV_CONF_AES_TYPE                 ${LIBSCARV_CONF_AES_TYPE}

/** Use an external, architecture-specific implementation of @p aes_enc.
  */
#define LIBSCARV_CONF_AES_ENC_EXTERN           ${LIBSCARV_CONF_AES_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec.
  */
#define LIBSCARV_CONF_AES_DEC_EXTERN           ${LIBSCARV_CONF_AES_DEC_EXTERN}

/** Pre-compute a table for field division       by the indeterminate (i.e., a / x).
  */
#define LIBSCARV_CONF_AES_DIVX_PRECOMP         ${LIBSCARV_CONF_AES_DIVX_PRECOMP}
/** Pre-compute a table for field multiplication by the indeterminate (i.e., a * x).
  */
#define LIBSCARV_CONF_AES_MULX_PRECOMP         ${LIBSCARV_CONF_AES_MULX_PRECOMP}
/** Pre-compute round constants (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_RCON_PRECOMP         ${LIBSCARV_CONF_AES_RCON_PRECOMP}
/** Pre-compute a set of AES S-boxes  (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_SBOX_PRECOMP         ${LIBSCARV_CONF_AES_SBOX_PRECOMP}
/** Pre-compute a set of AES T-tables (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_TBOX_PRECOMP         ${LIBSCARV_CONF_AES_TBOX_PRECOMP}

/** Evolve round key in a forward direction (i.e., the starting point is the first round key).
  */
#define LIBSCARV_CONF_AES_KEY_EVOLVE_FWD       ${LIBSCARV_CONF_AES_KEY_EVOLVE_FWD}
/** Evolve round key in a reverse direction (i.e., the starting point is the last  round key).
  */
#define LIBSCARV_CONF_AES_KEY_EVOLVE_REV       ${LIBSCARV_CONF_AES_KEY_EVOLVE_REV}
/** Pre-compute round      keys (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_KEY_PRECOMP          ${LIBSCARV_CONF_AES_KEY_PRECOMP}

/** If/where possible, apply inter- or intra-round unrolling.
  */
#define LIBSCARV_CONF_AES_RND_INLINE           ${LIBSCARV_CONF_AES_RND_INLINE}
/** If/where possible, apply inter- or intra-round  inlining.
  */
#define LIBSCARV_CONF_AES_RND_UNROLL           ${LIBSCARV_CONF_AES_RND_UNROLL}

/* ------------------------------------------------------------------------- */

/** Set maximum number of limbs in an instance of @p mpz_t.
  */
#define LIBSCARV_CONF_MPZ_MAX_LIMBS            ${LIBSCARV_CONF_MPZ_MAX_LIMBS}
/** Set maximum number of limbs in an instance of @p mrz_t.
  */
#define LIBSCARV_CONF_MRZ_MAX_LIMBS            ${LIBSCARV_CONF_MRZ_MAX_LIMBS}
  
/** Use an external, architecture-specific implementation of @p mpn_cmp.
  */
#define LIBSCARV_CONF_MPN_CMP_EXTERN           ${LIBSCARV_CONF_MPN_CMP_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_add.
  */
#define LIBSCARV_CONF_MPN_ADD_EXTERN           ${LIBSCARV_CONF_MPN_ADD_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_sub.
  */
#define LIBSCARV_CONF_MPN_SUB_EXTERN           ${LIBSCARV_CONF_MPN_SUB_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_sqr.
  */
#define LIBSCARV_CONF_MPN_SQR_EXTERN           ${LIBSCARV_CONF_MPN_SQR_EXTERN}
/** Use an external, architecture-specific implementation of @p mpn_mul.
  */
#define LIBSCARV_CONF_MPN_MUL_EXTERN           ${LIBSCARV_CONF_MPN_MUL_EXTERN}

/** Use an external, architecture-specific implementation of @p mrn_red.
  */
#define LIBSCARV_CONF_MRZ_RED_EXTERN           ${LIBSCARV_CONF_MRZ_RED_EXTERN}
/** Use an external, architecture-specific implementation of @p mrn_mul.
  */
#define LIBSCARV_CONF_MRZ_MUL_EXTERN           ${LIBSCARV_CONF_MRZ_MUL_EXTERN}

/** Use a   guarded         integer addition                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_ADD_GUARD            ${LIBSCARV_CONF_MPN_ADD_GUARD}
/** Use an unrolled         integer addition                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_ADD_UNROLL           ${LIBSCARV_CONF_MPN_ADD_UNROLL}
/** Use a   guarded         integer subtraction                                                          implementation.
  */
#define LIBSCARV_CONF_MPN_SUB_GUARD            ${LIBSCARV_CONF_MPN_SUB_GUARD}
/** Use an unrolled         integer subtraction                                                          implementation.
  */
#define LIBSCARV_CONF_MPN_SUB_UNROLL           ${LIBSCARV_CONF_MPN_SUB_UNROLL}
/** Use an operand scanning integer squaring                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_SQR_OPERAND_SCANNING ${LIBSCARV_CONF_MPN_SQR_OPERAND_SCANNING}
/** Use a  product scanning integer squaring                                                             implementation.
  */
#define LIBSCARV_CONF_MPN_SQR_PRODUCT_SCANNING ${LIBSCARV_CONF_MPN_SQR_PRODUCT_SCANNING}
/** Use an operand scanning integer multiplication                                                       implementation.
  */
#define LIBSCARV_CONF_MPN_MUL_OPERAND_SCANNING ${LIBSCARV_CONF_MPN_MUL_OPERAND_SCANNING}
/** Use a  product scanning integer multiplication                                                       implementation.
  */
#define LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING ${LIBSCARV_CONF_MPN_MUL_PRODUCT_SCANNING}

/** Use a         Un-integrated (i.e.. separate multiplication then reduction) Montgomery multiplication implementation.
  */
#define LIBSCARV_CONF_MRZ_MUL_REDC             ${LIBSCARV_CONF_MRZ_MUL_REDC}
/** Use a  Coarsely Integrated Operand Scanning (CIOS)                         Montgomery multiplication implementation.
  */
#define LIBSCARV_CONF_MRZ_MUL_CIOS             ${LIBSCARV_CONF_MRZ_MUL_CIOS}

/* ------------------------------------------------------------------------- */

#define LIBSCARV_CONF_SHA1_COMP_EXTERN         ${LIBSCARV_CONF_SHA1_COMP_EXTERN}

#define LIBSCARV_CONF_SHA2_256_COMP_EXTERN     ${LIBSCARV_CONF_SHA2_256_COMP_EXTERN}
#define LIBSCARV_CONF_SHA2_512_COMP_EXTERN     ${LIBSCARV_CONF_SHA2_512_COMP_EXTERN}

/* ========================================================================= */

#endif
