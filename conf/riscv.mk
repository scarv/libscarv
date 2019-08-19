# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

include ${REPO_HOME}/conf/share.mk

# =============================================================================

ifeq "${HOST}" "native"

ifndef RISCV
  $(error "point RISCV environment variable at toolchain installation")
endif

export ARCH_SUBSET        = rv32imac
export ARCH_ABI           = ilp32

export TOOL_PREFIX_TARGET = riscv32-
export TOOL_PREFIX_VENDOR = unknown-
export TOOL_PREFIX_ABI    = elf-

export TOOL_PREFIX        = ${RISCV}/bin/${TOOL_PREFIX_TARGET}${TOOL_PREFIX_VENDOR}${TOOL_PREFIX_ABI}

export TEST_PREFIX        = ${RISCV}/bin/spike --isa=${ARCH_SUBSET} ${RISCV}/riscv32-unknown-elf/bin/pk
export TEST_SUFFIX        = | tail -n+2

export CC_PATHS           =
export CC_FLAGS           = -Wall -O2 -march=${ARCH_SUBSET} -mabi=${ARCH_ABI} 
export CC_LIBS            =

endif

# =============================================================================

ifeq "${HOST}" "docker"

       BRANCH       = $(shell git branch | grep '*' | cut --characters=3-)

ifeq "${BRANCH}" "master"
export DOCKER_REPO  = scarv/libscarv.${ARCH}
export DOCKER_TAG   = master
export DOCKER_FLAGS = --env RISCV="/opt/riscv"
else
export DOCKER_REPO  = scarv/libscarv.${ARCH}
export DOCKER_TAG   = $(shell echo ${BRANCH} | cut --delimiter='/' --fields=3)
export DOCKER_FLAGS = --env RISCV="/opt/riscv"
endif

endif

# =============================================================================
