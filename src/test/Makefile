# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# ${1} = kernel identifier

define map_bin
  ${REPO_HOME}/build/${ARCH}/bin/test_$(strip ${1})
endef
define map_log
  ${REPO_HOME}/build/${ARCH}/log/test_$(strip ${1})
endef

# =============================================================================

# ${1} = kernel identifier
# ${2} = directories
# ${3} = header files (i.e.,      %.h)
# ${4} = source files (i.e., %.c, %.S)

define generate
BUILD_TARGETS += $(call map_bin,$(notdir ${1}).elf)
BUILD_SCRIPTS += $(call map_log,$(notdir ${1}).py )
BUILD_RESULTS += $(call map_log,$(notdir ${1}).log)

$(call map_bin,$(notdir ${1}).elf) : ${3} ${4} 
	@$${TOOL_PREFIX}gcc $${CC_DIRS} $${CC_FLAGS} $$(addprefix -I, ${2}) -I $${REPO_HOME}/build/${ARCH}/include -L $${REPO_HOME}/build/${ARCH}/lib -o $${@} ${4} $${CC_LIBS} -lscarv 

$(call map_log,$(notdir ${1}).py ) : $(call map_bin,$(notdir ${1}).elf)
	@$${TEST_PREFIX} $${<}${TEST_SUFFIX} > $${@} 

$(call map_log,$(notdir ${1}).log) : $(call map_log,$(notdir ${1}).py )
	@python3 -O $${<} > $${@}
endef

# =============================================================================

include $(patsubst %, ${REPO_HOME}/src/test/%/Makefile.in, ${KERNELS})

BUILD_FILES   = ${BUILD_TARGETS} 
BUILD_FILES  += ${BUILD_SCRIPTS} 
BUILD_FILES  += ${BUILD_RESULTS}

BUILD_PATHS   = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

${BUILD_PATHS} :
	@mkdir --parents ${@}

clean    :
	@rm --force --recursive ${BUILD_PATHS}

build    :                      ${BUILD_PATHS} ${BUILD_TARGETS}

generate : build                               ${BUILD_SCRIPTS}

validate : build generate                      ${BUILD_RESULTS}
	@( cat ${REPO_HOME}/build/${ARCH}/log/*.log | grep 'fail' ) || true

# =============================================================================
