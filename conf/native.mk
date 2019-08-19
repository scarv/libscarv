# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

include ${REPO_HOME}/conf/share.mk

# =============================================================================

ifeq "${HOST}" "native"

export TOOL_PREFIX_TARGET =
export TOOL_PREFIX_VENDOR =
export TOOL_PREFIX_ABI    =

export TOOL_PREFIX        = ${TOOL_PREFIX_TARGET}${TOOL_PREFIX_VENDOR}${TOOL_PREFIX_ABI}

export TEST_PREFIX        = 
export TEST_SUFFIX        = 

export CC_PATHS           =
export CC_FLAGS           = -Wall -O3
export CC_LIBS            =

endif

# =============================================================================

ifeq "${HOST}" "docker"

       BRANCH       = $(shell git branch | grep '*' | cut --characters=3-)

ifeq "${BRANCH}" "master"
export DOCKER_REPO  = scarv/libscarv.${ARCH}
export DOCKER_TAG   = master
export DOCKER_FLAGS = 
else
export DOCKER_REPO  = scarv/libscarv.${ARCH}
export DOCKER_TAG   = $(shell echo ${BRANCH} | cut --delimiter='/' --fields=3)
export DOCKER_FLAGS = 
endif

endif

# =============================================================================
