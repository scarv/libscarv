# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

# Provide default values for HOST, ARCHS, and KERNELS.

export HOST    ?= native
export ARCHS   ?= native
export KERNELS ?= block/* hash/* mp/* stream/*

# Perform a (limited) expansion of wildcards in KERNELS.

export KERNELS := $(patsubst ${REPO_HOME}/src/libscarv/%,%,$(wildcard $(addprefix ${REPO_HOME}/src/libscarv/,${KERNELS})))

%-docker   :
	@$(foreach ARCH,${ARCHS},ARCH="${ARCH}" make --directory="${REPO_HOME}/src/docker"   ${*} ;)
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
