# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# ${1} = kernel identifier

define bin_map
  ${REPO_HOME}/build/bin/test_${1}
endef

define log_map
  ${REPO_HOME}/build/log/test_${1}
endef

# =============================================================================

# ${1} = kernel identifier
# ${2} = directories
# ${3} = header files (i.e.,      %.h)
# ${4} = source files (i.e., %.c, %.S)

define generate
TARGET_TARGETS += $(call bin_map,$(notdir ${1}).elf)
TARGET_RESULTS += $(call log_map,$(notdir ${1}).py )
TARGET_RESULTS += $(call log_map,$(notdir ${1}).log)

$(call bin_map,$(notdir ${1}).elf) : ${3} ${4} 
	@$${PREFIX}gcc $$(addprefix -D, $${CONF}) $${CC_DIRS} $${CC_FLAGS} $$(addprefix -I, ${2}) -I $${REPO_HOME}/build/include -L $${REPO_HOME}/build/lib -o $${@} ${4} $${CC_LIBS} -lscarv 
$(call log_map,$(notdir ${1}).py ) : $(call bin_map,$(notdir ${1}).elf)
	@$${TEST_PREFIX} $${<}${TEST_SUFFIX} > $${@} 
$(call log_map,$(notdir ${1}).log) : $(call log_map,$(notdir ${1}).py )
	@python3 -O $${<} > $${@}
endef

# =============================================================================

TARGET_DIRS     = ${REPO_HOME}/build/bin
TARGET_DIRS    += ${REPO_HOME}/build/log

TARGET_TARGETS  = 
TARGET_RESULTS  = 

include $(patsubst %, ${REPO_HOME}/src/test/%/Makefile.in, ${KERNELS})

TARGET_DIRS    := $(sort ${TARGET_DIRS}   )

TARGET_TARGETS := $(sort ${TARGET_TARGETS})
TARGET_RESULTS := $(sort ${TARGET_RESULTS})

${TARGET_DIRS} :
	@mkdir --parents ${@}

build : ${TARGET_DIRS} ${TARGET_TARGETS}

clean :

run   : build          ${TARGET_RESULTS}

# =============================================================================
