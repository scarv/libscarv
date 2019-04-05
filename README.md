# `libscarv`: cryptographic reference implementations for RISC-V

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/libscarv.svg)](https://travis-ci.com/scarv/libscarv)
[![Documentation](https://codedocs.xyz/scarv/libscarv.svg)](https://codedocs.xyz/scarv/libscarv)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the
[SCARV](https://www.scarv.org)
project,
`libscarv` is a collection of cryptographic reference implementations
for RISC-V *and* the SCARV-related cryptographic ISE
[XCrypto](https://github.com/scarv/xcrypto);
the implementations are written in a mix of C and assembly language.
Note that `libscarv` *isn't* a library you'd expect (or want) to see
in production code: it's really only intended for internal use, as
a) a guide for (e.g., ISE) design and implementation work, 
   plus
b) a resource for benchmarking and evaluation.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin                       - scripts (e.g., environment configuration)
├── build                     - working directory for build
├── src                       - source code for library
│   ├── aes
│   └── aes
└── test                      - source code for test suite
    ├── aes
    └── aes
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. Install any associated pre-requisites, e.g.,

   - a
     [Python 3](https://www.python.org)
     distribution,
   - the
     [Doxygen](http://www.doxygen.nl)
     documentation generation system.

2. Execute

   ```sh
   git clone https://github.com/scarv/libscarv.git
   cd ./libscarv
   source ./bin/conf.sh
   ```

   to clone and initialise the repository,
   then configure the environment;
   for example, you should find that the environment variable
   `REPO_HOME`
   is set appropriately.

3. Fix the library configuration

   ```
   export ARCH="riscv"
   export KERNELS="aes mp sha1 sha2"
   ```

4. Build and test the library

   1. Create and populate a suitable Python
      [virtual environment](https://docs.python.org/library/venv.html)
      based on `${REPO_HOME}/requirements.txt` by executing
   
      ```
      make venv
      ```
   
      then activate it by executing
   
      ```
      source ${REPO_HOME}/build/venv/bin/activate
      ```

   2. Execute 

      ```
      make build
      ```
      
      to build the library and associated outputs.

   3. Execute

      ```
      make test
      ```

      to validate the build, applying a suite of tests to each
      kernel in the library: doing so may take some time!

<!--- -------------------------------------------------------------------- --->

## Notes

- library as a whole is just a collection of kernels

- the implementation of a given kernel is in

  ${REPO_HOME}/src/X

  with an associated test program in

  ${REPO_HOME}/test/X

- the implementation of each kernel is configurable, st.
  a *family* of implementations can be selected between
  using configuration options: the namespace for those
  is 
 
  LIBSCARV_CONF_X

- the library makes extensive use of pre-processor

  <domain separator>_<kernel identifier>_<kernel function>_<property>

  e.g.,

  LIBSCARV_AES_ENC_ENABLE

- ENABLE enables (i.e., includes) or disables (i.e., excludes) some functionality
  EXTERN uses a architecture-specific (typically assembly language implementation) vs. architecture-specific (typically C implementation) of some functionality




- The 
  `make`-based
  build system is split into three parts:

  - configuration for the build is determined by
    `Makefile.conf`,
  - the build is  launched via
    `Makefile`
    which provides architecture-agnostic variables and targets.
  - the build is supported by 
    `Makefile.arch-${ARCH}`
    which provides architecture-specific variables and targets,

  So, for example, running:

  ```
  make ARCH=[generic, riscv, riscv-xcrypto]
  ```

  will build the library for the appropriate architecture.

- Building for `riscv-xcrypto` requires a modified toolchain, which
  can be obtained from
  [scarv/riscv-tools](https://github.com/scarv/riscv-tools).

  The `RISCV` environment variable must point at the installation of
  this toolchain in order to compile the library and run tests on the
  Spike simulator.

## Running Tests

- Tests can be run for a given architecture by running the following:

  ```
  $> make ARCH=[generic,riscv,riscv-xcrypto] run-tests
  ```

  This will build and run all of the algorithm tests, placing their
  output in `build/<ARCH>/work`.

- The output of each test is valid Python2 code. We use Python as a golden
  reference for some of the tests, and as a checker for all of the
  outputs.

  The output of each test is automatically run through Python.
  Any mismatches are identified and printed out.

- To run tests for the `riscv` or `riscv-xcrypto` architecture, you will
  need to have an appropriate toolchain and version of spike installed.

## Target architectures

There are three supported target architectures:

Architecture    | Description
----------------|------------------------------------------------------------
`generic`       | Builds with whatever default GCC toolchain is setup.
`riscv`         | Targets the RISC-V `rv32imac` architecture.
`riscv-xcrypto` | Targets the RISC-V `rv32imaxc` architecture. The `x` indicates support for the [XCrypto](https://github.com/scarv/xcrypto) ISE.

## Configuration Options

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
  | `CONF_AES_ENC_INIT_EXTERN`         | Use an external (assembly) definition of `aes_enc_init` function               |
  | `CONF_AES_ENC_ITER_EXTERN`         | Use an external (assembly) definition of `aes_enc_iter` function               |
  | `CONF_AES_ENC_FINI_EXTERN`         | Use an external (assembly) definition of `aes_enc_fini` function               |
  | `CONF_AES_ENC_EXTERN`              | Use an external (assembly) definition of unsplitted `aes_enc` function         |
  | `CONF_AES_DEC_INIT_EXTERN`         | Use an external (assembly) definition of `aes_dec_init` function               |
  | `CONF_AES_DEC_ITER_EXTERN`         | Use an external (assembly) definition of `aes_dec_iter` function               |
  | `CONF_AES_DEC_FINI_EXTERN`         | Use an external (assembly) definition of `aes_dec_fini` function               |
  | `CONF_AES_DEC_EXTERN`              | Use an external (assembly) definition of unsplitted `aes_dec` function         |
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
  |                                    |                                                                                                                     |
  | `CONF_KECCAKP400_ROUND_EXTERN`     | Use an external                                                            KeccakP[400]              implementation |
  | `CONF_KECCAKP400_INDEX_FUNC=[1,0]` | Use an in memory LUT to compute indexes [1, faster, larger] or the `remu` instruction [0, slower, smaller]          |
  |                                    |                                                                                                                     |
  | `CONF_KECCAKP1600_ROUND_EXTERN`    | Use an external                                                            KeccakP[1600]             implementation |
  | `CONF_KECCAKP1600_INDEX_FUNC=[1,0]`| Use an in memory LUT to compute indexes [1, faster, larger] or the `remu` instruction [0, slower, smaller]          |
  | `CONF_PRINCE_SBOX_EXTERN`          | Use an external (assembly) definition of the prince SBOX function                                                   |
  | `CONF_PRINCE_ISBOX_EXTERN`         | Use an external (assembly) definition of the prince inverse SBOX function                                           |
  | `CONF_PRINCE_GF_MUL_EXTERN`        | Use an external (assembly) definition of the prince GF\_MUL function                                                |
  | `CONF_CHACHA20_BLOCK_EXTERN`       | Use an external (assembly) definition of the ChaCha20 block function                                                |

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

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

<!--- -------------------------------------------------------------------- --->
