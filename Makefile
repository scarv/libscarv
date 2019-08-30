# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

# =============================================================================

# Provide default values for CONTEXT, ARCH, and KERNELS.

export CONTEXT ?= native

export ARCH    ?= native
export KERNELS ?= block/* hash/* mp/* stream/*

# Perform a (limited) expansion of wildcards in KERNELS.

export KERNELS := $(patsubst ${REPO_HOME}/src/libscarv/%,%,$(wildcard $(addprefix ${REPO_HOME}/src/libscarv/,${KERNELS})))

# =============================================================================

# Define targets to drive build process, depending on CONTEXT (i.e., on the 
# selected build context):
#
# 1. for the Docker build context, defer everything to the Docker container 
#    (i.e., execute make on the same target *within* the container), or
# 2. for the native build context, 
#
#    - deal with specific "global" targets (e.g., wrt. the Python virtual 
#      environment or documentation), or
#    - defer to the appropriate sub-Makefile for everything else.

ifeq "${CONTEXT}" "docker"
include ${REPO_HOME}/conf/${ARCH}.mk_docker

%          :
	@docker run --rm --volume "${REPO_HOME}:/mnt/scarv/libscarv" --env DOCKER_GID="$(shell id --group)" --env DOCKER_UID="$(shell id --user)" --env REPO_HOME="/mnt/scarv/libscarv" --env CONTEXT="native" --env ARCH="${ARCH}" --env KERNELS="${KERNELS}" ${DOCKER_FLAGS} ${DOCKER_REPO}:${DOCKER_TAG} ${*}
endif

ifeq "${CONTEXT}" "native"
include ${REPO_HOME}/conf/${ARCH}.mk_native

%-docker   :
	@make --directory="${REPO_HOME}/src/docker"   ${*}
%-libscarv :
	@make --directory="${REPO_HOME}/src/libscarv" ${*}
%-test     :
	@make --directory="${REPO_HOME}/src/test"     ${*}

venv  : ${REPO_HOME}/requirements.txt
	@${REPO_HOME}/bin/venv.sh

doc   : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

clean :
	@rm --force --recursive ${REPO_HOME}/build/*
endif

# =============================================================================
