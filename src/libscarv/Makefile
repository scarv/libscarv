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

define include_map
  $(patsubst ${3},${REPO_HOME}/build/include/scarv/${1}/${4},$(notdir ${2}))
endef
define     lib_map
  $(patsubst ${3},${REPO_HOME}/build/lib/${1}/${4},          $(notdir ${2}))
endef

define include_rule
$(call include_map,${1},${2},${3},${4}) : ${2}
	@cp $${^} $${@}
endef
define     lib_rule
$(call     lib_map,${1},${2},${3},${4}) : ${2}
	@$${PREFIX}gcc $$(addprefix -D, $${CONF}) $${CC_DIRS} $${CC_FLAGS} -I ${REPO_HOME}/build/include -c -o $${@} $${<}
endef

# =============================================================================

# ${1} = kernel identifier
# ${2} = header files (i.e.,      %.h)
# ${2} = source files (i.e., %.c, %.S)

define generate
TARGET_DIRS    += $(foreach FILE,$(filter %.h,${2}),$(dir $(call include_map,${1},${FILE},%.h,%.h)))
TARGET_DIRS    += $(foreach FILE,$(filter %.c,${3}),$(dir $(call     lib_map,${1},${FILE},%.c,%.o)))
TARGET_DIRS    += $(foreach FILE,$(filter %.S,${3}),$(dir $(call     lib_map,${1},${FILE},%.S,%.o)))

TARGET_HEADERS += $(foreach FILE,$(filter %.h,${2}),$(call include_map,${1},${FILE},%.h,%.h))
TARGET_OBJECTS += $(foreach FILE,$(filter %.c,${3}),$(call     lib_map,${1},${FILE},%.c,%.o))
TARGET_OBJECTS += $(foreach FILE,$(filter %.S,${3}),$(call     lib_map,${1},${FILE},%.S,%.o))

$(foreach FILE,$(filter %.h, ${2}),$(eval $(call include_rule,${1},${FILE},%.h,%.h)))
$(foreach FILE,$(filter %.c, ${3}),$(eval $(call     lib_rule,${1},${FILE},%.c,%.o)))
$(foreach FILE,$(filter %.S, ${3}),$(eval $(call     lib_rule,${1},${FILE},%.S,%.o)))
endef

# =============================================================================

TARGET_DIRS     = ${REPO_HOME}/build/lib ${REPO_HOME}/build/include/scarv

TARGET_HEADERS  = 
TARGET_OBJECTS  = 

include $(patsubst %, ${REPO_HOME}/src/libscarv/%/Makefile.in, ${KERNELS} share)

TARGET_DIRS    := $(sort ${TARGET_DIRS}   )

TARGET_HEADERS := $(sort ${TARGET_HEADERS})
TARGET_OBJECTS := $(sort ${TARGET_OBJECTS})

TARGET_TARGETS  = ${REPO_HOME}/build/lib/libscarv.a

${TARGET_DIRS} :
	@mkdir --parents ${@}

${TARGET_TARGETS} : %.a : ${TARGET_OBJECTS}
	@${PREFIX}ar rcs ${@} ${^}

build    :                      ${TARGET_DIRS} ${TARGET_HEADERS} ${TARGET_OBJECTS} ${TARGET_TARGETS}

clean    :
	@rm --force --recursive ${TARGET_DIRS} ${TARGET_HEADERS} ${TARGET_OBJECTS} ${TARGET_TARGETS}

# =============================================================================
