# `libscarv`: cryptographic software kernels for RISC-V

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/libscarv.svg)](https://travis-ci.com/scarv/libscarv)
[![Documentation](https://codedocs.xyz/scarv/libscarv.svg)](https://codedocs.xyz/scarv/libscarv)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the wider
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

## Quickstart (with more detail in the [wiki](https://github.com/scarv/libscarv/wiki))

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
   git clone https://github.com/scarv/libscarv.git ./libscarv
   cd ./libscarv
   source ./bin/conf.sh
   ```

   to clone and initialise the repository,
   then configure the environment;
   for example, you should find that the
   `REPO_HOME`
   environment variable is set appropriately.

3. Perform various preparatory steps:

   1. Create and populate a suitable Python
      [virtual environment](https://docs.python.org/library/venv.html)
      based on 
      `${REPO_HOME}/requirements.txt`
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
      by setting the 
      `CONTEXT`
      environment variable  appropriately, e.g., via

      ```sh
      export CONTEXT="native"
      ```
  
      or just accept the default(s) per `${REPO_HOME}/Makefile`.

   3. Optionally, 
      select the
      target architecture
      and
      library content (i.e., the set of kernels included)
      by setting the
      `ARCH`
      and
      `KERNELS`
      environment variables appropriately, e.g., via

      ```sh
      export ARCH="riscv"
      export KERNELS="block/aes hash/sha*"
      ```

      or just accept the default(s) per `${REPO_HOME}/Makefile`.

4. Use targets in the top-level `Makefile` to drive a set of
   common tasks, e.g.,

   | Command                  | Description
   | :----------------------- | :----------------------------------------------------------------------------------- |
   | `make doc`               | build the [Doxygen](http://www.doxygen.nl)-based documentation                       |
   | `make venv`              | build the Python [virtual environment](https://docs.python.org/library/venv.html)    |
   | `make    build-libscarv` | build    the `libscarv` library                                                      |
   | `make    build-test`     | build    the `libscarv` test suite                                                   |
   | `make generate-test`     | generate the `libscarv` test suite (i.e., produce meta-program from test executable) |
   | `make validate-test`     | validate the `libscarv` test suite (i.e., execute meta-program)                      |
   | `make    clean`          | clean-up (e.g., remove everything built in `${REPO_HOME}/build`)                     |

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part
by EPSRC via grant [EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1) (under the [RISE](http://www.ukrise.org) programme).

<!--- -------------------------------------------------------------------- --->
