
SRCS = test.c
OUT  = test.elf

CC     = $(RISCV)/bin/riscv32-unknown-elf-gcc
OBJDUMP= $(RISCV)/bin/riscv32-unknown-elf-objdump

SPIKE  = /home/ben/tools/xc-riscv/bin/spike
PK     = /home/ben/tools/xc-riscv/riscv32-unknown-elf/bin/pk

$(OUT) : $(SRCS)
	$(CC) -O2  -o $@ $< 
	$(OBJDUMP) -D $@ > $@.dis

run : $(OUT)
	$(SPIKE) $(PK) $(OUT)
