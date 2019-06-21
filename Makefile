# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

export ARCH    ?= native
export KERNELS ?= mp block/* stream/* hash/*

export KERNELS := $(patsubst ${REPO_HOME}/src/libscarv/%,%,$(wildcard $(addprefix ${REPO_HOME}/src/libscarv/,${KERNELS})))

include ${REPO_HOME}/conf/${ARCH}.conf

    %-libscarv :
	@make --directory="${REPO_HOME}/src/libscarv" ${*}
    %-test     :
	@make --directory="${REPO_HOME}/src/test"     ${*}

build-doc      :
	@doxygen ${REPO_HOME}/Doxyfile
clean-doc      :
	@rm --force --recursive ${REPO_HOME}/build/doc	

spotless :
	@rm --force --recursive ${REPO_HOME}/build/*
