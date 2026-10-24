# ==============================================================================
#                                 Build Makefile
# ==============================================================================
# This Makefile builds and runs the OS, and contains documentation on how to
# run. It contains two rules: 'run', 'clean'. See below.
# ==============================================================================

# ------ Helpers ---------------------------------------------------------------
command_exists = $(shell command -v $(1))
this_or_that = $(if $(call command_exists,$(1)),$(1),$(2))

# ------ Configuration ---------------------------------------------------------
# These variables are for you to configure. Default values are approximations.
CC := $(call this_or_that,i386-elf-gcc,gcc) # the C compiler - i386-elf-gcc or gcc
LD := $(call this_or_that,i386-elf-ld,ld) # the linker - i386-elf-ld or ld
OBJCOPY := $(call this_or_that,i386-elf-objcopy,objcopy)

# ------ Files and Directories -------------------------------------------------
SRC := $(wildcard *.asm)
BOOT := boot.asm
BUILD_DIR := build
IMG := $(BUILD_DIR)/floppy.img
BIN := $(BUILD_DIR)/boot.bin

# Define a rule called 'run' that builds and runs. This rule is the default
# because it is first.
.PHONY: run
run: $(IMG)
	qemu-system-i386 -fda $(IMG)

<<<<<<< HEAD
$(IMG): $(BIN) test.out
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BIN) of=$@ conv=notrunc
	dd if=test.out of=build/floppy.img conv=notrunc seek=1
=======
$(IMG): $(BIN) test.bin | $(BUILD_DIR)
	@# Make sure we build the file completely from scratch.
	rm -f $@
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BIN) of=$@ conv=notrunc
	dd if=test.bin of=$@ conv=notrunc bs=512 seek=1
>>>>>>> 0116f3e19606242c650d2cac3f0e80eeef25b4eb

$(BIN): $(SRC) | $(BUILD_DIR)
	nasm $(BOOT) -f bin -o $@

<<<<<<< HEAD
test.o : test.c 
	gcc test.c -march=i386 -m32 -c -ffreestanding -nostdlib

test.out : test.o
	ld -m elf_i386 -Ttext 0x200 test.o -o test.out
=======
test.o: test.c
	$(CC) -nostdlib -ffreestanding -nostartfiles test.c -c -o test.o

test.out: test.o
	$(LD) test.o -o test.out

test.bin: test.out
	@# The `-O` flag specifies the output format.
	$(OBJCOPY) -I elf32-i386 -O binary $< $@

$(BUILD_DIR):
	mkdir -p $@

# Define a rule called 'clean'.
.PHONY: clean
clean:
	rm -r -f build
	rm -f test.o test.out test.bin
>>>>>>> 0116f3e19606242c650d2cac3f0e80eeef25b4eb
