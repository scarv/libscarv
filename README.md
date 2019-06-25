# `libscarv`: reference implementations

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/libscarv.svg)](https://travis-ci.com/scarv/libscarv)
[![Documentation](https://codedocs.xyz/scarv/libscarv.svg)](https://codedocs.xyz/scarv/libscarv)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the
[SCARV](https://www.scarv.org)
project,
`libscarv` is a library of cryptographic reference implementations for 
RISC-V generally, *and* the SCARV-related cryptographic ISE
[XCrypto](https://github.com/scarv/xcrypto)
specifically; the implementations are written in a mixture of C and/or
assembly language.
Note that `libscarv` definitely isn't a library you'd expect (or want)
to see in production code: it's really only intended for internal use, 
e.g., as
a) a guide for (e.g., ISE) design and implementation work, 
   plus
b) a resource for benchmarking and evaluation.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin                       - scripts (e.g., environment configuration)
├── build                     - working directory for build
├── conf                      - architecture-specific configuration
└── src                       
    ├── libscarv              - source code for library
    │   ├─ block                - block ciphers
    │   ├─ hash                 - hash functions
    │   ├─ mp                   - multi-precision integer arithmetic
    │   ├─ share                - shared functions, macros, etc.
    │   └─ stream               - stream ciphers
    └── test                  - source code for test suite
        ├─ block                - block ciphers
        ├─ hash                 - hash functions
        ├─ mp                   - multi-precision integer arithmetic
        ├─ share                - shared functions, macros, etc.
        └─ stream               - stream ciphers
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. Install any associated pre-requisites, e.g.,

   - a suitable
     compiler 
     and 
     simulator 
     tool-chain,
     e.g.,

     - [`riscv/riscv-tools`](https://github.com/riscv/riscv-tools)
       for the 
       `riscv`
       target architecture,
       or
     - [`scarv/riscv-tools`](https://github.com/scarv/riscv-tools)
       for the 
       `riscv-xcrypto`
       target architecture,

     exporting the
     `RISCV`
     environment variable st.
     `${RISCV}/bin` 
     houses the associated executables,
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

3. Perform various preparatory steps:

   1. Create and populate a suitable Python
      [virtual environment](https://docs.python.org/library/venv.html)
      based on `${REPO_HOME}/requirements.txt` by executing
   
      ```sh
      make venv
      ```
   
      then activate it by executing
   
      ```sh
      source ${REPO_HOME}/build/venv/bin/activate
      ```

   2. Select the
      target architecture
      and
      library content (i.e., the set of kernels included)
      by setting the environment variables
      `ARCHS`
      and
      `KERNELS`
      appropriately,
      e.g., via

      ```sh
      export ARCHS="riscv"
      export KERNELS="block/aes hash/sha* mp/*"
      ```

4. Use targets in the top-level `Makefile` to drive a set of
   common tasks, e.g.,

   - execute

     ```sh
     make doc
     ```
   
     to build the documentation,

   - execute 

     ```sh
     make build-libscarv
     ```
      
     to build the library,

   - execute

     ```sh
     make build-test
     ```

     to build the test suite, then

     ```sh
     make generate-test
     make validate-test
     ```

     to apply it,

   - execute

     ```sh
     make        clean
     ```

     to clean-up
     (e.g., remove everything built in `${REPO_HOME}/build`).

<!--- -------------------------------------------------------------------- --->

## Notes

#### The `libscarv` library

- The `libscarv` library is a set of individual kernels; 
  the associated             implementation is housed in

  ```sh
  ${REPO_HOME}/src/libscarv/${KERNEL}
  ```

- The directory housing a kernel implementation is structured per

  ```sh
  ${REPO_HOME}/src/libscarv/${KERNEL}
  ${REPO_HOME}/src/libscarv/${KERNEL}/native
  ${REPO_HOME}/src/libscarv/${KERNEL}/riscv
  ${REPO_HOME}/src/libscarv/${KERNEL}/riscv-xcrypto
  ```
 
  i.e., there are sub-directories for *each* target architecture.

#### The `libscarv` test suite

- Forming part of a larger test suite, each kernel has an associated
  test driver;
  the associated test driver implementation is housed in

  ```sh
  ${REPO_HOME}/src/test/${KERNEL}
  ```

- For a given kernel, the test process is essentially:

  1. build the test driver, producing a test executable

     ```sh
     ${REPO_HOME}/build/${ARCH}/bin/test_${KERNEL}
     ```

  2. execute the test executable, an thereby generate a Python-based
     validation (meta-)program

     ```sh
     ${REPO_HOME}/build/${ARCH}/test/test_${KERNEL}.py
     ```

  3. execute the validation (meta-)program, producing output into

     ```sh
     ${REPO_HOME}/build/${ARCH}/test/test_${KERNEL}.log
     ```

     Essentially this means using Python (or appropriate library for
     it) as a 
     [test oracle](https://en.wikipedia.org/wiki/Test_oracle)
     if/where need be.

  The test strategy used depends on the kernel: some use randomised 
  testing, whereas others fixed, hard-coded test vectors.

- Note that for the 
  `riscv` 
  and `
  riscv-xcrypto` 
  target architectures, execution of the test executable implies
  *simulation* via a suitable version of Spike, i.e., either
  [`riscv/riscv-isa-sim`](https://github.com/riscv/riscv-isa-sim)
  or
  [`scarv/riscv-isa-sim`](https://github.com/riscv/riscv-isa-sim),
  as supported by the proxy kernel.

#### The build system

- The 
  `ARCHS`
  environment variable specifies a list of 
  target architectures
  to consider, identifiers for which are one of the following:
  
  | Architecture      | Description                                                                             |
  | :---------------- | :-------------------------------------------------------------------------------------- |
  | `native`          | Architecture-agnostic: whatever the default GCC targets                                 |
  | `riscv`           | Architecture-specific: RISC-V RV32IMAC                                                  |
  | `riscv-xcrypto`   | Architecture-specific: RISC-V RV32IMAC plus [XCrypto](https://github.com/scarv/xcrypto) |
 
- The
  `KERNELS`
  environment variable specifies a list of
  kernels
  to consider, identifiers for which are one of the following:
  
  | Kernel            | Description                                                                             |
  | :---------------- | :-------------------------------------------------------------------------------------- |
  | `block/aes`       |                                                                                         |
  | `block/prince`    |                                                                                         |
  | `block/sparx`     |                                                                                         |
  | `hash/keccak`     |                                                                                         |
  | `hash/sha1`       |                                                                                         |
  | `hash/sha2`       |                                                                                         |
  | `mp/limb`         |                                                                                         |
  | `mp/mpn`          |                                                                                         |
  | `mp/mpz`          |                                                                                         |
  | `mp/mrz`          |                                                                                         |
  | `stream/chacha20` |                                                                                         |

  Note that a limited form of wildcard is supported: for example,

  - rather than 
    `hash/sha1 hash/sha2`,
    one could use
    `hash/sha*`,
  - rather than 
    `hash/keccak hash/sha1 hash/sha2`,
    one could use
    `hash/*`.

- Two classes of configuration file are required:

  1. `${REPO_HOME}/conf/${ARCH}.mk`,
     which specifies configuration wrt. the built itself
     (e.g., options that control the toolchain),
  2. `${REPO_HOME}/conf/${ARCH}.conf`,
     which specifies configuration wrt. the library
     (i.e., options that control features in the source code).

- A given kernel implementation *may* be configurable via the second 
  class of configuration file, st. a *family* of implementations can 
  be selected between: 

  - the configuration header file
    [`${REPO_HOME}/src/libscarv/share/conf.h`](./src/libscarv/share/conf.h)
    is populated using the configuration file; 
    it includes documentation for each configuration symbol,

  - configuration symbols are made available in the source code via
    application of the
    [C pre-processor](https://en.wikipedia.org/wiki/C_preprocessor),
    and follow a standard namespace, i.e.,

    ```
    LIBSCARV_CONF_${KERNEL}_${FUNCTION}_${PROPERTY}
    ```

    with some standard(ish) properties including the following:

    | Property  | Description                                                                                                                        |
    | :-------- | :--------------------------------------------------------------------------------------------------------------------------------- |
    |  `ENABLE` |  enables (i.e., includes) functionality (assuming default is to disable it)                                                        |
    | `DISABLE` | disables (i.e., excludes) functionality (assuming default is to  enable it)                                                        |
    | `PRECOMP` | support functionality via pre-computation                                                                                          |
    |  `EXTERN` | uses a architecture-specific (typically assembly language) vs. architecture-specific (typically C) implementation of functionality |

  - if a kernel cannot support a given configuration symbol, it must
    produce an error: it should be impossible to build the library 
    using a configuration that would cause it to (silently) fail,

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

<!--- -------------------------------------------------------------------- --->
