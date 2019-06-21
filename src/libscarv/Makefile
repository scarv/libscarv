# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# ${1} = kernel identifier
# ${2} = source file
# ${3} = source pattern
# ${4} = target pattern

define map_include
  $(patsubst ${3},${REPO_HOME}/build/include/scarv/$(strip ${1})/$(strip ${4}),$(notdir ${2}))
endef
define map_lib
  $(patsubst ${3},${REPO_HOME}/build/lib/$(strip ${1})/$(strip ${4}),          $(notdir ${2}))
endef

define rule_header
$(call map_include,${1},${2},${3},${4}) : ${2}
	@cat $${^} | envsubst > $${@}
endef
define rule_object
$(call map_lib,    ${1},${2},${3},${4}) : ${2}
	@$${TOOL_PREFIX}gcc -I ${REPO_HOME}/build/include -c -o $${@} $${<}
endef
define rule_dump
$(call map_lib,    ${1},${2},${3},${4}) : ${4} : %.o
	@$${TOOL_PREFIX}objdump --disassemble-all $${<} > $${@} 
endef

# =============================================================================

# ${1} = kernel identifier
# ${2} = header files (i.e.,      %.h)
# ${2} = source files (i.e., %.c, %.S)

define generate
BUILD_HEADERS += $(foreach FILE,$(filter %.h,${2}),$(call map_include,${1},${FILE},%.h,%.h      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.c,${3}),$(call map_lib,    ${1},${FILE},%.c,%.o      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.S,${3}),$(call map_lib,    ${1},${FILE},%.S,%.o      ))
BUILD_DUMPS   += $(foreach FILE,$(filter %.c,${3}),$(call map_lib,    ${1},${FILE},%.c,%.objdump))
BUILD_DUMPS   += $(foreach FILE,$(filter %.S,${3}),$(call map_lib,    ${1},${FILE},%.S,%.objdump))

$(foreach FILE,$(filter %.h, ${2}),$(eval $(call rule_header,${1},${FILE},%.h,%.h      )))
$(foreach FILE,$(filter %.c, ${3}),$(eval $(call rule_object,${1},${FILE},%.c,%.o      )))
$(foreach FILE,$(filter %.S, ${3}),$(eval $(call rule_object,${1},${FILE},%.S,%.o      )))
$(foreach FILE,$(filter %.c, ${3}),$(eval $(call rule_dump,  ${1},${FILE},%.c,%.objdump)))
$(foreach FILE,$(filter %.S, ${3}),$(eval $(call rule_dump,  ${1},${FILE},%.S,%.objdump)))
endef

# =============================================================================

include $(patsubst %, ${REPO_HOME}/src/libscarv/%/Makefile.in, ${KERNELS} share)

BUILD_FILES   = ${BUILD_HEADERS} 
BUILD_FILES  += ${BUILD_OBJECTS} 
BUILD_FILES  += ${BUILD_DUMPS}

BUILD_PATHS   = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

BUILD_TARGETS = ${REPO_HOME}/build/lib/libscarv.a

${BUILD_PATHS} :
	@mkdir --parents ${@}

${BUILD_TARGETS} : %.a : ${BUILD_OBJECTS}
	@${PREFIX}ar rcs ${@} ${^}

clean    :
	@rm --force --recursive ${BUILD_PATHS}

build    :                      ${BUILD_PATHS} ${BUILD_HEADERS} ${BUILD_OBJECTS} ${BUILD_DUMPS} ${BUILD_TARGETS}

# =============================================================================
