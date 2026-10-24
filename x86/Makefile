SRC = $(wildcard *.asm)
BOOT = boot.asm
BUILD = build/
IMG = build/floppy.img
BIN = build/boot.bin

.PHONY: run
run: $(IMG)
	qemu-system-i386 -fda $(IMG)

$(IMG): $(BIN) test.out
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BIN) of=$@ conv=notrunc
	dd if=test.out of=build/floppy.img conv=notrunc seek=1

$(BIN): $(SRC)
	nasm $(BOOT) -f bin -o $@

test.o : test.c 
	gcc test.c -march=i386 -m32 -c -ffreestanding -nostdlib

test.out : test.o
	ld -m elf_i386 -Ttext 0x200 test.o -o test.out