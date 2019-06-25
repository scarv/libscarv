#ifndef __CONF_H
#define __CONF_H

/* ========================================================================= */

#define CONF_ARCH_NATIVE                 ( 0 )
#define CONF_ARCH_RISCV                  ( 1 )
#define CONF_ARCH_RISCV_XCRYPTO          ( 2 )

/** Specify the target architecture (e.g., @p native, @p riscv, or @p riscv-xcrypto).
  */
#define CONF_ARCH                        CONF_ARCH_${CONF_ARCH}

/* ------------------------------------------------------------------------- */

/** Select AES implementation type (from @p sbox or @p tbox).
  */
#define CONF_AES_TYPE                    ${CONF_AES_TYPE}
/** Enable AES encryption functionality.
  */
#define CONF_AES_ENC_ENABLE              ${CONF_AES_ENC_ENABLE}
/** Enable AES decryption functionality.
  */
#define CONF_AES_DEC_ENABLE              ${CONF_AES_DEC_ENABLE}
/** Use an external, architecture-specific implementation of @p aes_enc.
  */
#define CONF_AES_ENC_EXTERN              ${CONF_AES_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec.
  */
#define CONF_AES_DEC_EXTERN              ${CONF_AES_DEC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_exp.
  */
#define CONF_AES_ENC_EXP_EXTERN          ${CONF_AES_ENC_EXP_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_exp.
  */
#define CONF_AES_DEC_EXP_EXTERN          ${CONF_AES_DEC_EXP_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_init (i.e., first  round).
  */
#define CONF_AES_ENC_INIT_EXTERN         ${CONF_AES_ENC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_iter (i.e., middle rounds).
  */
#define CONF_AES_ENC_ITER_EXTERN         ${CONF_AES_ENC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_fini (i.e., last   round).
  */
#define CONF_AES_ENC_FINI_EXTERN         ${CONF_AES_ENC_FINI_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_init (i.e., first  round).
  */
#define CONF_AES_DEC_INIT_EXTERN         ${CONF_AES_DEC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_iter (i.e., middle rounds).
  */
#define CONF_AES_DEC_ITER_EXTERN         ${CONF_AES_DEC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_fini (i.e., last   round).
  */
#define CONF_AES_DEC_FINI_EXTERN         ${CONF_AES_DEC_FINI_EXTERN}
/** Pre-compute a set of AES S-boxes  (for encryption and/or decryption).
  */
#define CONF_AES_PRECOMP_SBOX            ${CONF_AES_PRECOMP_SBOX}
/** Pre-compute a set of AES T-tables (for encryption and/or decryption).
  */
#define CONF_AES_PRECOMP_TBOX            ${CONF_AES_PRECOMP_TBOX}
/** Pre-compute a table for field multiplication by the indeterminate (i.e., a * x).
  */
#define CONF_AES_PRECOMP_MULX            ${CONF_AES_PRECOMP_MULX}
/** Pre-compute a table for field division       by the indeterminate (i.e., a / x).
  */
#define CONF_AES_PRECOMP_DIVX            ${CONF_AES_PRECOMP_DIVX}
/** Pre-compute round constants (rather than evolve from starting point).
  */
#define CONF_AES_PRECOMP_RC              ${CONF_AES_PRECOMP_RC}
/** Pre-compute round      keys (rather than evolve from starting point).
  */
#define CONF_AES_PRECOMP_RK              ${CONF_AES_PRECOMP_RK}
/** Evolve round key in a forward direction (i.e., the cipher key is the first round key).
  */
#define CONF_AES_KEY_FWD                 ${CONF_AES_KEY_FWD}
/** Evolve round key in a reverse direction (i.e., the cipher key is the last  round key).
  */
#define CONF_AES_KEY_REV                 ${CONF_AES_KEY_REV}

#define CONF_AES_ROUND_SPLIT             ${CONF_AES_ROUND_SPLIT}
#define CONF_AES_ROUND_PACK              ${CONF_AES_ROUND_PACK}
#define CONF_AES_ROUND_UNROLL            ${CONF_AES_ROUND_UNROLL}

/* ------------------------------------------------------------------------- */

#define CONF_MP_MPZ_MAX_LIMBS            ${CONF_MP_MPZ_MAX_LIMBS}
#define CONF_MP_MRZ_MAX_LIMBS            ${CONF_MP_MRZ_MAX_LIMBS}
  
#define CONF_MP_MPN_CMP_EXTERN           ${CONF_MP_MPN_CMP_EXTERN}
#define CONF_MP_MPN_ADD_EXTERN           ${CONF_MP_MPN_ADD_EXTERN}
#define CONF_MP_MPN_SUB_EXTERN           ${CONF_MP_MPN_SUB_EXTERN}
#define CONF_MP_MPN_SQR_EXTERN           ${CONF_MP_MPN_SQR_EXTERN}
#define CONF_MP_MPN_MUL_EXTERN           ${CONF_MP_MPN_MUL_EXTERN}

#define CONF_MP_MRZ_RED_EXTERN           ${CONF_MP_MRZ_RED_EXTERN}
#define CONF_MP_MRZ_MUL_EXTERN           ${CONF_MP_MRZ_MUL_EXTERN}

#define CONF_MP_MPN_ADD_GUARD            ${CONF_MP_MPN_ADD_GUARD}
#define CONF_MP_MPN_ADD_UNROLL           ${CONF_MP_MPN_ADD_UNROLL}
#define CONF_MP_MPN_SUB_GUARD            ${CONF_MP_MPN_SUB_GUARD}
#define CONF_MP_MPN_SUB_UNROLL           ${CONF_MP_MPN_SUB_UNROLL}
#define CONF_MP_MPN_SQR_OPERAND_SCANNING ${CONF_MP_MPN_SQR_OPERAND_SCANNING}
#define CONF_MP_MPN_SQR_PRODUCT_SCANNING ${CONF_MP_MPN_SQR_PRODUCT_SCANNING}
#define CONF_MP_MPN_MUL_OPERAND_SCANNING ${CONF_MP_MPN_MUL_OPERAND_SCANNING}
#define CONF_MP_MPN_MUL_PRODUCT_SCANNING ${CONF_MP_MPN_MUL_PRODUCT_SCANNING}

#define CONF_MP_MRZ_SQR_REDC             ${CONF_MP_MRZ_SQR_REDC}
#define CONF_MP_MRZ_SQR_CIOS             ${CONF_MP_MRZ_SQR_CIOS}
#define CONF_MP_MRZ_MUL_REDC             ${CONF_MP_MRZ_MUL_REDC}
#define CONF_MP_MRZ_MUL_CIOS             ${CONF_MP_MRZ_MUL_CIOS}

/* ========================================================================= */

#endif
