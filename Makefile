# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

export

# Provide a default value for ARCH and KERNELS if need be, then "expand" any 
# wildcards in the list of kernels

ARCH    ?= native
KERNELS ?= mp block/* stream/* hash/*

KERNELS := $(patsubst ${REPO_HOME}/src/libscarv/%, %, $(wildcard $(addprefix ${REPO_HOME}/src/libscarv/, ${KERNELS})))

# Include architecture-dependent configuration, then use the list of symbols
# to define associated Makefile varibles (so the source code and build match
# where necessary)

include ${REPO_HOME}/src/conf/${ARCH}.conf

$(foreach SYMBOL, ${CONF}, $(eval ${SYMBOL} = 1))

# Define a set of top-level targets, recursively deferring to sub-Makefiles 
# if need be

%-libscarv :
	@make --directory="${REPO_HOME}/src/libscarv" ${*}
%-test     :
	@make --directory="${REPO_HOME}/src/test"     ${*}

doc      :
	@doxygen ${REPO_HOME}/Doxyfile

spotless :
	@rm --force --recursive ${REPO_HOME}/build/*
