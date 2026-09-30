osname := $(shell uname -s)

# Use Android toolchain on OS X
# Use bare metal ARM64 toolchain on Linux
ifeq ($(osname), Darwin)
CROSS_PREFIX = aarch64-linux-android-
else
CROSS_PREFIX = aarch64-none-elf-
endif

# Build the kernel binary
all: kernel.bin

# Compile kernel.c into kernel.o
kernel.o: kernel.c
	$(CROSS_PREFIX)gcc -c $< -o $@ -ffreestanding

# Compile uarnt.c into uarnt.o
uarnt.o: uarnt.c
	$(CROSS_PREFIX)gcc -c $< -o $@ -ffreestanding

# Assemble boot.asm into boot.o
boot.o: boot.asm
	$(CROSS_PREFIX)as $< -o $@

# Link all object files using the linker script
kernel.elf: kernel.o uarnt.o boot.o
	$(CROSS_PREFIX)ld -T linker.ld $^ -o $@

# Convert ELF file to binary
kernel.bin: kernel.elf
	$(CROSS_PREFIX)objcopy -O binary $< $@

# Remove generated files
clean:
	rm -f kernel.bin kernel.elf boot.o kernel.o uarnt.o