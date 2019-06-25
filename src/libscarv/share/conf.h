#ifndef __LIBSCARV_CONF_H
#define __LIBSCARV_CONF_H

/* ========================================================================= */

#define LIBSCARV_CONF_ARCH_NATIVE                 ( 0 )
#define LIBSCARV_CONF_ARCH_RISCV                  ( 1 )
#define LIBSCARV_CONF_ARCH_RISCV_XCRYPTO          ( 2 )

/** Specify the target architecture (e.g., @p native, @p riscv, or @p riscv-xcrypto).
  */
#define LIBSCARV_CONF_ARCH                        LIBSCARV_CONF_ARCH_${LIBSCARV_CONF_ARCH}

/* ------------------------------------------------------------------------- */

/** Select AES implementation type (from @p sbox or @p tbox).
  */
#define LIBSCARV_CONF_AES_TYPE                    ${LIBSCARV_CONF_AES_TYPE}
/** Enable AES encryption functionality.
  */
#define LIBSCARV_CONF_AES_ENC_ENABLE              ${LIBSCARV_CONF_AES_ENC_ENABLE}
/** Enable AES decryption functionality.
  */
#define LIBSCARV_CONF_AES_DEC_ENABLE              ${LIBSCARV_CONF_AES_DEC_ENABLE}
/** Use an external, architecture-specific implementation of @p aes_enc.
  */
#define LIBSCARV_CONF_AES_ENC_EXTERN              ${LIBSCARV_CONF_AES_ENC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec.
  */
#define LIBSCARV_CONF_AES_DEC_EXTERN              ${LIBSCARV_CONF_AES_DEC_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_exp.
  */
#define LIBSCARV_CONF_AES_ENC_EXP_EXTERN          ${LIBSCARV_CONF_AES_ENC_EXP_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_exp.
  */
#define LIBSCARV_CONF_AES_DEC_EXP_EXTERN          ${LIBSCARV_CONF_AES_DEC_EXP_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_init (i.e., first  round).
  */
#define LIBSCARV_CONF_AES_ENC_INIT_EXTERN         ${LIBSCARV_CONF_AES_ENC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_iter (i.e., middle rounds).
  */
#define LIBSCARV_CONF_AES_ENC_ITER_EXTERN         ${LIBSCARV_CONF_AES_ENC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_enc_fini (i.e., last   round).
  */
#define LIBSCARV_CONF_AES_ENC_FINI_EXTERN         ${LIBSCARV_CONF_AES_ENC_FINI_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_init (i.e., first  round).
  */
#define LIBSCARV_CONF_AES_DEC_INIT_EXTERN         ${LIBSCARV_CONF_AES_DEC_INIT_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_iter (i.e., middle rounds).
  */
#define LIBSCARV_CONF_AES_DEC_ITER_EXTERN         ${LIBSCARV_CONF_AES_DEC_ITER_EXTERN}
/** Use an external, architecture-specific implementation of @p aes_dec_fini (i.e., last   round).
  */
#define LIBSCARV_CONF_AES_DEC_FINI_EXTERN         ${LIBSCARV_CONF_AES_DEC_FINI_EXTERN}
/** Pre-compute a set of AES S-boxes  (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_PRECOMP_SBOX            ${LIBSCARV_CONF_AES_PRECOMP_SBOX}
/** Pre-compute a set of AES T-tables (for encryption and/or decryption).
  */
#define LIBSCARV_CONF_AES_PRECOMP_TBOX            ${LIBSCARV_CONF_AES_PRECOMP_TBOX}
/** Pre-compute a table for field multiplication by the indeterminate (i.e., a * x).
  */
#define LIBSCARV_CONF_AES_PRECOMP_MULX            ${LIBSCARV_CONF_AES_PRECOMP_MULX}
/** Pre-compute a table for field division       by the indeterminate (i.e., a / x).
  */
#define LIBSCARV_CONF_AES_PRECOMP_DIVX            ${LIBSCARV_CONF_AES_PRECOMP_DIVX}
/** Pre-compute round constants (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_PRECOMP_RC              ${LIBSCARV_CONF_AES_PRECOMP_RC}
/** Pre-compute round      keys (rather than evolve from starting point).
  */
#define LIBSCARV_CONF_AES_PRECOMP_RK              ${LIBSCARV_CONF_AES_PRECOMP_RK}
/** Evolve round key in a forward direction (i.e., the cipher key is the first round key).
  */
#define LIBSCARV_CONF_AES_KEY_FWD                 ${LIBSCARV_CONF_AES_KEY_FWD}
/** Evolve round key in a reverse direction (i.e., the cipher key is the last  round key).
  */
#define LIBSCARV_CONF_AES_KEY_REV                 ${LIBSCARV_CONF_AES_KEY_REV}

#define LIBSCARV_CONF_AES_ROUND_SPLIT             ${LIBSCARV_CONF_AES_ROUND_SPLIT}
#define LIBSCARV_CONF_AES_ROUND_PACK              ${LIBSCARV_CONF_AES_ROUND_PACK}
#define LIBSCARV_CONF_AES_ROUND_UNROLL            ${LIBSCARV_CONF_AES_ROUND_UNROLL}

/* ------------------------------------------------------------------------- */

#define LIBSCARV_CONF_MP_MPZ_MAX_LIMBS            ${LIBSCARV_CONF_MP_MPZ_MAX_LIMBS}
#define LIBSCARV_CONF_MP_MRZ_MAX_LIMBS            ${LIBSCARV_CONF_MP_MRZ_MAX_LIMBS}
  
#define LIBSCARV_CONF_MP_MPN_CMP_EXTERN           ${LIBSCARV_CONF_MP_MPN_CMP_EXTERN}
#define LIBSCARV_CONF_MP_MPN_ADD_EXTERN           ${LIBSCARV_CONF_MP_MPN_ADD_EXTERN}
#define LIBSCARV_CONF_MP_MPN_SUB_EXTERN           ${LIBSCARV_CONF_MP_MPN_SUB_EXTERN}
#define LIBSCARV_CONF_MP_MPN_SQR_EXTERN           ${LIBSCARV_CONF_MP_MPN_SQR_EXTERN}
#define LIBSCARV_CONF_MP_MPN_MUL_EXTERN           ${LIBSCARV_CONF_MP_MPN_MUL_EXTERN}

#define LIBSCARV_CONF_MP_MRZ_RED_EXTERN           ${LIBSCARV_CONF_MP_MRZ_RED_EXTERN}
#define LIBSCARV_CONF_MP_MRZ_MUL_EXTERN           ${LIBSCARV_CONF_MP_MRZ_MUL_EXTERN}

#define LIBSCARV_CONF_MP_MPN_ADD_GUARD            ${LIBSCARV_CONF_MP_MPN_ADD_GUARD}
#define LIBSCARV_CONF_MP_MPN_ADD_UNROLL           ${LIBSCARV_CONF_MP_MPN_ADD_UNROLL}
#define LIBSCARV_CONF_MP_MPN_SUB_GUARD            ${LIBSCARV_CONF_MP_MPN_SUB_GUARD}
#define LIBSCARV_CONF_MP_MPN_SUB_UNROLL           ${LIBSCARV_CONF_MP_MPN_SUB_UNROLL}
#define LIBSCARV_CONF_MP_MPN_SQR_OPERAND_SCANNING ${LIBSCARV_CONF_MP_MPN_SQR_OPERAND_SCANNING}
#define LIBSCARV_CONF_MP_MPN_SQR_PRODUCT_SCANNING ${LIBSCARV_CONF_MP_MPN_SQR_PRODUCT_SCANNING}
#define LIBSCARV_CONF_MP_MPN_MUL_OPERAND_SCANNING ${LIBSCARV_CONF_MP_MPN_MUL_OPERAND_SCANNING}
#define LIBSCARV_CONF_MP_MPN_MUL_PRODUCT_SCANNING ${LIBSCARV_CONF_MP_MPN_MUL_PRODUCT_SCANNING}

#define LIBSCARV_CONF_MP_MRZ_SQR_REDC             ${LIBSCARV_CONF_MP_MRZ_SQR_REDC}
#define LIBSCARV_CONF_MP_MRZ_SQR_CIOS             ${LIBSCARV_CONF_MP_MRZ_SQR_CIOS}
#define LIBSCARV_CONF_MP_MRZ_MUL_REDC             ${LIBSCARV_CONF_MP_MRZ_MUL_REDC}
#define LIBSCARV_CONF_MP_MRZ_MUL_CIOS             ${LIBSCARV_CONF_MP_MRZ_MUL_CIOS}

/* ========================================================================= */

#endif
