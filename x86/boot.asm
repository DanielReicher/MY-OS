org 0x7C00 ;tells the program to start in the address the bios look for the bootloader
bits 16 ;before booting, we are in real mode (16 bits)

start:
    jmp main

;function to print
print:
	push si ;save register
	push ax ;save register

.loop:
	lodsb ;load next char from si to al
	or al, al ; if both 0 returns 0 
	jz .done ;if zero, done printing bc we reach the end

	mov ah, 0x0E ;BIOS interrupt, ah = 0x0E print character
	mov bh, 0 ;bh = 0 is the first page of the BIOS's display pages
	int 0x10 ;call BIOS interrupt
	jmp .loop

.done:
	pop ax ;restore register
	pop si ;restore register
	ret ;return

read_sector:
	mov ah, 0x02 ;set the BIOS disk func to read sectors from drive
	mov al, 0x01 ;the number of the sector we want to read (1)
	int 0x13 ;calls BIOS disk services interrupt
	jc .failed_reading ;if the carry flag is set the reading failed
	ret

.failed_reading:
	mov si, msg_reading_error
	call print
	jmp $ ;infinite loop


main:
	xor ax, ax ;set ax to 0

	;set segments to 0
	mov ds, ax
	mov es, ax
	mov ss, ax

	;set stack pointer to the address the bios look for the bootloader
	mov sp, 0x7C00

	mov si, msg_hello
	call print

	call enter_protected_mode

	;configure and call read_sector to load sector 2 to 0
	mov ax, 0x0000
	mov es, ax ;dest segment
	mov bx, 0x0500 ;dest offsset
	mov dl, 0x00 ;floppy's drive 0
	mov ch, 0x00 ;cylinder 0
	mov cl, 0x02 ;sector 2
	mov dh, 0x00 ;head 0
	call read_sector


	; Jump to the kernel
    ;jmp 0x0000:0x0500


	hlt ;privileged instruction, stop executing until interrupt

.halt: ;infinite loop
	jmp .halt

;Message string
;0x0D- Carriage Return, bring back to the start of the line
;0x0A- Line Feed, next line
;0- null, end of the line
msg_hello: db 'Hello, OS World!', 0x0D, 0x0A, 0 
msg_reading_error db "Disk Read Error" , 0

%include "switchTo32.asm"

msg_protected: db 'Protected Mode is active', 0

;Fills the rest of the 512-byte boot sector with zeros
;$- currtent position in file, $$- beginning of the file
times 510-($-$$) db 0 

;Boot signature (0xAA55)- must be present at the last two bytes
;The BIOS checks this signature to determine if the disk is bootable
dw 0xAA55 
