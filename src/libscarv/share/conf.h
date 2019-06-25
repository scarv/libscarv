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

/** Specify AES implementation type (from @p sbox or @p tbox).
  */
#define LIBSCARV_CONF_AES_TYPE                 ${LIBSCARV_CONF_AES_TYPE}

/** Use an external, architecture-specific implementation of @p aes_enc.
  */
#define LIBSCARV_CONF_AES_ENC_EXTERN           ${LIBSCARV_CONF_AES_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_init (i.e., first  round).
  */
#define LIBSCARV_CONF_AES_ENC_INIT_EXTERN      ${LIBSCARV_CONF_AES_ENC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_iter (i.e., middle rounds).
  */
#define LIBSCARV_CONF_AES_ENC_ITER_EXTERN      ${LIBSCARV_CONF_AES_ENC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_fini (i.e., last   round).
  */
#define LIBSCARV_CONF_AES_ENC_FINI_EXTERN      ${LIBSCARV_CONF_AES_ENC_FINI_EXTERN}

/** Use an external, architecture-specific implementation of @p aes_dec.
  */
#define LIBSCARV_CONF_AES_DEC_EXTERN           ${LIBSCARV_CONF_AES_DEC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_init (i.e., first  round).
  */
#define LIBSCARV_CONF_AES_DEC_INIT_EXTERN      ${LIBSCARV_CONF_AES_DEC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_iter (i.e., middle rounds).
  */
#define LIBSCARV_CONF_AES_DEC_ITER_EXTERN      ${LIBSCARV_CONF_AES_DEC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_fini (i.e., last   round).
  */
#define LIBSCARV_CONF_AES_DEC_FINI_EXTERN      ${LIBSCARV_CONF_AES_DEC_FINI_EXTERN}

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

/** Use split (i.e., separate) vs. merged round functions.
  */
#define LIBSCARV_CONF_AES_ROUND_SPLIT          ${LIBSCARV_CONF_AES_ROUND_SPLIT}
/** Use a packed representation of the state and round key matrices.
  */
#define LIBSCARV_CONF_AES_ROUND_PACK           ${LIBSCARV_CONF_AES_ROUND_PACK}
/** Use unrolled loops wherever possible.
  */
#define LIBSCARV_CONF_AES_ROUND_UNROLL         ${LIBSCARV_CONF_AES_ROUND_UNROLL}

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
