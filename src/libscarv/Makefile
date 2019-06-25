# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# ${1} = kernel identifier
# ${2} = kernel paths
# ${3} = source file
# ${4} = source pattern
# ${5} = target pattern

define map_header
  $(patsubst ${4},$(strip ${REPO_HOME})/build/$(strip ${ARCH})/include/scarv/$(strip ${1})/$(strip ${5}),$(notdir ${3}))
endef
define map_object
  $(patsubst ${4},$(strip ${REPO_HOME})/build/$(strip ${ARCH})/lib/$(strip ${1})/$(strip ${5}),          $(notdir ${3}))
endef
define map_dump
  $(patsubst ${4},$(strip ${REPO_HOME})/build/$(strip ${ARCH})/lib/$(strip ${1})/$(strip ${5}),          $(notdir ${3}))
endef

define rule_header
$(call map_header,${1},${2},${3},${4},${5}) : ${3}
	@cat $${^} | envsubst > $${@}
endef
define rule_object
$(call map_object,${1},${2},${3},${4},${5}) : ${3}
	@$${TOOL_PREFIX}gcc $${CC_DIRS} $${CC_FLAGS} $$(addprefix -I ,${2}) -I $$(strip $${REPO_HOME})/build/$$(strip $${ARCH})/include -c -o $${@} $${<}
endef
define rule_dump
$(call map_dump,  ${1},${2},${3},${4},${5}) : ${5} : %.o
	@$${TOOL_PREFIX}objdump --disassemble-all $${<} > $${@} 
endef

# =============================================================================

# ${1} = kernel identifier
# ${2} = kernel paths
# ${3} = header files (i.e.,      %.h)
# ${4} = source files (i.e., %.c, %.S)

define generate
BUILD_HEADERS += $(foreach FILE,$(filter %.h,${3}),$(call map_header,${1},${2},${FILE},%.h,%.h      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.c,${4}),$(call map_object,${1},${2},${FILE},%.c,%.o      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.S,${4}),$(call map_object,${1},${2},${FILE},%.S,%.o      ))
BUILD_DUMPS   += $(foreach FILE,$(filter %.c,${4}),$(call map_dump,  ${1},${2},${FILE},%.c,%.objdump))
BUILD_DUMPS   += $(foreach FILE,$(filter %.S,${4}),$(call map_dump,  ${1},${2},${FILE},%.S,%.objdump))

$(foreach FILE,$(filter %.h, ${3}),$(eval $(call rule_header,${1},${2},${FILE},%.h,%.h      )))
$(foreach FILE,$(filter %.c, ${4}),$(eval $(call rule_object,${1},${2},${FILE},%.c,%.o      )))
$(foreach FILE,$(filter %.S, ${4}),$(eval $(call rule_object,${1},${2},${FILE},%.S,%.o      )))
$(foreach FILE,$(filter %.c, ${4}),$(eval $(call rule_dump,  ${1},${2},${FILE},%.c,%.objdump)))
$(foreach FILE,$(filter %.S, ${4}),$(eval $(call rule_dump,  ${1},${2},${FILE},%.S,%.objdump)))
endef

# =============================================================================

include ${REPO_HOME}/conf/${ARCH}.mk ${REPO_HOME}/conf/${ARCH}.conf 
include $(patsubst %,${REPO_HOME}/src/libscarv/%/Makefile.in,${KERNELS}) ${REPO_HOME}/src/libscarv/share/Makefile.in

BUILD_FILES   = ${BUILD_HEADERS} 
BUILD_FILES  += ${BUILD_OBJECTS} 
BUILD_FILES  += ${BUILD_DUMPS}

BUILD_PATHS   = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

BUILD_TARGETS = ${REPO_HOME}/build/${ARCH}/lib/libscarv.a

${BUILD_PATHS} :
	@mkdir --parents ${@}

${BUILD_TARGETS} : %.a : ${BUILD_OBJECTS}
	@${TOOL_PREFIX}ar rcs ${@} ${^}

clean :
	@rm --force --recursive ${BUILD_PATHS}

build :                         ${BUILD_PATHS} ${BUILD_HEADERS} ${BUILD_OBJECTS} ${BUILD_DUMPS} ${BUILD_TARGETS}

# =============================================================================
