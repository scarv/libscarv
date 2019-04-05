ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

ifndef ARCH
  $(error "undefined environment variable: ARCH"   )
endif
ifndef KERNELS
  $(error "undefined environment variable: KERNELS")
endif

#
# Top-level variables that the included makefiles will modify
#
 
TRASH           =

INSTALL_DIR     =build/$(ARCH)
OBJ_DIR         = $(INSTALL_DIR)/obj
LIB_DIR         = $(INSTALL_DIR)/lib
BIN_DIR         = $(INSTALL_DIR)/bin
HEADER_DIR      = $(INSTALL_DIR)/include/scarv
WORK_DIR        = $(INSTALL_DIR)/work

#CFLAGS         += -Isrc/share

# All object files to be compiled
OBJS            =

# Static libraries to build
LIBS            = 

# Test executables
TESTS           =
TEST_OUTPUTS    =

# Headers to be coppied to the installation dir.
HEADERS         =

# Disassembly targets
DISASM          =
DISASM_DIR      = $(INSTALL_DIR)/disasm

# Object files to be included in libscarv.a
LIBSCARV_LIBID  =libscarv.a
LIBSCARV        =$(LIB_DIR)/$(LIBSCARV_LIBID)
LIBS           +=$(LIBSCARV)

#
# Include the generic top-level configuration makefile.
#
include Makefile.conf

#
# Include the architecture specific make file.
#
ifeq ($(ARCH),generic)
    CFLAGS += -DLIBSCARV_ARCH_GENERIC
    include Makefile.arch-generic
else ifeq ($(ARCH),riscv)
    include Makefile.arch-riscv
    CFLAGS += -DLIBSCARV_ARCH_RISCV
else ifeq ($(ARCH),riscv-xcrypto)
    include Makefile.arch-riscv-xcrypto
    CFLAGS += -DLIBSCARV_ARCH_RISCV_XCRYPTO
else
    $(error Unknown architecture specified: $(ARCH))
endif

# Add architecture specific configuration switches to CFLAGS
CFLAGS += $(CONF)

#
# Functions for generating rules
#

#
# 1 - header source path
# 2 - destination subfolder
#
define map_include
$(abspath $(HEADER_DIR)/${2}/$(notdir ${1}))
endef

#
# 1 - header source path
# 2 - destination subfolder
#
define tgt_include_header
$(call map_include,${1},${2}) : $(abspath ${1}) ;
	@mkdir -p $(dir $(call map_include,${1},${2}))
	cp $${^} $${@}

endef

#
# 1 - object file source path
# 2 - destination subfolder
#
define map_obj
    $(OBJ_DIR)/${2}/$(basename $(notdir ${1})).o
endef

#
# 1 - object file source path
# 2 - destination subfolder
# 3 - extra flags
#
define tgt_obj
$(call map_obj,${1},${2}) : ${1} ;
	@mkdir -p $(dir $(call map_obj,${1},${2}))
	$(CC) -c ${CFLAGS} ${3} -o $$@ $$<

endef

#
# 1 - library name
#
define map_static_lib
    $(LIB_DIR)/lib$(basename $(notdir ${1})).a
endef

#
# 1 - Source objects
# 2 - Library name
#
define tgt_static_lib
$(call map_static_lib,${2}) : ${1} ;
	@mkdir -p $(dir $(call map_static_lib,${2}))
	$(AR) rcs $$@ $$^
endef

#
# 1 - object file source path
# 2 - destination subfolder
#
define map_disasm
    $(DISASM_DIR)/${2}/$(basename $(notdir ${1})).dis
endef

#
# 1 - object file source path
# 2 - destination subfolder
#
define tgt_disasm
$(call map_disasm,${1},${2}) : $(call map_obj,${1},${2}) ;
	@mkdir -p $(dir $(call map_disasm,${1},${2}))
	$(OBJDUMP) -D $$< > $$@
endef

#
# GCC tool paths - GCC_PREFIX set by architecture dependent makefile.
#
AS         = ${GCC_PREFIX}as
CC         = ${GCC_PREFIX}gcc
AR         = ${GCC_PREFIX}ar
OBJDUMP    = ${GCC_PREFIX}objdump
OBJCOPY    = ${GCC_PREFIX}objcopy

#
# Include the makefiles responsible for each portion of the library
#

all: headers objects disasm libs tests

# Shared utility code
$(eval $(call tgt_include_header,src/share/util.h,.))
HEADERS += $(call map_include,src/share/util.h,.)

# includes
$(foreach KERNEL,${KERNELS},$(eval include ./src/${KERNEL}/Makefile.in))
include test/Makefile.in

TRASH += $(HEADERS) $(OBJS) $(DISASM) $(LIBS) $(TESTS)

headers: $(HEADERS)
objects: $(OBJS)
libs:    $(LIBS)
disasm:  $(DISASM)
tests:   $(HEADERS) $(LIBS) $(TESTS)

$(LIBSCARV) : $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

test     : $(TEST_OUTPUTS)

venv     : ${REPO_HOME}/requirements.txt
	@${REPO_HOME}/bin/venv.sh

doc      : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

clean    :
	@rm -rf ${REPO_HOME}/build/*
