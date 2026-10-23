SRC = $(wildcard *.asm)
BOOT = boot.asm
BUILD = build/
IMG = build/floppy.img
BIN = build/boot.bin

.PHONY: run
run: $(IMG)
	qemu-system-i386 -fda $(IMG)

$(IMG): $(BIN)
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$^ of=$@ conv=notrunc

$(BIN): $(SRC)
	nasm $(BOOT) -f bin -o $@
