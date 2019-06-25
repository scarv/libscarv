# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

export ARCHS   ?= native
export KERNELS ?= block/* hash/* mp/* stream/*

export KERNELS := $(patsubst ${REPO_HOME}/src/libscarv/%,%,$(wildcard $(addprefix ${REPO_HOME}/src/libscarv/,${KERNELS})))

%-docker   :
	@docker run --env DOCKER_GID="$(shell id --group)" --env DOCKER_UID="$(shell id --user)" --env REPO_HOME="/mnt/scarv/xcrypto" --env ARCHS="${ARCHS}" --env KERNELS="${KERNELS}" --volume ${PWD}:/mnt/scarv/xcrypto --rm scarv/xcrypto ${*}

%-libscarv :
	@$(foreach ARCH,${ARCHS},ARCH="${ARCH}" make --directory="${REPO_HOME}/src/libscarv" ${*} ;)
%-test     :
	@$(foreach ARCH,${ARCHS},ARCH="${ARCH}" make --directory="${REPO_HOME}/src/test"     ${*} ;)

venv  : ${REPO_HOME}/requirements.txt
	@${REPO_HOME}/bin/venv.sh

doc   : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

clean :
	@rm --force --recursive ${REPO_HOME}/build/*
