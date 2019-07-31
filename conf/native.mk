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

export DOCKER_IMAGE       = scarv/libscarv.native
export DOCKER_FLAGS       = 

endif

# =============================================================================