# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

# For each built file type, map source path into build path so as to allow
# totally out-of-tree build.

# ${1} = identifier (i.e., sub-directory)
# ${2} = search path
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

# =============================================================================

# For each built file type, generate suitable Makefile rule.

# ${1} = identifier (i.e., sub-directory)
# ${2} = search path
# ${3} = source file
# ${4} = source pattern
# ${5} = target pattern

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
	@$${TOOL_PREFIX}objdump --all-headers --syms --reloc --disassemble-all --source --wide $${<} > $${@} 
endef

# =============================================================================

# Centralised function called by each per-kernel Makefile.in, which serves
# two main purposes: it 
#
# 1) generates Makefile rules for the kernel, then
# 2) updates BUILD_X for X in each built file type, meaning we can track 
#    the library content wrt. dependencies.

# ${1} = identifier (i.e., sub-directory)
# ${2} = search path
# ${3} = header files (i.e.,      %.h)
# ${4} = source files (i.e., %.c, %.S)

define build
$(foreach FILE,$(filter %.h, ${3}),$(eval $(call rule_header,${1},${2},${FILE},%.h,%.h      )))
$(foreach FILE,$(filter %.c, ${4}),$(eval $(call rule_object,${1},${2},${FILE},%.c,%.o      )))
$(foreach FILE,$(filter %.S, ${4}),$(eval $(call rule_object,${1},${2},${FILE},%.S,%.o      )))
$(foreach FILE,$(filter %.c, ${4}),$(eval $(call rule_dump,  ${1},${2},${FILE},%.c,%.objdump)))
$(foreach FILE,$(filter %.S, ${4}),$(eval $(call rule_dump,  ${1},${2},${FILE},%.S,%.objdump)))

BUILD_HEADERS += $(foreach FILE,$(filter %.h,${3}),$(call map_header,${1},${2},${FILE},%.h,%.h      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.c,${4}),$(call map_object,${1},${2},${FILE},%.c,%.o      ))
BUILD_OBJECTS += $(foreach FILE,$(filter %.S,${4}),$(call map_object,${1},${2},${FILE},%.S,%.o      ))
BUILD_DUMPS   += $(foreach FILE,$(filter %.c,${4}),$(call map_dump,  ${1},${2},${FILE},%.c,%.objdump))
BUILD_DUMPS   += $(foreach FILE,$(filter %.S,${4}),$(call map_dump,  ${1},${2},${FILE},%.S,%.objdump))
endef

# =============================================================================

# Automagically derive configuration symbol for target architecture.

export LIBSCARV_CONF_ARCH = $(shell echo ${ARCH} | tr [:lower:] [:upper:] | tr '-' '_')

# Automagically derive configuration symbols to enable each kernel.

define kernel_enum
  $(shell find ${REPO_HOME}/src/libscarv/ -mindepth 2 -maxdepth 2 -type d -printf '%P\n')
endef
define kernel_enable
  $(shell if [ "$(filter ${KERNELS},${1})" = "" ] ; then echo "0" ; else echo "1" ; fi)
endef

$(foreach KERNEL,$(call kernel_enum),$(eval export $(addprefix LIBSCARV_CONF_,$(addsuffix _ENABLE,$(notdir $(shell echo ${KERNEL} | tr [:lower:] [:upper:])))) = $(call kernel_enable,${KERNEL})))

# -----------------------------------------------------------------------------

# Initialise BUILD_X for each built file type, then include 
#
# 1) the per target architecture build and library configurations, plus
# 2) each per kernel build configuration (plus global and shared pseudo
#    kernels).

BUILD_TARGETS  = ${REPO_HOME}/build/${ARCH}/lib/libscarv.a

BUILD_HEADERS  = 
BUILD_OBJECTS  = 
BUILD_DUMPS    = 

include ${REPO_HOME}/conf/${ARCH}.mk ${REPO_HOME}/conf/${ARCH}.conf 
include $(patsubst %,${REPO_HOME}/src/libscarv/%/Makefile.in,${KERNELS}) ${REPO_HOME}/src/libscarv/Makefile.in ${REPO_HOME}/src/libscarv/share/Makefile.in

# Construct a definitive list of built files, plus their associated paths 
# to allow pre-creation of an appropriate directory structure (note that
# use of sort is required to remove duplicates).

BUILD_FILES    = ${BUILD_HEADERS} 
BUILD_FILES   += ${BUILD_OBJECTS} 
BUILD_FILES   += ${BUILD_DUMPS}

BUILD_PATHS    = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

# Define targets for built files not otherwise catered for, e.g., via the
# invocation of build function by the kernel build configurations.

${BUILD_TARGETS} : %.a : ${BUILD_OBJECTS}
	@${TOOL_PREFIX}ar rcs ${@} ${^}

${BUILD_PATHS} :
	@mkdir --parents ${@}

${CLEAN_PATHS} :
	@rm --force --recursive ${@}

# -----------------------------------------------------------------------------

# Define targets to drive build process, dividing into cases dependant on
# the host platform: for a Docker-based host platform, defer to it (i.e., 
# execute an analogous build process inside the container).

ifeq "${HOST}" "native"
build : ${BUILD_PATHS} ${BUILD_HEADERS} ${BUILD_OBJECTS} ${BUILD_DUMPS} ${BUILD_TARGETS}

clean : ${CLEAN_PATHS}
endif

ifeq "${HOST}" "docker"
build :
	@$(call docker,${@}-libscarv)
clean :
	@$(call docker,${@}-libscarv)
endif

# =============================================================================
