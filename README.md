# `libscarv`: cryptographic software kernels for RISC-V

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
**Note that `libscarv` definitely isn't a library you'd expect (or want)
to see in production code**: it's really only intended for internal use, 
e.g., as
a) a guide for (e.g., ISE) design and implementation work, 
   plus
b) a resource for benchmarking and evaluation.
One could therefore view it as a cryptography-specific analogue of more
general-purpose alternatives, e.g., the
[Embench](https://github.com/embench/embench)
benchmark.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin                    - scripts (e.g., environment configuration)
├── build                  - working directory for build
├── conf                   - global, architecture-specific configuration
└── src                       
    ├── docker             - source code for containers
    ├── libscarv           - source code for libscarv library
    │   ├─ block             - block ciphers
    │   ├─ hash              - hash functions
    │   ├─ mp                - multi-precision integer arithmetic
    │   ├─ share             - shared functions, macros, etc.
    │   └─ stream            - stream ciphers
    └── test               - source code for libscarv test suite
        ├─ block             - block ciphers
        ├─ hash              - hash functions
        ├─ mp                - multi-precision integer arithmetic
        ├─ share             - shared functions, macros, etc.
        └─ stream            - stream ciphers
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. Either

   1. provide a native build context by installing 
      associated pre-requisites, e.g.,

      - a suitable
        compiler 
        and 
        simulator 
        tool-chain,
        e.g.,
   
        - for the 
          `riscv`
          target architecture,
   
          - build and install
            [`riscv/riscv-tools`](https://github.com/riscv/riscv-tools),
            then
          - export the
            `RISCV`
            environment variable st.
            `${RISCV}/bin` 
            houses the associated executables,
   
        - for the 
          `riscv-xcrypto`
          target architecture,
   
          - build and install
            [`scarv/riscv-tools`](https://github.com/scarv/riscv-tools),
            then
          - export the
            `RISCV_XCRYPTO`
            environment variable st.
            `${RISCV_XCRYPTO}/bin` 
            houses the associated executables,
   
      - a
        [Python 3](https://www.python.org)
        distribution,
      - the
        [Doxygen](http://www.doxygen.nl)
        documentation generation system.
      
      and/or

   2. provide a Docker build context by installing 
      the 
      [Docker](https://www.docker.com)
      container platform.

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
      based on 
      [`${REPO_HOME}/requirements.txt`](./requirements.txt) 
      by executing
   
      ```sh
      make venv
      ```
   
      then activate it by executing
   
      ```sh
      source ${REPO_HOME}/build/venv/bin/activate
      ```

   2. Optionally,
      select the
      build context
      by setting the environment variable
      `CONTEXT`
      appropriately,
      e.g., via

      ```sh
      export CONTEXT="native"
      ```
  
      or just accept the default (per [`${REPO_HOME}/Makefile`](./Makefile)).

   3. Optionally, 
      select the
      target architecture
      and
      library content (i.e., the set of kernels included)
      by setting the environment variables
      `ARCH`
      and
      `KERNELS`
      appropriately,
      e.g., via

      ```sh
      export ARCH="riscv"
      export KERNELS="block/aes hash/sha*"
      ```

      or just accept the default (per [`${REPO_HOME}/Makefile`](./Makefile)).

4. Use targets in the top-level `Makefile` to drive a set of
   common tasks, e.g.,

   | Command                  | Description
   | :----------------------- | :----------------------------------------------------------------------------------- |
   | `make doc`               | build the [Doxygen](http://www.doxygen.nl)-based documentation                       |
   | `make    build-libscarv` | build    the `libscarv` library                                                      |
   | `make    build-test`     | build    the `libscarv` test suite                                                   |
   | `make generate-test`     | generate the `libscarv` test suite (i.e., produce meta-program from test executable) |
   | `make generate-test`     | validate the `libscarv` test suite (i.e., execute meta-program)                      |
   | `make    clean`          | clean-up (e.g., remove everything built in `${REPO_HOME}/build`)                     |

<!--- -------------------------------------------------------------------- --->

## Notes

#### The `libscarv` library

- The `libscarv` library is a set of individual kernels; 
  the associated             implementation is housed in

  ```sh
  ${REPO_HOME}/src/libscarv/${KERNEL}
  ```

  and built by providing

  ```sh
  ${REPO_HOME}/src/libscarv/${KERNEL}/Makefile.in
  ```
  
  for the build system to include.

- The directory housing a kernel implementation is structured per

  ```sh
  ${REPO_HOME}/src/libscarv/${KERNEL}
  ${REPO_HOME}/src/libscarv/${KERNEL}/native
  ${REPO_HOME}/src/libscarv/${KERNEL}/riscv
  ${REPO_HOME}/src/libscarv/${KERNEL}/riscv-xcrypto
  ```
 
  i.e., there are sub-directories for *each* target architecture.
  Note that:

  - The top-level directory for a given kernel
    (i.e., `${REPO_HOME}/src/libscarv/${KERNEL}`)
    houses
    an architecture-agnostic implementation.  
    This implementation may be either 

    - incomplete,
      meaning it *must* be combined with supporting,
      architecture-specific functionality
      (i.e., cannot be used as a stand-alone kernel),
    -   complete, 
      meaning it *may*  be combined with supporting,
      architecture-specific functionality
      (i.e., can    be used as a stand-alone kernel).

  - *If* supporting, architecture-specific functionality is used,
    the target architecture (sub-)directory
    (i.e., `${REPO_HOME}/src/libscarv/${KERNEL}/${ARCH}`)
    houses it.

  - Within a given target architecture (sub-)directory,

    - `X_imp.S` captures the architecture-specific implementation
      of some functionality `X`,
    - `macro.S` captures macros that support said implementation(s).

#### The `libscarv` test suite

- Forming part of a larger test suite, each kernel has an associated
  test driver;
  the associated test driver implementation is housed in

  ```sh
  ${REPO_HOME}/src/test/${KERNEL}
  ```

  and built by providing

  ```sh
  ${REPO_HOME}/src/test/${KERNEL}/Makefile.in
  ```
  
  for the build system to include.

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
  [`scarv/riscv-isa-sim`](https://github.com/scarv/riscv-isa-sim),
  as supported by the proxy kernel.

#### The `libscarv` build system

- The 
  `CONTEXT`
  environment variable specifies the
  build context
  within which the build process is executed:

  | Context           | Description                                                                     |
  | :---------------- | :------------------------------------------------------------------------------ |
  | `native`          | The default, native build context                                               |
  | `docker`          | A containerised build context, offered by an architecture-specific Docker image |

  Note that:

  - Each architecture-specific Docker image is built using 
    the content housed in
    [`${REPO_HOME}/src/docker`](./src/docker).
    However, **there is no need to do this manually**: a pre-built 
    image can (and will) be pulled from
    [Docker Hub](https://cloud.docker.com/u/scarv)
    by the build process as needed.

  - It is somewhat reasonable to view this aspect of the build system 
    as over-engineered.  In a sense it is, but, equally, there *is* a
    clear motivation.  Use of
    [Travis CI](https://travis-ci.com)
    as a
    [https://en.wikipedia.org/wiki/Continuous_integration](continuous integration)
    provided places a time-limit on the build process; this limit is
    too small to also build bespoke tool-chains (e.g., for XCrypto),
    a problem which is addressed by using a pre-built, containerised 
    tool-chain.

- The 
  `ARCH`
  environment variable specifies the
  target architecture
  to consider, identifiers for which are one of the following:
  
  | Architecture      | Description                                                                             |
  | :---------------- | :-------------------------------------------------------------------------------------- |
  | `native`          | Architecture-agnostic: whatever the default, native GCC targets                         |
  | `riscv`           | Architecture-specific: RISC-V RV32IMAC                                                  |
  | `riscv-xcrypto`   | Architecture-specific: RISC-V RV32IMAC plus [XCrypto](https://github.com/scarv/xcrypto) |
 
- The
  `KERNELS`
  environment variable specifies a list of
  kernels
  to consider, identifiers for which are one of the following:
  
  | Kernel            | Variant  | Description                                                                             | native  | riscv | riscv-xcrypto |
  | :---------------- | :------- | :-------------------------------------------------------------------------------------- | :------ | :---- | :------------ |
  | `block/aes`       | `sbox`   |                                                                                         | o       | x     | o             |
  | `block/aes`       | `packed` |                                                                                         | o       | x     | x             |
  | `block/aes`       | `ttable` |                                                                                         | o       | x     | x             |
  | `block/prince`    |          |                                                                                         | o       | x     | x             |
  | `block/sparx`     |          |                                                                                         | o       | x     | x             |
  | `hash/keccak`     |          |                                                                                         | o       | x     | x             |
  | `hash/sha1`       |          |                                                                                         | o       | x     | x             |
  | `hash/sha2`       |          |                                                                                         | o       | x     | x             |
  | `mp/limb`         |          |                                                                                         | o       | x     | x             |
  | `mp/mpn`          |          |                                                                                         | o       | o     | o             |
  | `mp/mpz`          |          |                                                                                         | o       | x     | x             |
  | `mp/mrz`          |          |                                                                                         | o       | x     | x             |
  | `stream/chacha20` |          |                                                                                         | o       | x     | o             |

  Note that:

  - The variant column 
    toward the  left-hand side of the table
    highlights where a major variant of a given kernel 
    is available:
    the variant is selected via configuration symbols for said kernel,
    vs. being classed a separate kernel.

  - The         columns
    toward the right-hand side of the table 
    highlight  where specific support for a given target architecture
    is available:
    `o` means an architecture-specific (typically assembly language) implementation is available,
    whereas
    `x` means an architecture-agnostic (typically C)                 implementation is available.

  - A *limited* form of wildcard are supported: for example,

    - rather than 
      `hash/sha1 hash/sha2`,
      one could use
      `hash/sha*`,
    - rather than 
      `hash/keccak hash/sha1 hash/sha2`,
      one could use
      `hash/*`.

- Each target architecture demands two configuration files:

  1. `${REPO_HOME}/conf/${ARCH}.mk`,
     which specifies configuration wrt. the build process
     (e.g., options that control the toolchain),
  2. `${REPO_HOME}/conf/${ARCH}.conf`,
     which specifies configuration wrt. the library
     (i.e., options that control features in the source code).

- A given kernel implementation *may* be configurable via the second 
  class of configuration file, st. a *family* of implementations can 
  be selected between: 

  - the configuration header file
    [`${REPO_HOME}/src/libscarv/share/conf.h`](./src/libscarv/share/conf.h)
    is populated using the configuration file, plus automatically
    generated content stemming from `${ARCH}` and `${KERNELS}`; 
    it houses some documentation for each configuration symbol,

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
    |  `EXTERN` | uses a architecture-specific (typically assembly language) vs. architecture-agnostic (typically C) implementation of functionality |

  - if a kernel cannot support a given configuration symbol, it must
    produce an error: it should be impossible to build the library 
    using a configuration that would cause it to (silently) fail.

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

<!--- -------------------------------------------------------------------- --->
