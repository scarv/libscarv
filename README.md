# `libscarv`: a (software) library of cryptographic reference implementations

<!--- -------------------------------------------------------------------- --->

## Content

- It *isn't* a library you'd expect (or want) in production code.  In
  short, it's really only intended for internal use: it offers 
  a) a guide for (e.g., ISA) design and implementation work, 
     plus
  b) a means of benchmarking and evaluation.

- The 
  `make`-based
  build system is split into three parts:

  - configuration for the build is determined by
    `Makefile.conf`,
  - the build is  launched via
    `Makefile.arch-${ARCH}`
    which provides architecture-specific variables and targets,
  - the build is supported by 
    `Makefile`
    which provides architecture-agnostic variables and targets.

  So, for example, 

  ```
  make -f Makefile.arch-generic clean all test
  ```

  to 
  a) build the library, 
     and then
  b) build and execute some associated unit tests (which use Python as
     a reference oracle),
  for the generic (i.e., vanilla C) architecture.

- The configuration options available in
  `Makefile.conf`
  can be summarised as follows

  | Option                             | Meaning                                                                                                             |
  | :--------------------------------- | :------------------------------------------------------------------------------------------------------------------ |
  | `CONF_AES_ENABLE_ENC`              | Enable encryption, i.e., `aes_enc`                                                                                  |
  | `CONF_AES_ENABLE_DEC`              | Enable decryption, i.e., `aes_dec`                                                                                  |
  | `CONF_AES_PRECOMP_SBOX`            | Pre-compute S-box                                                                                                   |
  | `CONF_AES_PRECOMP_TBOX`            | Pre-compute T-tables                                                                                                |
  | `CONF_AES_PRECOMP_MULX`            | Pre-compute "multiply by x" (or `xtime`) finite field operation                                                     |
  | `CONF_AES_PRECOMP_DIVX`            | Pre-compute "divide   by x"              finite field operation                                                     |
  | `CONF_AES_PRECOMP_RC`              | Pre-compute round constants                                                                                         |
  | `CONF_AES_PRECOMP_RK`              | Pre-compute round keys                                                                                              |
  | `CONF_AES_KEY_FWD`                 | For `aes_dec`, specify that cipher key is initial round key                                                         |
  | `CONF_AES_KEY_REV`                 | For `aes_dec`, specify that cipher key is final   round key                                                         |
  | `CONF_AES_ROUND_SPLIT`             | A given implementation splits each round function, vs. merges them into one round                                   |
  | `CONF_AES_ROUND_PACK`              | Use a packed representation of the state and round key matrices                                                     |
  | `CONF_AES_ROUND_UNROLL`            | Use unrolled loops wherever possible                                                                                |
  |                                    |                                                                                                                     |
  | `CONF_MP_MPZ_MAX_LIMBS`            | Set maximum number of limbs in an instance of `mpz_t`                                                               |
  | `CONF_MP_MRZ_MAX_LIMBS`            | Set maximum number of limbs in an instance of `mrz_t`                                                               |
  | `CONF_MP_MPN_CMP_EXTERN`           | Use an external         integer comparison                                                           implementation |
  | `CONF_MP_MPN_ADD_EXTERN`           | Use an external         integer addition                                                             implementation |
  | `CONF_MP_MPN_ADD_GUARD`            | Use a   guarded         integer addition                                                             implementation |
  | `CONF_MP_MPN_ADD_UNROLL`           | Use an unrolled         integer addition                                                             implementation |
  | `CONF_MP_MPN_SUB_EXTERN`           | Use an external         integer subtraction                                                          implementation |
  | `CONF_MP_MPN_SUB_GUARD`            | Use a   guarded         integer subtraction                                                          implementation |
  | `CONF_MP_MPN_SUB_UNROLL`           | Use an unrolled         integer subtraction                                                          implementation |
  | `CONF_MP_MPN_SQR_EXTERN`           | Use an external         integer squaring                                                             implementation |
  | `CONF_MP_MPN_SQR_OPERAND_SCANNING` | Use an operand scanning integer squaring                                                             implementation |
  | `CONF_MP_MPN_SQR_PRODUCT_SCANNING` | Use a  product scanning integer squaring                                                             implementation |
  | `CONF_MP_MPN_MUL_EXTERN`           | Use an external         integer multiplication                                                       implementation |
  | `CONF_MP_MPN_MUL_OPERAND_SCANNING` | Use an operand scanning integer multiplication                                                       implementation |
  | `CONF_MP_MPN_MUL_PRODUCT_SCANNING` | Use a  product scanning integer multiplication                                                       implementation |
  | `CONF_MP_MRZ_RED_EXTERN`           | Use an external                                                            Montgomery reduction      implementation |
  | `CONF_MP_MRZ_MUL_EXTERN`           | Use an external                                                            Montgomery multiplication implementation |
  | `CONF_MP_MRZ_MUL_REDC`             | Use a         Un-integrated (i.e.. separate multiplication then reduction) Montgomery multiplication implementation |
  | `CONF_MP_MRZ_MUL_CIOS`             | Use a  Coarsely Integrated Operand Scanning (CIOS)                         Montgomery multiplication implementation |
  | `CONF_KECCAKP400_ROUND_EXTERN`     | Use an external                                                            KeccakP[400]              implementation |
  | `CONF_KECCAKP400_INDEX_FUNC=[1,0]` | Use an in memory LUT to compute indexes [1, faster, larger] or the `remu` instruction [0, slower, smaller]          |
  | `CONF_KECCAKP1600_ROUND_EXTERN`    | Use an external                                                            KeccakP[1600]             implementation |
  | `CONF_KECCAKP1600_INDEX_FUNC=[1,0]`| Use an in memory LUT to compute indexes [1, faster, larger] or the `remu` instruction [0, slower, smaller]          |

  noting that not *all* combinations are valid: "correct" configuration
  isn't fool proof!

- For AES, the goal is to support 
  a) AES-128 *only*,
  b) encryption *and* decryption functionality,
     and
  c) three high-level implementation strategies, namely

  1. a reference strategy
     (`AES_TYPE`=`space`, `!CONF_AES_ROUND_PACK`; see [Section 4.1, 1]),
  2. a T-tables  strategy
     (`AES_TYPE`=`speed`;                         see [Section 4.2, 1]),
     and
  3. a packed    strategy
     (`AES_TYPE`=`space`,  `CONF_AES_ROUND_PACK`; see              [2]).

<!--- -------------------------------------------------------------------- --->

## References

1. J. Daemen and V. Rijmen.
   [The Design of Rijndael](https://www.springer.com/gb/book/9783540425809).
   Springer, 2002.
2. G. Bertoni, L. Breveglieri, P. Fragneto, M. Macchetti, and S. Marchesin.
   [Efficient Software Implementation of AES on 32-Bit Platforms](https://link.springer.com/chapter/10.1007/3-540-36400-5_13).
   Cryptographic Hardware and Embedded Systems (CHES),
   Springer-Verlag LNCS 2523, 159--171, 2002.

<!--- -------------------------------------------------------------------- --->
