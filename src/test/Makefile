# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# For each built file type, map source path into build path so as to allow
# totally out-of-tree build.

# ${1} = kernel identifier

define map_target
  $(strip ${REPO_HOME})/build/$(strip ${ARCH})/bin/test_$(strip ${1})
endef
define map_script
  $(strip ${REPO_HOME})/build/$(strip ${ARCH})/test/test_$(strip ${1})
endef
define map_result
  $(strip ${REPO_HOME})/build/$(strip ${ARCH})/test/test_$(strip ${1})
endef

# =============================================================================

# Centralised function called by each per-kernel Makefile.in, which serves
# two main purposes: it 
#
# 1) generates Makefile rules for the kernel, then
# 2) updates BUILD_X for X in each built file type, meaning we can track 
#    the library content wrt. dependencies.

# ${1} = kernel identifier
# ${2} = kernel paths
# ${3} = header files (i.e.,      %.h)
# ${4} = source files (i.e., %.c, %.S)

define build
$(call map_target,$(notdir ${1}).elf) : ${3} ${4} 
	@$${TOOL_PREFIX}gcc $${CC_DIRS} $${CC_FLAGS} $$(addprefix -I ,${2}) -I $$(strip $${REPO_HOME})/build/$$(strip $${ARCH})/include -L $$(strip $${REPO_HOME})/build/$$(strip $${ARCH})/lib -o $${@} ${4} $${CC_LIBS} -lscarv 

$(call map_script,$(notdir ${1}).py ) : $(call map_target,$(notdir ${1}).elf)
	@$${TEST_PREFIX} $${<} $${TEST_SUFFIX} > $${@} 

$(call map_result,$(notdir ${1}).log) : $(call map_script,$(notdir ${1}).py )
	@python3 -O $${<} > $${@}

BUILD_TARGETS += $(call map_target,$(notdir ${1}).elf)

BUILD_SCRIPTS += $(call map_script,$(notdir ${1}).py )
BUILD_RESULTS += $(call map_result,$(notdir ${1}).log)
endef

# =============================================================================

# Initialise BUILD_X for each built file type, then include 
#
# 1) the per target architecture build configuration, plus
# 2) each per kernel build configuration.

BUILD_TARGETS  =

BUILD_SCRIPTS  =
BUILD_RESULTS  =

include ${REPO_HOME}/conf/${ARCH}.mk
include $(patsubst %,${REPO_HOME}/src/test/%/Makefile.in,${KERNELS})

# Construct a definitive list of built files, plus their associated paths 
# to allow pre-creation of an appropriate directory structure (note that
# use of sort is required to remove duplicates).

BUILD_FILES    = ${BUILD_TARGETS} 
BUILD_FILES   += ${BUILD_SCRIPTS} 
BUILD_FILES   += ${BUILD_RESULTS}

BUILD_PATHS    = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

# Define targets for built files not otherwise catered for, e.g., via the
# invocation of build function by the kernel build configurations.

${BUILD_PATHS} :
	@mkdir --parents ${@}

${CLEAN_PATHS} :
	@rm --force --recursive ${@}

# -----------------------------------------------------------------------------

# Define targets to drive build process, dividing into cases dependant on
# the host platform: for a Docker-based host platform, defer to it (i.e., 
# execute an analogous build process inside the container).

ifeq "${HOST}" "native"
build    : ${BUILD_PATHS} ${BUILD_TARGETS}

clean    : ${CLEAN_PATHS}

generate : build          ${BUILD_SCRIPTS}

validate : build generate ${BUILD_RESULTS}
	@( cat ${REPO_HOME}/build/${ARCH}/test/*.log | grep 'fail' ) || true
endif

ifeq "${HOST}" "docker"
build    :
	$(call docker,${@}-test)
clean    :
	$(call docker,${@}-test)
generate :
	$(call docker,${@}-test)
validate :
	$(call docker,${@}-test)
endif

# =============================================================================
