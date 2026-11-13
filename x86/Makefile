# ==============================================================================
#                                 Build Makefile
# ==============================================================================
# This Makefile builds and runs the OS, and contains documentation on how to
# run. It contains two rules: 'run', 'clean'. See below.
# ==============================================================================

# ------ Helpers ---------------------------------------------------------------
command_exists = $(shell command -v $(1))

# ------ Tool Flags ------------------------------------------------------------
# These are just some of the flags. Certain flags should be set in the Toolchain
# section instead.
gcc_flags := -m32 -nostdlib -ffreestanding -nostartfiles
ld_flags := -Ttext 0x7E00 -e 0
objcopy :=

# ------ Toolchain -------------------------------------------------------------
# On Daniel's machine we use a standard GCC version, but on Jonathan's we use
# the i386 version of GCC (our target architecture). That means that on Daniel's
# machine we *cross-compile* (that's what it's called). This part is where we
# decide whether to cross-compile or not.
target_arch_gcc     := i386-elf-gcc
target_arch_ld      := i386-elf-ld
target_arch_objcopy := i386-elf-objcopy
has_gcc := $(call command_exists,gcc)
has_target_arch_gcc := $(call command_exists,$(target_arch_gcc))
ifneq ($(has_target_arch_gcc),) # If this did not return an empty string...
	gcc := $(target_arch_gcc)
	ld := $(target_arch_ld)
	objcopy := $(target_arch_objcopy)
else
	gcc := gcc
	ld := ld
	ld_flags += -m elf_i386
	objcopy := objcopy
endif

# ------ Files and Directories -------------------------------------------------
src := $(wildcard *.asm)
boot := boot.asm
build_dir := build
img := $(build_dir)/floppy.img
bin := $(build_dir)/boot.bin

# Define a rule called 'run' that builds and runs. This rule is the default
# because it is first.
.PHONY: run
run: $(img)
	qemu-system-i386 -fda $(img)

$(img): $(bin) test.bin | $(build_dir)
	@# Make sure we build the file completely from scratch.
	rm -f $@
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(bin) of=$@ conv=notrunc
	dd if=test.bin of=$@ conv=notrunc bs=512 seek=1

$(bin): $(src) | $(build_dir)
	nasm $(boot) -f bin -o $@

test.o: test.c
	$(gcc) $(gcc_flags) test.c -c -o test.o

test.out: test.o
	$(ld) $(ld_flags) test.o -o test.out
	
test.bin: test.out
	@# The `-O` flag specifies the output format.
	$(objcopy) $(objcopy_flags) -I elf32-i386 -O binary test.out test.bin

$(build_dir):
	mkdir -p $@

# Define a rule called 'clean'.
.PHONY: clean
clean:
	rm -r -f build
	rm -f test.o test.out test.bin
