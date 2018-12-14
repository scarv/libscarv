 SRC_PATHS   += ./src/share \
                ./src/aes/share \
                ./src/aes/${TYPE} \
                ./src/aes/${TYPE}/${ARCH} \
                ./src/mp/mpn \
                ./src/mp/mpn/${ARCH} \
                ./src/mp/mpz \
                ./src/mp/mrz \
                ./src/mp/limb \
                ./src/mp/limb/${ARCH} \
                ./src/keccak \
                ./src/keccak/${ARCH} \
                ./src/prince \
                ./src/prince/${ARCH}

 SRC_HEADERS += $(foreach DIR,${SRC_PATHS},$(wildcard ${DIR}/*.h))
 SRC_SOURCES += $(foreach DIR,${SRC_PATHS},$(wildcard ${DIR}/*.c))
 SRC_SOURCES += $(foreach DIR,${SRC_PATHS},$(wildcard ${DIR}/*.S))

define include_map
  $(patsubst ${1},./build/include/${LIB_ID}/${2},$(notdir ${3}))
endef
define     lib_map
  $(patsubst ${1},./build/lib/${2},              $(notdir ${3}))
endef

define include_rule
$(call include_map,${1},${2},${3}) : ${3}
	@cp $${^} $${@}
endef
define     lib_rule
$(call     lib_map,${1},${2},${3}) : ${3}
	$${CC} $$(patsubst %, -I %, $${SRC_PATHS}) $${GCC_PATHS} $${GCC_FLAGS} -c -o $${@} $${<}
endef
define     asm_lib_rule
$(call     lib_map,${1},${2},${3}) : ${3}
	$$(AS) $$(patsubst %, -I %, $${SRC_PATHS}) $${GCC_PATHS} $${AS_FLAGS} -c -o $${@} $${<}
endef

 LIB_ID       = scarv
 LIB_VERSION  = 

 LIB_PATHS   += ./build/bin ./build/lib ./build/include/${LIB_ID}

 LIB_HEADERS += $(foreach FILE,$(filter %.h, ${SRC_HEADERS}),$(call include_map,%.h,%.h,${FILE}))
 LIB_OBJECTS += $(foreach FILE,$(filter %.c, ${SRC_SOURCES}),$(call     lib_map,%.c,%.o,${FILE}))
 LIB_OBJECTS += $(foreach FILE,$(filter %.S, ${SRC_SOURCES}),$(call     lib_map,%.S,%.o,${FILE}))

 LIB_TARGET  += ./build/lib/lib${LIB_ID}.a

$(foreach FILE, $(filter %.h, ${SRC_HEADERS}), $(eval $(call include_rule,%.h,%.h,${FILE})))
$(foreach FILE, $(filter %.c, ${SRC_SOURCES}), $(eval $(call     lib_rule,%.c,%.o,${FILE})))
$(foreach FILE, $(filter %.S, ${SRC_SOURCES}), $(eval $(call asm_lib_rule,%.S,%.o,${FILE})))

${LIB_PATHS}   :
	@mkdir -p ${@}
${LIB_TARGET} : ${LIB_OBJECTS}
	${AR} rcs ${@} ${^}

TEST_PATHS   += ./test ./test/aes ./test/mp

TEST_HEADERS += $(foreach DIR,${TEST_PATHS},$(wildcard ${DIR}/*.h))
TEST_SOURCES += $(foreach DIR,${TEST_PATHS},$(wildcard ${DIR}/*.c))
TEST_SOURCES += $(foreach DIR,${TEST_PATHS},$(wildcard ${DIR}/*.S))

TEST_TARGET  += ./build/bin/lib${LIB_ID}_test.elf

${TEST_TARGET} : ${LIB_TARGET} ${TEST_SOURCES} ${TEST_HEADERS}
	${CC} -L ./build/lib -I ./build/include -I ./test ${GCC_PATHS} ${GCC_FLAGS} -o ${@} $(filter %.c, ${^}) -l${LIB_ID}

lib      : ${LIB_TARGET}

objects  : ${LIB_PATHS} ${LIB_HEADERS} ${LIB_OBJECTS}

all      : objects ${LIB_TARGET} ${TEST_TARGET}

clean    :
	@rm -rf ${LIB_PATHS} ${LIB_HEADERS} ${LIB_OBJECTS} ${LIB_TARGET} ${TEST_TARGET}

spotless :
	@rm -rf ./build/*
