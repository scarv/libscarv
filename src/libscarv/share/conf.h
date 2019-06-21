#ifndef __CONF_H
#define __CONF_H

// ============================================================================

#define CONF_AES_TYPE                    ${CONF_AES_TYPE}

#define CONF_AES_ENABLE_ENC              ${CONF_AES_ENABLE_ENC}
#define CONF_AES_ENABLE_DEC              ${CONF_AES_ENABLE_DEC}

#define CONF_AES_PRECOMP_SBOX            ${CONF_AES_PRECOMP_SBOX}
#define CONF_AES_PRECOMP_TBOX            ${CONF_AES_PRECOMP_TBOX}
#define CONF_AES_PRECOMP_MULX            ${CONF_AES_PRECOMP_MULX}
#define CONF_AES_PRECOMP_DIVX            ${CONF_AES_PRECOMP_DIVX}
#define CONF_AES_PRECOMP_RC              ${CONF_AES_PRECOMP_RC}
#define CONF_AES_PRECOMP_RK              ${CONF_AES_PRECOMP_RK}

#define CONF_AES_KEY_FWD                 ${CONF_AES_KEY_FWD}
#define CONF_AES_KEY_REV                 ${CONF_AES_KEY_REV}

#define CONF_AES_ROUND_SPLIT             ${CONF_AES_ROUND_SPLIT}
#define CONF_AES_ROUND_PACK              ${CONF_AES_ROUND_PACK}
#define CONF_AES_ROUND_UNROLL            ${CONF_AES_ROUND_UNROLL}

// ----------------------------------------------------------------------------

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

// ============================================================================

#endif
